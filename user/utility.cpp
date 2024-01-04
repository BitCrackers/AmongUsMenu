#include "pch-il2cpp.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "gitparams.h"
#include "logger.h"
#include "profiler.h"
#include <random>
#include <regex>

using namespace std::string_view_literals;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

RoleRates::RoleRates(const class GameOptions& gameOptions, int playerAmount) {
	this->ImpostorCount = gameOptions.GetNumImpostors();
	auto maxImpostors = GetMaxImpostorAmount(playerAmount);
	if (State.CustomImpostorAmount)
		this->ImpostorCount = maxImpostors;
	else if (this->ImpostorCount > maxImpostors)
		this->ImpostorCount = maxImpostors;

	const auto& roleOptions = gameOptions.GetRoleOptions();
#define GET_ROLE_RATE(type) \
	this->type##Chance = roleOptions.GetChancePerGame(RoleTypes__Enum::##type); \
	this->type##Count = roleOptions.GetNumPerGame(RoleTypes__Enum::##type);

	GET_ROLE_RATE(Engineer);
	GET_ROLE_RATE(Scientist);
	GET_ROLE_RATE(Shapeshifter);
	GET_ROLE_RATE(GuardianAngel);
#undef GET_ROLE_RATE
}

int RoleRates::GetRoleCount(RoleTypes__Enum role) {
	switch (role)
	{
		case RoleTypes__Enum::Shapeshifter:
			return this->ShapeshifterCount;
		case RoleTypes__Enum::Impostor:
			return this->ImpostorCount;
		case RoleTypes__Enum::Scientist:
			return this->ScientistCount;
		case RoleTypes__Enum::Engineer:
			return this->EngineerCount;
		case RoleTypes__Enum::GuardianAngel:
			return this->GuardianAngelCount;
		case RoleTypes__Enum::Crewmate:
			return this->MaxCrewmates;
		default:
#ifdef _DEBUG
			assert(false);
#endif
			return 0;
	}
}

void RoleRates::SubtractRole(RoleTypes__Enum role) {
	if (role == RoleTypes__Enum::Shapeshifter)
	{
		if (this->ShapeshifterCount < 1)
			return;
		this->ShapeshifterCount--;
		this->ImpostorCount--;
	}
	else if (role == RoleTypes__Enum::Impostor)
	{
		if (this->ImpostorCount < 1)
			return;
		this->ImpostorCount--;
		this->ShapeshifterCount--;
	}
	else if (role == RoleTypes__Enum::Scientist)
	{
		if (this->ScientistCount < 1)
			return;
		this->ScientistCount--;
	}
	else if (role == RoleTypes__Enum::Engineer)
	{
		if (this->EngineerCount < 1)
			return;
		this->EngineerCount--;
	}
	else if (role == RoleTypes__Enum::GuardianAngel)
	{
		if (this->GuardianAngelCount < 1)
			return;
		this->GuardianAngelCount--;
	}
}

int GetMaxImpostorAmount(int playerAmount)
{
	GameOptions options;
	if (State.CustomImpostorAmount)
		return State.ImpostorCount;
	if (options.GetGameMode() == GameModes__Enum::HideNSeek)
		return 1;
	if (playerAmount >= 9)
		return 3;
	if (playerAmount >= 7)
		return 2;
	return 1;
}

int GenerateRandomNumber(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

Vector2 GetTrueAdjustedPosition(PlayerControl* playerControl)
{
	Vector2 playerVector2 = PlayerControl_GetTruePosition(playerControl, NULL);
	playerVector2.y += 0.36f;
	return playerVector2;
}

#pragma region PlayerSelection
PlayerSelection::PlayerSelection() noexcept
{
	this->reset();
}

PlayerSelection::PlayerSelection(const PlayerControl* playerControl) {
	if (Object_1_IsNotNull((Object_1*)playerControl)) {
		this->clientId = playerControl->fields._.OwnerId;
		this->playerId = playerControl->fields.PlayerId;
	}
	else {
		this->reset();
	}
}

PlayerSelection::PlayerSelection(GameData_PlayerInfo* playerData) {
	new (this)PlayerSelection(app::GameData_PlayerInfo_get_Object(playerData, nullptr));
}

PlayerSelection::PlayerSelection(const PlayerSelection::Result& result) {
	new (this)PlayerSelection(result.has_value() ? result.get_PlayerControl() : nullptr);
}

PlayerSelection::Result PlayerSelection::validate() {
	auto playerControl = this->get_PlayerControl();
	if (playerControl) {
		auto playerData = app::PlayerControl_get_Data((*playerControl), nullptr);
		if (playerData) {
			return { (*playerControl), playerData };
		}
	}
	this->reset();
	return {};
}

bool PlayerSelection::equals(const PlayerSelection& selectedPlayer) const
{
	if (this == &selectedPlayer) return true;
	if (!this->has_value() || !selectedPlayer.has_value()) return false;
	return std::tie(clientId, playerId) == std::tie(selectedPlayer.clientId, selectedPlayer.playerId);
}

bool PlayerSelection::equals(const PlayerSelection::Result& selectedPlayer) const {
	if (!this->has_value() || !selectedPlayer.has_value()) return false;
	if (clientId == Game::HostInherit) {
		return playerId == selectedPlayer.get_PlayerControl()->fields.PlayerId;
	}
	return std::tie(clientId, playerId) ==
		std::tie(selectedPlayer.get_PlayerControl()->fields._.OwnerId,
			selectedPlayer.get_PlayerControl()->fields.PlayerId);
}

std::optional<PlayerControl*> PlayerSelection::get_PlayerControl() const {
	if (!this->has_value())
		return std::nullopt;

	if (clientId == Game::HostInherit) {
		auto playerControl = GetPlayerControlById(this->playerId);
		if (Object_1_IsNotNull((Object_1*)playerControl))
			return playerControl;
#if _DEBUG
		if (playerControl) {
			// oops: game bug
			STREAM_ERROR(ToString(playerControl) << " playerControl is invalid");
		}
#endif
	}

	for (auto client : GetAllClients()) {
		if (client->fields.Id == this->clientId) {
			if (auto playerControl = client->fields.Character;
				Object_1_IsNotNull((Object_1*)playerControl)) {
				return playerControl;
			}
#if _DEBUG
			if (client->fields.Character) {
				// oops: game bug
				STREAM_ERROR(ToString(client->fields.Character) << " Character is invalid");
			}
#endif
			return std::nullopt;
		}
	}

	return std::nullopt;
}

std::optional<GameData_PlayerInfo*> PlayerSelection::get_PlayerData() const
{
	if (auto data = GetPlayerData(this->get_PlayerControl().value_or(nullptr));
		data != nullptr) {
		return data;
	}
	return std::nullopt;
	}
#pragma endregion

ImVec4 AmongUsColorToImVec4(const Color& color) {
	return ImVec4(color.r, color.g, color.b, color.a);
}

ImVec4 AmongUsColorToImVec4(const Color32& color) {
	static_assert(offsetof(Color32, a) + sizeof(Color32::a) == sizeof(Color32::rgba), "Color32 must be defined as union");
	return ImVec4(color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F);
}

#define LocalInGame (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define LocalInLobby (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Joined))
#define OnlineInGame (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define OnlineInLobby (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Joined))
#define TutorialScene (State.CurrentScene.compare("Tutorial") == 0)

bool IsInLobby() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInLobby || OnlineInLobby) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsHost() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	return app::InnerNetClient_get_AmHost((InnerNetClient*)(*Game::pAmongUsClient), NULL);
}

bool IsInGame() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInGame || OnlineInGame || TutorialScene) && Object_1_IsNotNull((Object_1*)*Game::pShipStatus) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsInMultiplayerGame() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInGame || OnlineInGame) && Object_1_IsNotNull((Object_1*)*Game::pShipStatus) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsColorBlindMode() {
	if (auto settings = DataManager_get_Settings(nullptr)) {
		if (auto accessibility = SettingsData_get_Accessibility(settings, nullptr)) {
			return AccessibilitySettingsData_get_ColorBlindMode(accessibility, nullptr);
		}
	}
	return false;
}

bool IsStreamerMode() {
	if (auto settings = DataManager_get_Settings(nullptr)) {
		if (auto gameplay = SettingsData_get_Gameplay(settings, nullptr)) {
			return GameplaySettingsData_get_StreamerMode(gameplay, nullptr);
		}
	}
	return false;
}

std::string GetHostUsername(bool colored) {
	if (IsInGame() || IsInLobby() && !colored)
		return convert_from_string(InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.PlayerName);
	if (IsInGame() || IsInLobby()) {
		Color32 color = GetPlayerColor(GetPlayerOutfit(GetPlayerData(InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.Character))->fields.ColorId);
		std::string username = convert_from_string(InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.PlayerName);
		return std::format("<#{:02x}{:02x}{:02x}>{}</color>", color.r, color.g, color.b, RemoveHtmlTags(username));
	}
	return "";
}

std::string RemoveHtmlTags(std::string html_str) {
	std::regex tags("<[^>]*>");
	std::string remove{};
	return std::regex_replace(html_str, tags, remove);
}

bool IsNameValid(std::string str) {
	if (str == "") return false;
	if (str.length() > 12) return false;
	if (str.find("<") != std::string::npos || str.find(">") != std::string::npos || str.find("=") != std::string::npos) return false;
	return true;
}


GameData_PlayerInfo* GetPlayerData(PlayerControl* player) {
	if (player) return app::PlayerControl_get_Data(player, NULL);
	return NULL;
}

GameData_PlayerInfo* GetPlayerDataById(Game::PlayerId id) {
	return app::GameData_GetPlayerById((*Game::pGameData), id, NULL);
}

PlayerControl* GetPlayerControlById(Game::PlayerId id) {
	for (auto player : GetAllPlayerControl()) {
		if (player->fields.PlayerId == id) return player;
	}

	return NULL;
}

bool IsColorAvailable(int colorId) {
	for (auto player : GetAllPlayerData()) {
		if (GetPlayerOutfit(player)->fields.ColorId = colorId) {
			return false;
			break;
		}
	}
	return true;
}

std::string GenerateRandomString(bool completelyRandom) {
	if (completelyRandom) {
		std::string allowedChars = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		int outputLength = randi(0, 9) % 10 + 1;

		int randomIndex;
		std::string outputString = "";

		for (int i = 0; i < outputLength; ++i) {
			randomIndex = rand() % (allowedChars.length() - 1);
			outputString += allowedChars[randomIndex];
		}
		return outputString;
	}
	else {
		std::vector<std::string> threeLetters = { "ace", "ado", "age", "air", "ant", "apt", "art", "awe", "axe", "bag", "bat", "bay", "bay", "bee", "big", "bin", "bow", "bud", "bug", "bus", "bye", "cab", "can", "car", "cat", "cod", "cos", "cow", "coy", "cub", "cud", "cue", "dam", "day", "den", "dew", "dim", "dot", "due", "due", "dun", "ebb", "egg", "elf", "far", "fax", "fee", "few", "fey", "fin", "fir", "fit", "fly", "fog", "fox", "fun", "fur", "gap", "gen", "gig", "gnu", "gun", "gym", "hay", "hen", "hod", "hue", "ice", "ink", "inn", "jam", "jar", "jet", "jib", "jog", "joy", "key", "key", "kin", "kit", "kop", "lap", "lea", "lid", "lip", "lot", "lug", "map", "mid", "mop", "mud", "net", "net", "new", "nib", "nil", "nth", "oak", "oar", "oil", "one", "one", "ore", "our", "own", "pad", "pan", "pea", "pen", "pie", "pin", "pip", "pit", "pod", "pug", "pun", "pup", "rag", "ray", "ria", "rib", "rug", "saw", "sea", "set", "set", "she", "shy", "spa", "spy", "sty", "sum", "sun", "sup", "tab", "tag", "tan", "tap", "tax", "tea", "tee", "ten", "tie", "tin", "tip", "toy", "tub", "use", "vac", "van", "vet", "wad", "wax", "web", "wig", "wit", "wok", "wry", "yea", "yen", "yon", "zoo" };
		std::vector<std::string> fourLetters = { "able", "aged", "agog", "aide", "airy", "ajar", "akin", "ammo", "apex", "arch", "arch", "arty", "ashy", "atom", "auto", "avid", "away", "awed", "baby", "band", "bank", "bark", "barn", "base", "base", "bass", "bass", "bath", "bead", "beam", "bean", "bear", "beef", "bend", "best", "bevy", "bike", "bill", "bine", "blog", "blot", "blue", "blur", "boar", "bold", "bold", "bolt", "book", "boot", "born", "boss", "both", "bowl", "boxy", "brag", "brim", "buff", "bulb", "bump", "bunk", "burr", "busy", "cafe", "cake", "calf", "calm", "cane", "cape", "card", "care", "carp", "cart", "case", "cash", "cask", "cave", "cell", "cent", "chic", "chin", "chip", "chop", "city", "clad", "claw", "clay", "clef", "clip", "clod", "clog", "club", "clue", "coal", "coat", "coda", "code", "coin", "colt", "comb", "cook", "cool", "copy", "cord", "core", "cork", "corn", "cosy", "crab", "crew", "crib", "crop", "crow", "cube", "cult", "curd", "curl", "dame", "damp", "dark", "dart", "dash", "dawn", "dear", "deep", "deer", "deft", "desk", "dhal", "dhow", "dial", "dice", "diet", "disc", "dish", "doer", "doll", "dome", "done", "door", "dove", "dray", "drop", "drum", "dual", "duck", "duct", "dusk", "each", "east", "east", "easy", "echo", "ecru", "edge", "edgy", "envy", "epic", "euro", "even", "ewer", "exam", "exit", "fain", "fair", "fair", "fall", "fare", "farm", "fast", "faun", "fawn", "feet", "fell", "fern", "fife", "file", "film", "fine", "fire", "firm", "fish", "five", "flag", "flat", "flax", "flea", "flex", "flit", "flue", "flux", "foal", "foam", "fond", "font", "food", "fore", "form", "foxy", "free", "fuse", "fuss", "gaff", "gala", "gale", "game", "game", "gamy", "gaol", "gate", "germ", "ghat", "gill", "gilt", "glad", "glue", "goal", "goat", "gold", "gold", "gone", "good", "gram", "grey", "grid", "grub", "gulf", "gull", "gust", "hair", "hale", "half", "half", "hall", "hare", "hazy", "heap", "heat", "herd", "hero", "hewn", "hill", "hind", "hive", "home", "home", "hood", "hoof", "hoop", "hour", "huge", "hunt", "iced", "idea", "inch", "inky", "iron", "item", "jail", "joke", "just", "kame", "keel", "keen", "keep", "kelp", "kerb", "king", "kite", "knee", "knot", "kohl", "lace", "lacy", "lamb", "lamp", "lane", "late", "lava", "lawn", "laze", "lead", "leaf", "lean", "left", "lens", "life", "like", "limb", "line", "link", "lino", "lion", "live", "load", "loaf", "loan", "loch", "loft", "logo", "lone", "long", "look", "loop", "lord", "lost", "loud", "luck", "lure", "lush", "mail", "mall", "mane", "many", "mast", "maze", "meal", "meet", "mega", "menu", "mere", "mews", "mice", "mike", "mild", "mill", "mime", "mind", "mine", "mine", "mini", "mint", "mint", "mire", "mitt", "mole", "mood", "moon", "moor", "more", "moss", "most", "much", "musk", "myth", "name", "nave", "navy", "neap", "near", "neat", "neck", "need", "nest", "news", "next", "nice", "nosh", "note", "noun", "nova", "nowt", "null", "numb", "oast", "odds", "ogee", "once", "only", "open", "open", "oval", "oval", "over", "pace", "page", "pail", "pair", "pall", "palm", "park", "part", "past", "past", "path", "pawl", "peak", "peak", "pear", "peel", "pile", "pill", "pink", "pins", "pith", "pity", "plan", "plot", "plum", "plus", "plus", "poem", "poet", "pony", "pool", "pore", "port", "posh", "pout", "pram", "prey", "prim", "prow", "puce", "pure", "purr", "quay", "quin", "quip", "quiz", "raft", "rail", "rain", "rake", "ramp", "rare", "reed", "rent", "rest", "rich", "rife", "ripe", "rise", "road", "roan", "roof", "rope", "rose", "rose", "rosy", "ruby", "ruff", "rule", "rung", "rust", "safe", "saga", "sage", "sail", "sake", "sale", "salt", "salt", "same", "sand", "sane", "save", "scar", "seal", "seam", "seer", "sett", "shed", "ship", "shoe", "shop", "shot", "show", "side", "sign", "silk", "sine", "sink", "site", "size", "skew", "skip", "slab", "sloe", "slow", "slub", "snap", "snow", "snub", "snug", "sock", "sofa", "soil", "sole", "sole", "solo", "some", "song", "soup", "spam", "span", "spar", "spot", "spry", "stag", "star", "stem", "such", "suet", "sure", "swan", "swap", "tale", "tall", "tame", "tank", "tape", "task", "taut", "taxi", "team", "tear", "teat", "tent", "term", "test", "text", "then", "thud", "tick", "tide", "tidy", "tile", "till", "time", "tiny", "toad", "tofu", "toga", "toil", "tomb", "tour", "town", "trad", "tram", "trap", "tray", "trio", "true", "trug", "tsar", "tube", "tuna", "tune", "turf", "turn", "tusk", "twee", "twig", "twin", "twin", "type", "tyre", "unit", "used", "vase", "vast", "veal", "veil", "very", "vest", "view", "vote", "wail", "wall", "wand", "ward", "warm", "wary", "wasp", "wave", "wavy", "waxy", "week", "weir", "well", "well", "west", "west", "whey", "whim", "whip", "wide", "wild", "wile", "will", "wily", "wind", "wing", "wipe", "wire", "wise", "wise", "wish", "wont", "wont", "wool", "worn", "wove", "wren", "yawl", "yawn", "year", "yoke", "yolk", "zany", "zany", "zing" };
		std::vector<std::string> fiveLetters = { "ackee", "actor", "acute", "adept", "afoot", "agile", "aglow", "alarm", "album", "alert", "alike", "alive", "alkyl", "alkyl", "alloy", "alone", "alpha", "alpha", "amber", "amber", "ample", "angle", "apple", "apron", "arena", "argon", "arrow", "aside", "astir", "atlas", "attic", "audio", "aunty", "avail", "awake", "award", "aware", "awash", "axial", "azure", "badge", "baggy", "balmy", "barge", "basal", "basic", "basin", "basis", "baths", "baton", "baulk", "beach", "beads", "beady", "beefy", "beery", "beige", "bench", "berry", "bhaji", "bidet", "bijou", "bitty", "blank", "blase", "blaze", "bling", "bliss", "bliss", "block", "bloke", "blond", "blues", "blurb", "board", "bonny", "bonus", "booth", "boric", "bound", "bower", "brake", "brass", "brass", "brave", "break", "bream", "bride", "brief", "briny", "brisk", "broad", "broom", "brown", "brown", "bugle", "built", "bulky", "bumpy", "bunch", "cabin", "cable", "cairn", "calyx", "canny", "canoe", "canto", "caret", "cargo", "chain", "chalk", "charm", "chart", "chary", "chess", "chest", "chewy", "chief", "chief", "chill", "chine", "chive", "choir", "chump", "cinch", "civic", "civil", "claim", "clank", "class", "clear", "clerk", "cliff", "cloak", "clock", "close", "cloth", "cloud", "clove", "clump", "coach", "coast", "cocoa", "combe", "comfy", "comic", "comic", "comma", "conic", "coomb", "copse", "coral", "coral", "corps", "court", "coven", "cover", "crane", "crate", "crisp", "crisp", "croak", "crony", "crowd", "crown", "crumb", "crust", "cubic", "curly", "curve", "daily", "dairy", "dairy", "daisy", "dance", "dazed", "delta", "demob", "denim", "diary", "digit", "diner", "dinky", "disco", "ditch", "diver", "divot", "dizzy", "dodge", "domed", "doubt", "dozen", "draft", "drain", "drama", "drawl", "drawn", "dream", "dress", "dried", "drier", "drill", "drink", "drive", "droll", "drone", "duple", "dusky", "dusty", "eager", "eagle", "early", "eater", "elder", "elect", "elfin", "elite", "email", "envoy", "epoch", "equal", "error", "ether", "ethic", "event", "every", "exact", "extra", "facet", "faint", "famed", "fancy", "farad", "fated", "feast", "fence", "ferny", "ferry", "fever", "fibre", "fiery", "filmy", "final", "finch", "fishy", "fizzy", "flash", "flash", "flask", "fleet", "fleet", "flick", "flies", "flock", "flood", "floor", "flour", "fluid", "fluid", "flush", "flute", "focal", "focus", "foggy", "force", "forge", "forty", "fount", "frame", "frank", "fresh", "front", "frost", "frown", "funny", "furry", "furze", "futon", "fuzzy", "gable", "gamma", "gamut", "gauzy", "gecko", "ghost", "giant", "giant", "giddy", "given", "glace", "glass", "glaze", "gleam", "globe", "glory", "glove", "gluey", "going", "goods", "goody", "gooey", "goose", "gorse", "gouge", "gourd", "grace", "grain", "grand", "grand", "grape", "graph", "grasp", "great", "green", "groat", "group", "grown", "guard", "guest", "guide", "guise", "gummy", "gusty", "hanky", "happy", "hardy", "hasty", "heads", "heaps", "heavy", "hedge", "hefty", "helix", "herby", "hertz", "hewer", "hilly", "hinge", "hobby", "holey", "homey", "honey", "hoppy", "hotel", "humid", "husky", "husky", "hutch", "hyena", "icing", "ideal", "image", "imago", "index", "inner", "ionic", "irons", "ivory", "jacks", "jaggy", "jammy", "jazzy", "jeans", "jelly", "jewel", "jokey", "jolly", "juice", "jumbo", "jumbo", "jumpy", "kazoo", "khaki", "kiosk", "knife", "knurl", "koala", "label", "laird", "large", "larky", "larva", "laser", "lasso", "latex", "lathe", "latte", "layer", "leafy", "leaky", "least", "ledge", "leech", "leggy", "lemon", "lento", "level", "level", "lever", "lilac", "limit", "linen", "liner", "litre", "loads", "loamy", "local", "lofty", "logic", "lolly", "loose", "lorry", "loser", "lotto", "lower", "lucid", "lucky", "lunar", "lunch", "lupin", "lyric", "lyric", "magic", "magic", "major", "malty", "mango", "marly", "marsh", "maser", "match", "matey", "maths", "mauve", "mayor", "mealy", "meaty", "medal", "media", "mercy", "merry", "metal", "metal", "meter", "metre", "micro", "miner", "minty", "misty", "mixed", "mixer", "modal", "model", "model", "molar", "month", "moral", "moral", "motel", "motet", "mothy", "motor", "motor", "motte", "mould", "mouse", "mousy", "mouth", "movie", "muddy", "mulch", "mural", "music", "musty", "muted", "natty", "naval", "navvy", "newel", "newsy", "nifty", "night", "ninja", "noble", "noise", "nomad", "north", "north", "notch", "noted", "novel", "novel", "oaken", "ocean", "olden", "olive", "onion", "onset", "orbit", "order", "other", "outer", "outer", "overt", "owing", "oxide", "ozone", "pacer", "pager", "paint", "pally", "palmy", "panda", "paper", "party", "pasty", "patch", "pause", "peace", "peach", "peaky", "pearl", "pearl", "peaty", "peeve", "pence", "penny", "perch", "perky", "petal", "phone", "photo", "piano", "pilot", "pitch", "pithy", "piton", "place", "plain", "plain", "plane", "plank", "plant", "plumy", "plush", "point", "polar", "polka", "porch", "posse", "pouch", "pound", "pouty", "power", "prank", "prawn", "price", "pride", "prime", "prime", "prior", "prism", "privy", "prize", "prize", "prone", "proof", "proof", "prose", "proud", "pulpy", "pupal", "pupil", "puppy", "puree", "purse", "quark", "quart", "query", "quest", "quick", "quiet", "quill", "quilt", "quirk", "quits", "radar", "radio", "radio", "rainy", "rally", "ranch", "range", "rapid", "raven", "razor", "ready", "recap", "redox", "reedy", "regal", "reign", "relay", "remit", "reply", "resit", "retro", "rhyme", "rider", "ridge", "rifle", "right", "rigid", "rimed", "risky", "river", "roast", "robin", "robot", "rocky", "rooms", "roomy", "roost", "round", "route", "royal", "royal", "ruler", "runic", "rural", "rusty", "sable", "salad", "salon", "sassy", "sated", "satin", "saute", "scale", "scaly", "scant", "scarf", "scent", "scoop", "scope", "scrub", "scuff", "sedge", "senna", "sense", "sepia", "seven", "shade", "shaky", "shale", "shame", "shank", "shape", "shark", "sharp", "sheer", "sheet", "shelf", "shell", "shiny", "shirt", "shoal", "shock", "shore", "short", "shrug", "shtum", "sieve", "sight", "silky", "silty", "sixer", "skate", "skill", "skirl", "slang", "slaty", "sleek", "sleet", "slice", "slide", "slime", "small", "smart", "smelt", "smoke", "smoky", "snack", "snail", "snake", "snare", "sniff", "snore", "snowy", "solar", "solid", "solid", "sonic", "soppy", "sorry", "sound", "sound", "soupy", "south", "south", "space", "spare", "spark", "spate", "spawn", "spear", "spent", "spicy", "spiel", "spike", "spire", "spite", "splay", "spoon", "sport", "spout", "spree", "squad", "stack", "staff", "stage", "staid", "stain", "stair", "stamp", "stand", "stare", "start", "state", "state", "steak", "steam", "steel", "steep", "stern", "stick", "still", "stock", "stock", "stoic", "stone", "stony", "stool", "store", "stork", "storm", "story", "stout", "strap", "straw", "stray", "stuck", "study", "style", "suave", "sugar", "sunny", "sunup", "super", "surge", "swarm", "sweet", "sweet", "swell", "swell", "swift", "swipe", "swish", "sword", "sworn", "syrup", "table", "tacit", "tamer", "tangy", "taper", "tarry", "taste", "tawny", "tenon", "tense", "tense", "tenth", "terms", "terse", "theme", "these", "thief", "third", "thorn", "those", "three", "tiara", "tidal", "tiger", "tight", "tilde", "tiled", "tined", "tinny", "tipsy", "tired", "title", "toast", "today", "token", "tonal", "tonic", "topic", "torch", "torte", "total", "total", "towel", "tower", "trail", "train", "treat", "trial", "tribe", "trice", "trike", "trill", "trout", "truce", "truck", "trunk", "trunk", "truss", "truth", "twain", "tweak", "twine", "twirl", "uncut", "undue", "union", "upper", "urban", "usual", "utter", "vague", "valid", "value", "vegan", "verse", "video", "visit", "vista", "vital", "vocal", "voice", "vowel", "wacky", "wagon", "waist", "washy", "watch", "water", "waxen", "weave", "weber", "weeny", "weird", "whale", "wheat", "whiff", "whole", "whorl", "widow", "width", "wince", "winch", "windy", "wiper", "wispy", "witty", "woody", "wordy", "world", "worth", "wound", "wreck", "wrist", "yacht", "yogic", "young", "youth", "yummy", "zebra", "zippy", "zonal" };
		std::vector<std::string> sixLetters = { "ablaze", "access", "acting", "action", "active", "actual", "acuity", "adagio", "adroit", "adverb", "advice", "aerial", "aflame", "afloat", "agency", "airway", "alight", "allied", "allure", "amazed", "amoeba", "amount", "anchor", "annual", "annual", "answer", "apeman", "apical", "arable", "arbour", "arcane", "ardent", "ardour", "armful", "armlet", "armour", "arrant", "artful", "artist", "asleep", "aspect", "asthma", "astral", "astute", "atomic", "august", "auntie", "autumn", "avatar", "badger", "ballet", "banner", "barber", "bardic", "barley", "barrel", "basics", "basket", "bathos", "batten", "battle", "beaded", "beaked", "beaker", "bedbug", "bedsit", "beetle", "belief", "benign", "better", "billow", "binary", "bionic", "biotic", "blazon", "blithe", "blotch", "blouse", "blower", "bluish", "blurry", "bonded", "bonnet", "bonsai", "border", "botany", "bottle", "bounds", "bovine", "breach", "breath", "breeze", "breezy", "brewer", "bridge", "bright", "bronze", "brooch", "bubbly", "bubbly", "bucket", "buckle", "budget", "bumper", "bumper", "bundle", "burger", "burrow", "button", "buzzer", "bygone", "byroad", "cachet", "cactus", "camera", "campus", "canape", "candid", "candle", "canine", "canned", "canopy", "canvas", "carbon", "career", "career", "carpet", "carrot", "carton", "castle", "casual", "catchy", "catnap", "cattle", "causal", "caveat", "caviar", "celery", "cellar", "cement", "centre", "centre", "cereal", "cerise", "chalky", "chance", "chancy", "change", "chatty", "cheery", "cheese", "chilly", "chirpy", "choice", "choice", "choral", "chorus", "chummy", "chunky", "cinder", "cinema", "circle", "circus", "classy", "claves", "clayey", "clever", "clinic", "cloche", "cobweb", "cocoon", "coeval", "coffee", "coffer", "cogent", "collar", "collie", "colour", "column", "comedy", "common", "conger", "conoid", "convex", "cookie", "cooler", "coping", "copper", "copper", "cordon", "corned", "corner", "cosmic", "county", "coupon", "course", "covert", "cowboy", "coyote", "cradle", "craggy", "crayon", "creaky", "credit", "crispy", "crumby", "crunch", "cuboid", "cupola", "curacy", "cursor", "curtsy", "custom", "cyclic", "dainty", "damper", "dapper", "daring", "dative", "dazzle", "debate", "debtor", "decent", "defect", "degree", "deluxe", "demure", "denary", "desert", "desire", "detail", "device", "dexter", "diatom", "dilute", "dimple", "dinghy", "direct", "divide", "divine", "docile", "doctor", "dogged", "doodle", "dotage", "doting", "dotted", "double", "doughy", "dragon", "drapes", "drawer", "dreamy", "dressy", "dulcet", "duplex", "earthy", "earwig", "echoey", "effect", "effort", "eighty", "either", "elated", "eldest", "elfish", "elixir", "embryo", "ending", "energy", "engine", "enough", "enough", "entire", "equine", "eraser", "ermine", "errant", "ersatz", "excise", "excuse", "exempt", "exotic", "expert", "expert", "expiry", "extant", "fabled", "facile", "factor", "fallow", "family", "famous", "farmer", "fecund", "feisty", "feline", "fellow", "fencer", "ferric", "fervid", "fierce", "figure", "filial", "fillip", "finish", "finite", "fiscal", "fitful", "fitted", "flambe", "flaxen", "fleece", "fleecy", "flight", "flinty", "floral", "florid", "flossy", "floury", "flower", "fluent", "fluffy", "fodder", "foible", "folder", "folksy", "forage", "forest", "formal", "former", "fridge", "frieze", "fright", "frilly", "frizzy", "frosty", "frothy", "frozen", "frugal", "funnel", "future", "future", "gabled", "gaffer", "gaiter", "galaxy", "gallon", "galore", "gaming", "gaoler", "garage", "garden", "garlic", "gentle", "gerbil", "gifted", "giggly", "ginger", "girder", "glassy", "glider", "glitzy", "global", "glossy", "glossy", "gloved", "golden", "gopher", "gowned", "grainy", "grassy", "grater", "gratis", "gravel", "grease", "greasy", "greeny", "grilse", "gritty", "groove", "grotto", "ground", "grubby", "grungy", "guitar", "gutter", "hairdo", "haloed", "hamlet", "hammer", "hanger", "hawser", "header", "health", "helper", "hempen", "herbal", "hermit", "heroic", "hiccup", "hinder", "hinged", "homely", "homing", "honest", "hoofed", "hooked", "horsey", "hostel", "hourly", "hubbub", "huddle", "humane", "humble", "humour", "hungry", "hunted", "hunter", "hurray", "hybrid", "hyphen", "iambic", "icicle", "iconic", "iguana", "immune", "inborn", "indoor", "inland", "inmost", "innate", "inrush", "insect", "inside", "inside", "instep", "intact", "intent", "intern", "invite", "inward", "iodine", "ironic", "island", "italic", "jacket", "jagged", "jailer", "jargon", "jaunty", "jingle", "jingly", "jockey", "jocose", "jocund", "jogger", "joggle", "jovial", "joyful", "joyous", "jumble", "jumper", "jungly", "junior", "kennel", "ketone", "kettle", "kilted", "kindly", "kingly", "kirsch", "kitbag", "kitten", "knight", "ladder", "landed", "laptop", "larder", "larval", "latest", "latter", "laurel", "lavish", "lawful", "lawyer", "layman", "leaded", "leaden", "league", "ledger", "legacy", "legend", "legion", "lemony", "lender", "length", "lepton", "lessee", "lesser", "lesson", "lethal", "letter", "liable", "lidded", "likely", "limber", "limpid", "lineal", "linear", "liquid", "lissom", "listed", "litter", "little", "lively", "livery", "living", "living", "lizard", "loaded", "loafer", "locker", "locust", "logger", "lordly", "lounge", "lovely", "loving", "lugger", "lupine", "lustre", "luxury", "madcap", "magnet", "maiden", "maiden", "malted", "mammal", "manful", "manned", "manner", "mantis", "manual", "marble", "margin", "marine", "marked", "market", "maroon", "marshy", "mascot", "massif", "matrix", "matted", "matter", "mature", "meadow", "medial", "median", "medium", "memory", "merest", "meteor", "method", "metric", "mickle", "mickle", "midday", "middle", "middle", "mighty", "milieu", "minded", "minute", "minute", "mirror", "missus", "moated", "mobile", "modern", "modest", "modish", "module", "mohair", "molten", "moment", "mosaic", "motion", "motive", "motive", "motley", "moving", "muckle", "mucous", "muddle", "mulish", "mulled", "mullet", "museum", "mutiny", "mutton", "mutual", "muzzle", "myopia", "myriad", "myriad", "mystic", "mythic", "nachos", "narrow", "nation", "native", "natter", "nature", "nearby", "nether", "nettle", "neuter", "newish", "nimble", "nobody", "normal", "notice", "nought", "number", "object", "oblate", "oblong", "oblong", "occult", "octane", "ocular", "oddity", "offcut", "office", "oldish", "oniony", "online", "onrush", "onside", "onward", "opaque", "opener", "orange", "orange", "origin", "ornate", "orphan", "osprey", "outfit", "owlish", "oxtail", "oxygen", "packed", "packet", "palace", "paltry", "papery", "parade", "parcel", "parody", "parrot", "patchy", "patent", "pathos", "pavane", "peachy", "peaked", "peanut", "pebble", "pebbly", "pedlar", "people", "pepper", "petite", "petrol", "phrase", "picker", "picket", "pickle", "picnic", "pigeon", "pillar", "pillow", "pimple", "pimply", "pincer", "pinion", "piping", "pitted", "placid", "planar", "planet", "plaque", "plenty", "pliant", "plucky", "plumed", "plummy", "plunge", "plural", "plural", "plushy", "pocked", "pocket", "pocket", "poetic", "poetry", "poised", "polite", "pollen", "porous", "postal", "poster", "potato", "potted", "pounce", "powder", "precis", "prefix", "pretty", "pricey", "primal", "profit", "prompt", "proper", "proven", "public", "puddle", "pulley", "pulsar", "punchy", "puppet", "purism", "purist", "purple", "purply", "puzzle", "quaint", "quango", "quasar", "quirky", "rabbit", "racing", "racket", "radial", "radius", "raffia", "raffle", "ragged", "raging", "raglan", "raglan", "ragtag", "raisin", "rammer", "ramrod", "random", "rapper", "raring", "rarity", "rasher", "rating", "ration", "rattle", "ravine", "raving", "reason", "rebate", "recent", "recess", "recipe", "record", "record", "redial", "reform", "regent", "region", "relief", "relish", "remark", "remiss", "remote", "rennet", "rennin", "repair", "report", "rested", "result", "retort", "revamp", "reward", "rhythm", "ribbon", "ridden", "riddle", "ridged", "ripple", "rising", "robust", "rocket", "rodent", "rotary", "rotund", "roving", "rubble", "ruched", "rudder", "rueful", "rugged", "rugger", "rumour", "rumpus", "runway", "russet", "rustic", "rustle", "rutted", "saddle", "saithe", "saline", "salmon", "sample", "sandal", "sateen", "satiny", "saucer", "saving", "sawfly", "scalar", "scalar", "scales", "scarab", "scarce", "scenic", "scheme", "school", "schtum", "scorer", "scrawl", "screen", "script", "scurfy", "season", "seated", "second", "secret", "secret", "secure", "sedate", "seemly", "select", "senior", "sensor", "septet", "serene", "serial", "series", "settee", "setter", "severe", "shaper", "sharer", "sheeny", "shield", "shiner", "shorts", "shovel", "shower", "shrewd", "shrill", "shrimp", "signal", "signal", "signet", "silage", "silent", "silken", "silver", "silver", "simian", "simile", "simper", "simple", "sinewy", "single", "sinter", "sister", "sketch", "slangy", "sledge", "sleepy", "sleety", "sleeve", "sleigh", "slight", "slinky", "slippy", "sluice", "slushy", "smooth", "smudge", "smudgy", "snaggy", "snazzy", "snoopy", "snoozy", "social", "socket", "sodium", "softie", "solemn", "solids", "sonnet", "source", "sparky", "speech", "speedy", "sphere", "sphinx", "spider", "spinet", "spiral", "spiral", "spooky", "sporty", "spotty", "sprain", "sprawl", "spring", "spruce", "sprung", "square", "square", "squash", "squish", "stable", "stagey", "stamen", "staple", "staple", "starch", "starry", "static", "statue", "steady", "steely", "stereo", "stereo", "stocks", "stocky", "stolid", "stormy", "streak", "stride", "string", "stripe", "stripy", "stroll", "strong", "stubby", "studio", "sturdy", "subtle", "suburb", "subway", "sudden", "suffix", "sugary", "sulpha", "summer", "sundry", "sunken", "sunlit", "sunset", "superb", "supine", "supper", "supply", "supply", "surfer", "surtax", "survey", "swampy", "swanky", "sweaty", "switch", "swivel", "sylvan", "symbol", "syntax", "syrupy", "tablet", "taking", "talent", "talker", "tangle", "tanker", "tannic", "target", "tartan", "taster", "tavern", "teacup", "teapot", "teasel", "temper", "tennis", "tester", "tether", "thesis", "thirty", "thrill", "throes", "throne", "ticker", "ticket", "tiddly", "tiered", "tights", "timber", "timely", "tinker", "tinned", "tinted", "tipped", "tipple", "tiptop", "tissue", "titchy", "titled", "tomato", "tracer", "trader", "treaty", "treble", "tremor", "trendy", "tricky", "triple", "troops", "trophy", "trough", "truant", "trusty", "tucker", "tufted", "tundra", "tunnel", "turbid", "turkey", "turtle", "tussle", "twirly", "twisty", "umlaut", "unable", "unborn", "undone", "uneven", "unique", "unlike", "unmade", "unpaid", "unread", "unreal", "unsaid", "unseen", "unsold", "untold", "unused", "unwary", "unworn", "upbeat", "uphill", "upland", "uproar", "uptake", "upward", "upwind", "urbane", "urchin", "urgent", "usable", "useful", "utmost", "valley", "vapour", "varied", "veggie", "veiled", "veined", "velour", "velvet", "verbal", "verity", "vernal", "versed", "vertex", "vessel", "viable", "vinous", "violet", "violin", "visage", "viscid", "visual", "volume", "voyage", "waders", "waggle", "waiter", "waiver", "waking", "wallet", "wallop", "walrus", "wanted", "warble", "warder", "wealth", "wearer", "webbed", "webcam", "wedded", "weevil", "wheezy", "whippy", "wicker", "wifely", "wilful", "window", "winged", "winger", "winner", "winter", "wintry", "witted", "wizard", "wobbly", "wonder", "wonted", "wooded", "woolly", "woolly", "worthy", "wreath", "wrench", "yarrow", "yearly", "yellow", "yonder", "zapper", "zenith", "zigzag", "zigzag", "zircon", "zither" };
		std::vector<std::string> sevenLetters = { "abiding", "ability", "abiotic", "absence", "account", "acidity", "acrobat", "acrylic", "actress", "actuary", "adamant", "addenda", "address", "advance", "aerated", "aerobic", "affable", "ageless", "airport", "alcopop", "alleged", "amazing", "ambient", "amenity", "amiable", "amusing", "anaemia", "ancient", "angelic", "angling", "angular", "animate", "animism", "aniseed", "annular", "annulus", "anodyne", "antacid", "anthill", "antique", "antique", "antonym", "aplenty", "apology", "apparel", "applied", "apropos", "aquatic", "aqueous", "arbiter", "archaic", "article", "ascetic", "aseptic", "assured", "athlete", "attache", "audible", "aureole", "autocue", "average", "avidity", "awesome", "bagpipe", "balcony", "balloon", "bandsaw", "banquet", "bargain", "baronet", "barrage", "bassist", "battery", "beeline", "belated", "beloved", "bemused", "bequest", "bespoke", "betters", "bicycle", "billion", "binding", "biology", "biscuit", "bismuth", "bivalve", "blanket", "blanket", "blatant", "blessed", "blister", "blogger", "blossom", "blowfly", "blurred", "bonfire", "bookish", "boracic", "boulder", "boxroom", "boycott", "boyhood", "bracket", "bravery", "breaded", "breadth", "breathy", "brimful", "brisket", "bristly", "brittle", "bromide", "brother", "buckram", "bucolic", "budding", "builder", "bulrush", "bulwark", "buoyant", "burning", "bursary", "butcher", "buzzard", "cabaret", "cadence", "cadenza", "caisson", "calends", "calorie", "candied", "cannery", "capable", "capital", "capital", "captain", "caption", "capture", "caravan", "caraway", "carbide", "careful", "carmine", "carnage", "cartoon", "carving", "cashier", "cavalry", "ceiling", "centaur", "central", "centric", "century", "ceramic", "certain", "cession", "chamber", "channel", "chapter", "charity", "charmer", "chatter", "checked", "checker", "chemist", "chevron", "chicane", "chicken", "chimney", "chirrup", "chortle", "chuffed", "civvies", "clarion", "classic", "classic", "clastic", "cleaver", "clement", "climate", "clinker", "cluster", "clutter", "coastal", "coating", "coaxial", "cobbled", "coequal", "cognate", "coldish", "collage", "college", "comical", "commune", "compact", "compact", "company", "compass", "complex", "concave", "concert", "concise", "conduit", "conical", "content", "contest", "control", "convert", "cooking", "coolant", "copious", "copycat", "cordial", "coronet", "correct", "council", "counter", "counter", "country", "courage", "courtly", "crackle", "crawler", "crested", "crimson", "crinkly", "croquet", "crucial", "crumbly", "crunchy", "cryptic", "crystal", "crystal", "culvert", "cunning", "cunning", "cupcake", "curator", "curious", "currant", "current", "curried", "cursive", "cursive", "cursory", "curtain", "cushion", "customs", "cutaway", "cutback", "cutlass", "cutlery", "cutting", "cutting", "cyclist", "dabbler", "dancing", "dappled", "darling", "dashing", "dawning", "deadpan", "decagon", "decided", "decimal", "decimal", "decoder", "defiant", "deltaic", "denizen", "dentist", "dervish", "desktop", "desktop", "dessert", "devoted", "devotee", "diagram", "diamond", "diamond", "dietary", "diffuse", "digital", "dignity", "dioxide", "diploid", "diploma", "display", "distant", "disused", "diurnal", "diverse", "divided", "dolphin", "donnish", "dormant", "doughty", "drachma", "drastic", "draught", "drawing", "dresser", "dribble", "driving", "drought", "drummer", "duality", "ductile", "dungeon", "duopoly", "durable", "dustbin", "dutiful", "dynamic", "dynasty", "earmark", "earnest", "earplug", "earring", "earshot", "earthen", "earthly", "eastern", "easting", "eclipse", "economy", "edaphic", "egghead", "elastic", "elastic", "elderly", "elegant", "elegiac", "ellipse", "elusive", "emerald", "emerald", "eminent", "emirate", "emotive", "empties", "endemic", "endless", "engaged", "enquiry", "ensuing", "epicure", "epigeal", "episode", "epitome", "equable", "equator", "equerry", "erosive", "erudite", "eternal", "ethical", "evasive", "evening", "evident", "exalted", "example", "excited", "exhaust", "exigent", "expanse", "express", "extreme", "factual", "fairing", "fancier", "fantasy", "faraway", "fashion", "feather", "feature", "federal", "feeling", "felspar", "ferrety", "ferrous", "ferrule", "fervent", "festive", "fibrous", "fiction", "fighter", "figment", "filings", "finicky", "fishnet", "fissile", "fission", "fitting", "fixated", "fixture", "flannel", "flavour", "flecked", "fledged", "flighty", "flouncy", "flowery", "fluency", "fluster", "fluvial", "foliage", "foliate", "footing", "footman", "forfeit", "fortune", "forward", "forward", "fragile", "freckly", "freebie", "freeman", "freesia", "freezer", "fretted", "friable", "frilled", "fringed", "frosted", "frowsty", "fulsome", "furcate", "furlong", "furrier", "further", "furtive", "fusible", "fusilli", "gainful", "gallant", "gallery", "gamelan", "garbled", "garnish", "gavotte", "gazette", "gearbox", "general", "genteel", "genuine", "germane", "getaway", "gherkin", "gibbous", "gingery", "giraffe", "girlish", "glaring", "gleeful", "glimmer", "glowing", "gnomish", "goggles", "gorilla", "gradual", "grammar", "grandam", "grandee", "graphic", "grating", "gravity", "greatly", "greyish", "greylag", "gristly", "grocery", "grommet", "grooved", "gryphon", "guarded", "guising", "gushing", "gymnast", "habitat", "hafnium", "halcyon", "halfway", "hallway", "halogen", "halting", "halyard", "handbag", "harbour", "harvest", "heading", "healthy", "hearing", "heating", "helical", "helpful", "helping", "herbage", "heroics", "hexagon", "history", "hitcher", "holdall", "holiday", "holmium", "hominid", "homonym", "honeyed", "hopeful", "horizon", "hotline", "hotness", "hulking", "hunched", "hundred", "hurdler", "hurried", "hydrous", "hygiene", "idyllic", "igneous", "immense", "imprint", "inbuilt", "inexact", "infuser", "ingrown", "initial", "initial", "inkling", "inshore", "instant", "instant", "intense", "interim", "interim", "invader", "inverse", "isohyet", "isthmus", "italics", "jackpot", "jasmine", "jocular", "journal", "journey", "jubilee", "justice", "kenning", "kestrel", "keynote", "kindred", "kindred", "kinetic", "kingdom", "kinsman", "kitchen", "knowing", "knuckle", "knurled", "laconic", "lacquer", "lactose", "lagging", "lambent", "lantern", "largish", "lasting", "lateral", "lattice", "lawsuit", "layette", "leading", "leaflet", "learned", "learner", "leather", "lectern", "legible", "leisure", "lengthy", "lenient", "leonine", "leopard", "lettuce", "lexical", "liberty", "library", "lilting", "lineage", "linkage", "linkman", "lioness", "literal", "lithium", "logging", "logical", "longish", "lottery", "louvred", "lovable", "lowland", "luggage", "lyrical", "machine", "maestro", "magenta", "magenta", "magical", "magnate", "majesty", "maltose", "mammoth", "mammoth", "manners", "mansard", "marbled", "marital", "marquee", "mascara", "massive", "matinee", "matting", "mattock", "maximal", "maximum", "mayoral", "meaning", "meaning", "medical", "meeting", "melodic", "mermaid", "message", "midland", "midweek", "million", "million", "mimetic", "mindful", "mineral", "mineral", "minimal", "minimum", "minster", "missile", "missing", "mission", "mistake", "mixture", "modular", "mollusc", "moneyed", "monitor", "monthly", "moonlit", "moorhen", "morello", "morning", "mottled", "mounted", "mourner", "movable", "muddler", "muffler", "mullion", "musical", "mustard", "mustard", "nankeen", "narwhal", "natural", "nebular", "needful", "neither", "netball", "netting", "network", "newness", "nightly", "nitrous", "nomadic", "nominal", "notable", "noughth", "nuclear", "nursery", "nursing", "nurture", "obesity", "oblique", "obscure", "obvious", "oceanic", "octagon", "octopus", "offbeat", "officer", "offline", "offside", "oilcake", "ominous", "onerous", "ongoing", "onshore", "opening", "opinion", "optimal", "optimum", "opulent", "orbital", "orchard", "ordered", "orderly", "ordinal", "ordinal", "organic", "osmosis", "osmotic", "outdoor", "outline", "outside", "outside", "outsize", "outward", "overall", "overarm", "overlay", "package", "padlock", "pageant", "painter", "paisley", "palaver", "palette", "palmate", "palmtop", "panicle", "paragon", "parking", "parlous", "partial", "passage", "passing", "passive", "pastime", "pasture", "patient", "patient", "pattern", "payable", "peacock", "peckish", "pelagic", "pelisse", "penalty", "pendent", "pending", "penguin", "pension", "peppery", "perfect", "perfume", "persona", "phantom", "philtre", "phonics", "picture", "piebald", "pillbox", "pinched", "pinkish", "piquant", "pitcher", "pitfall", "pivotal", "plaster", "plastic", "plastic", "platoon", "playful", "pleased", "pleated", "plenary", "pliable", "plumber", "plunger", "podcast", "poetess", "pointed", "polemic", "politic", "popcorn", "popular", "portion", "postage", "postbox", "postern", "postman", "potable", "pottage", "pottery", "powdery", "powered", "praline", "prattle", "precise", "prefect", "premier", "present", "present", "prickle", "primary", "process", "product", "profuse", "program", "project", "pronged", "pronoun", "propane", "protean", "protein", "proverb", "proviso", "prudent", "psychic", "puckish", "pumpkin", "purpose", "puzzler", "pyjamas", "pyramid", "pyrites", "quality", "quantum", "quarter", "quavery", "queenly", "quinine", "quorate", "rabbity", "rackety", "radiant", "radical", "raffish", "rafting", "railing", "railman", "railway", "rainbow", "rambler", "ramekin", "rampant", "rarebit", "ratable", "raucous", "rawhide", "readies", "recital", "recount", "recruit", "redhead", "redwing", "referee", "refined", "regards", "regatta", "regency", "regnant", "regular", "related", "relaxed", "reliant", "remorse", "removed", "replete", "reproof", "reptile", "reputed", "respect", "restful", "restive", "rethink", "retired", "retread", "revelry", "revenge", "reverse", "rhombus", "rickety", "rimless", "ringing", "riotous", "riviera", "roaring", "robotic", "rolling", "roseate", "rounded", "rounder", "routine", "routine", "ruffled", "ruinous", "runaway", "rundown", "running", "saddler", "sailing", "salient", "salvage", "sampler", "sapient", "sardine", "saurian", "sausage", "savings", "savoury", "scarlet", "scenery", "scented", "science", "scrappy", "scratch", "scrawny", "screech", "scribal", "sealant", "searing", "seasick", "seaside", "seaward", "seaweed", "section", "secular", "seedbed", "seeming", "segment", "seismic", "sensory", "sensual", "serious", "serried", "servant", "several", "shadowy", "shapely", "shelter", "sheriff", "shivery", "shocker", "showery", "showing", "shrubby", "shudder", "shutter", "sickbay", "sidecar", "sighted", "sightly", "signing", "silvery", "similar", "sincere", "sinless", "sinuous", "sixfold", "sketchy", "skilful", "skilled", "skimmed", "skyline", "skyward", "slatted", "sleeved", "slipper", "slotted", "slowish", "slurred", "sniffle", "sniffly", "snuffly", "snuggly", "society", "soldier", "soluble", "someone", "soprano", "sorghum", "soulful", "spangle", "spangly", "spaniel", "spanner", "sparing", "sparkly", "sparrow", "spartan", "spatial", "speaker", "special", "speckle", "spidery", "spindly", "splashy", "splotch", "spotted", "springy", "spurred", "squally", "squashy", "squidgy", "squiffy", "squishy", "stadium", "standby", "standby", "stapler", "starchy", "starlit", "stately", "station", "stature", "staunch", "stealth", "stellar", "sticker", "stilted", "stoical", "strange", "stratum", "streaky", "stretch", "striker", "strings", "stringy", "striped", "stubbly", "student", "studied", "stylish", "styptic", "subject", "subject", "sublime", "success", "suiting", "sultana", "summary", "summary", "summery", "sunburn", "sundial", "sundown", "sunfish", "sunless", "sunrise", "sunroof", "support", "supreme", "surface", "surface", "surfeit", "surgery", "surmise", "surname", "surplus", "surreal", "swarthy", "swearer", "sweater", "swollen", "synapse", "synonym", "tabular", "tactful", "tactile", "tadpole", "tallish", "tangram", "tantrum", "taxable", "teacher", "telling", "tenable", "tenfold", "tensile", "ternary", "terrace", "terrain", "terrine", "testate", "textile", "textual", "texture", "theatre", "thistle", "thought", "thrifty", "through", "thrower", "thunder", "tideway", "timpani", "titanic", "titular", "toaster", "toccata", "tombola", "tonight", "toothed", "topical", "topmost", "topsoil", "torment", "tornado", "touched", "tourism", "tourist", "tracing", "tracker", "tractor", "trailer", "trainer", "trapeze", "treacly", "tremolo", "triable", "triadic", "tribune", "trickle", "trochee", "trolley", "trophic", "tropism", "trouble", "trouper", "trumpet", "tsunami", "tubular", "tumbler", "tunable", "tuneful", "twelfth", "twiddly", "twilled", "twitchy", "twofold", "typical", "umpteen", "unaided", "unarmed", "unasked", "unaware", "unbound", "unbowed", "uncanny", "undying", "unequal", "unheard", "unicorn", "unifier", "uniform", "uniform", "unitary", "unladen", "unlined", "unmoved", "unnamed", "unpaved", "unready", "untried", "unusual", "unwaged", "upfront", "upright", "upriver", "upstage", "upstate", "upswept", "useable", "utility", "utility", "valiant", "vanilla", "variant", "variety", "various", "vaulted", "vehicle", "velvety", "venison", "verbena", "verbose", "verdant", "verdict", "verdure", "vernier", "version", "vesicle", "vibrant", "victory", "vinegar", "vintage", "vintner", "virtual", "visible", "visitor", "vitamin", "vlogger", "volcano", "voltaic", "voluble", "voucher", "vulpine", "waggish", "wagtail", "wakeful", "walkout", "wallaby", "wanting", "warmish", "warrant", "washing", "waverer", "waxwing", "waxwork", "wayward", "wealthy", "wearing", "weather", "weather", "webbing", "website", "weighty", "welcome", "welcome", "western", "wetsuit", "wheaten", "wheelie", "whisker", "widower", "wildcat", "willing", "willowy", "winning", "winsome", "wishful", "wistful", "witness", "woollen", "working", "working", "worldly", "worsted", "wriggly", "wrinkle", "writing", "wrought", "zealous", "zestful" };
		
		std::map<int, std::vector<std::string>> mapper;
		mapper[3] = threeLetters; mapper[4] = fourLetters; mapper[5] = fiveLetters; mapper[6] = sixLetters; mapper[7] = sevenLetters;
		int rand1 = randi(3, 7);
		std::string st = mapper[rand1][randi(0, mapper[rand1].size() - 1)];
		int rand2 = randi(3, 10 - (int)st.length());
		st += mapper[rand2][randi(0, mapper[rand2].size() - 1)];
		st[0] = std::toupper(st[0]);
		return st;
	}
}

PlainDoor* GetPlainDoorByRoom(SystemTypes__Enum room) {
	for (auto door : il2cpp::Array((*Game::pShipStatus)->fields.AllDoors))
	{
		if (door->fields.Room == room)
		{
			return (PlainDoor*)door;
		}
	}

	return nullptr;
}

OpenableDoor* GetOpenableDoorByRoom(SystemTypes__Enum room) {
	for (auto door : il2cpp::Array((*Game::pShipStatus)->fields.AllDoors))
	{
		if (door->fields.Room == room)
		{
			return (OpenableDoor*)door;
		}
	}

	return nullptr;
}

il2cpp::Array<OpenableDoor__Array> GetAllOpenableDoors() {
	return (*Game::pShipStatus)->fields.AllDoors;
}

il2cpp::List<List_1_PlayerControl_> GetAllPlayerControl() {
	return *Game::pAllPlayerControls;
}

il2cpp::List<List_1_GameData_PlayerInfo_> GetAllPlayerData() {
	return (*Game::pGameData)->fields.AllPlayers;
}

il2cpp::Array<DeadBody__Array> GetAllDeadBodies() {
	static std::string deadBodyType = translate_type_name("DeadBody, Assembly-CSharp");

	Type* deadBody_Type = app::Type_GetType(convert_to_string(deadBodyType), NULL);
	return (DeadBody__Array*)app::Object_1_FindObjectsOfType(deadBody_Type, NULL);
}

il2cpp::List<List_1_PlayerTask_> GetPlayerTasks(PlayerControl* player) {
	return player->fields.myTasks;
}

std::vector<NormalPlayerTask*> GetNormalPlayerTasks(PlayerControl* player) {
	static std::string normalPlayerTaskType = translate_type_name("NormalPlayerTask");

	auto playerTasks = GetPlayerTasks(player);
	std::vector<NormalPlayerTask*> normalPlayerTasks;
	normalPlayerTasks.reserve(playerTasks.size());

	for (auto playerTask : playerTasks)
		if (normalPlayerTaskType == playerTask->klass->_0.name || normalPlayerTaskType == playerTask->klass->_0.parent->name)
			normalPlayerTasks.push_back((NormalPlayerTask*)playerTask);

	return normalPlayerTasks;
}

Object_1* GetSabotageTask(PlayerControl* player) {
	static std::string sabotageTaskType = translate_type_name("SabotageTask");

	auto playerTasks = GetPlayerTasks(player);

	for (auto playerTask : playerTasks)
		if (sabotageTaskType == playerTask->klass->_0.name
			|| sabotageTaskType == playerTask->klass->_0.parent->name
			|| "MushroomMixupSabotageTask"sv == playerTask->klass->_0.name)
			return (Object_1*)playerTask;

	return NULL;
}

void RepairSabotage(PlayerControl* player) {
	static std::string electricTaskType = translate_type_name("ElectricTask");
	static std::string hqHudOverrideTaskType = translate_type_name("HqHudOverrideTask");
	static std::string hudOverrideTaskType = translate_type_name("HudOverrideTask");
	static std::string noOxyTaskType = translate_type_name("NoOxyTask");
	static std::string reactorTaskType = translate_type_name("ReactorTask");

	auto sabotageTask = GetSabotageTask(player);
	if (sabotageTask == NULL) return;

	if (electricTaskType == sabotageTask->klass->_0.name) {
		auto electricTask = (ElectricTask*)sabotageTask;

		auto switchSystem = electricTask->fields.system;
		auto actualSwitches = switchSystem->fields.ActualSwitches;
		auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

		if (actualSwitches != expectedSwitches) {
			for (auto i = 0; i < 5; i++) {
				auto switchMask = 1 << (i & 0x1F);

				if ((actualSwitches & switchMask) != (expectedSwitches & switchMask))
					State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Electrical, i));
			}
		}
	}
	else if (hqHudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Comms, 16));
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Comms, 17));
	}
	else if (hudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Comms, 0));
	}
	else if (noOxyTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::LifeSupp, 64));
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::LifeSupp, 65));
	}
	else if (reactorTaskType == sabotageTask->klass->_0.name) {
		if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Reactor, 64));
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Reactor, 65));
		}

		if (State.mapType == Settings::MapType::Pb) {
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Laboratory, 64));
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Laboratory, 65));
		}
		if (State.mapType == Settings::MapType::Airship) {
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Reactor, 16));
			State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Reactor, 17));
		}
	}
	else if ("MushroomMixupSabotageTask"sv == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::MushroomMixupSabotage, 0));
	}
	else {
		STREAM_ERROR("Unknown Task:" << sabotageTask->klass->_0.name);
	}
}

void CompleteTask(NormalPlayerTask* playerTask) {
	if (playerTask->fields._._Owner_k__BackingField == (*Game::pLocalPlayer)) {
		while (playerTask->fields.taskStep < playerTask->fields.MaxStep)
			app::NormalPlayerTask_NextStep(playerTask, NULL);
	}
}

const char* TranslateTaskTypes(TaskTypes__Enum taskType) {
	static constexpr std::array TASK_TRANSLATIONS = { "Submit Scan", "Prime Shields", "Fuel Engines", "Chart Course", "Start Reactor", "Swipe Card", "Clear Asteroids", "Upload Data",
		"Inspect Sample", "Empty Chute", "Empty Garbage", "Align Engine Output", "Fix Wiring", "Calibrate Distributor", "Divert Power", "Unlock Manifolds", "Stop Reactor Meltdown",
		"Fix Lights", "Clean O2 Filter", "Fix Communications", "Restore Oxygen", "Stabilize Steering", "Assemble Artifact", "Sort Samples", "Measure Weather", "Enter ID Code",
		"Buy Beverage", "Process Data", "Run Diagnostics", "Water Plants", "Monitor Oxygen", "Store Artifacts", "Fill Canisters", "Activate Weather Nodes", "Insert Keys",
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telescope", "Record Temperature", "Reboot Wifi",
		"Polish Ruby", "Reset Breakers", "Decontaminate", "Make Burger", "Unlock Safe", "Sort Records", "Put Away Pistols", "Fix Shower", "Clean Toilet", "Dress Mannequin",
		"Pick Up Towels", "Rewind Tapes", "Start Fans", "Develop Photos", "Get Biggol Sword", "Put Away Rifles", "Stop Charles", "Clean Vent", "None", "Build Sandcastle", 
		"Cook Fish", "Collect Shells", "Lift Weights", "Roast Marshmallow", "Throw Frisbee", "Collect Samples", "Prep Vegetables", "Hoist Supplies", "Mine Ores", "Polish Gem", "Replace Parts", "Help Critter", 
		"Crank Generator", "Fix Antenna", "Find Signal", "Activate Mushroom Mixup", "Extract Fuel", "Monitor Mushroom", "Play Video Game" };
	return TASK_TRANSLATIONS.at(static_cast<size_t>(taskType));
}

const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static constexpr std::array SYSTEM_TRANSLATIONS = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room", "Vault Room", "Cockpit", "Armory", "Kitchen", "Viewing Deck",
		"Hall Of Portraits", "Cargo Bay", "Ventilation", "Showers", "Engine Room", "The Brig", "Meeting Room", "Records", "Lounge Room", "Gap Room", "Main Hall", "Medical",
		"Decontamination", "Zipline", "Mining Pit", "Dock", "Splash Zone", "Lookout", "Beach", "Highlands", "Jungle", "The Dorm", "Activate Mushroom Mixup", "Heli Sabotage" };
	return SYSTEM_TRANSLATIONS.at(static_cast<size_t>(systemType));
}

Color32 GetPlayerColor(Game::ColorId colorId) {
	il2cpp::Array colorArray = app::Palette__TypeInfo->static_fields->PlayerColors;
	if ((colorId < 0 || colorId > 17) || (size_t)colorId >= colorArray.size()) {
		// oops: game bug
		Color32 fortegreen = Color32();
		fortegreen.r = (uint8_t)38;
		fortegreen.g = (uint8_t)166;
		fortegreen.b = (uint8_t)98;
		fortegreen.a = (uint8_t)255;
		return fortegreen;
	}
	return colorArray[colorId];
}

std::filesystem::path getModulePath(HMODULE hModule) {
	TCHAR buff[MAX_PATH];
	GetModuleFileName(hModule, buff, MAX_PATH);
	return std::filesystem::path(buff);
}

std::string getGameVersion() {
	if (app::Application_get_version != nullptr)
		return convert_from_string(app::Application_get_version(NULL));
	else
		return "unavailable";
}

SystemTypes__Enum GetSystemTypes(const Vector2& vector) {
	if (*Game::pShipStatus) {
		auto shipStatus = *Game::pShipStatus;
		for (auto room : il2cpp::Array(shipStatus->fields._AllRooms_k__BackingField))
			if (room->fields.roomArea != nullptr && app::Collider2D_OverlapPoint(room->fields.roomArea, vector, NULL)) 
				return room->fields.RoomId;
	}
	return State.mapType == Settings::MapType::Fungle ? SystemTypes__Enum::Beach : SystemTypes__Enum::Outside;
}

std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<EVENT_PLAYER> GetEventPlayerControl(PlayerControl* player)
{
	GameData_PlayerInfo* playerInfo = GetPlayerData(player);

	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<Vector2> GetTargetPosition(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	auto object = GameData_PlayerInfo_get_Object(playerInfo, nullptr);
	if (!object) {
		// Likely disconnected player.
		if (playerInfo->fields.Disconnected != true)
			LOG_ERROR(ToString(playerInfo) + " _object is null");
		return std::nullopt;
	}
	return PlayerControl_GetTruePosition(object, NULL);
}

il2cpp::Array<Camera__Array> GetAllCameras() {
	int32_t cameraCount = app::Camera_get_allCamerasCount(nullptr);
	il2cpp::Array cameraArray = (Camera__Array*)il2cpp_array_new((Il2CppClass*)app::Camera__TypeInfo, cameraCount);
	int32_t returnedCount = app::Camera_GetAllCameras(cameraArray.get(), nullptr);
	assert(returnedCount == cameraCount);
	return cameraArray;
}

il2cpp::List<List_1_InnerNet_ClientData_> GetAllClients()
{
	return (*Game::pAmongUsClient)->fields._.allClients;
}

Vector2 GetSpawnLocation(Game::PlayerId playerId, int32_t numPlayer, bool initialSpawn)
{
	if (State.mapType == Settings::MapType::Ship || State.mapType != Settings::MapType::Pb || initialSpawn)
	{
		Vector2 vector = { 0, 1 };
		vector = Rotate(vector, (float)(playerId - 1) * (360.f / (float)numPlayer));
		float radius = (*Game::pShipStatus)->fields.SpawnRadius;
		vector = { vector.x * radius, vector.y * radius };
		Vector2 spawncenter = (initialSpawn ? (*Game::pShipStatus)->fields.InitialSpawnCenter : (*Game::pShipStatus)->fields.MeetingSpawnCenter);
		return { spawncenter.x + vector.x, spawncenter.y + vector.y + 0.3636f };
	}
	if (playerId < 5)
	{
		Vector2 spawncenter = (*Game::pShipStatus)->fields.MeetingSpawnCenter;
		return { (spawncenter.x + 1) * (float)playerId, spawncenter.y * (float)playerId };
	}
	Vector2 spawncenter = (*Game::pShipStatus)->fields.MeetingSpawnCenter2;
	return { (spawncenter.x + 1) * (float)(playerId - 5), spawncenter.y * (float)(playerId - 5) };
}

bool IsAirshipSpawnLocation(const Vector2& vec)
{
	return (State.mapType == Settings::MapType::Airship);
}

Vector2 Rotate(const Vector2& vec, float degrees)
{
	float f = 0.017453292f * degrees;
	float num = cos(f);
	float num2 = sin(f);
	return { vec.x * num - num2 * vec.y, vec.x * num2 + num * vec.y };
}

bool Equals(const Vector2& vec1, const Vector2& vec2) {
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

std::string ToString(Object* object) {
	std::string type = convert_from_string(Object_ToString(object, NULL));
	if (type == "System.String") {
		return convert_from_string((String*)object);
	}
	return type;
}

std::string ToString(Game::PlayerId id) {
	if (auto data = GetPlayerDataById(id))
		return ToString(data);
	return std::format("<#{}>", +id);
}

std::string ToString(__maybenull PlayerControl* player) {
	if (player) {
		if (auto data = GetPlayerData(player))
			return ToString(data);
		return std::format("<#{}>", +player->fields.PlayerId);
	}
	return "<Unknown>";
}

std::string ToString(__maybenull GameData_PlayerInfo* data) {
	if (data) {
		if (const auto outfit = GetPlayerOutfit(data))
			return std::format("<#{} {}>", +data->fields.PlayerId, convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr)));
		return std::format("<#{}>", +data->fields.PlayerId);
	}
	return "<Unknown>";
}

#define ADD_QUOTES_HELPER(s) #s
#define ADD_QUOTES(s) ADD_QUOTES_HELPER(s)

std::string GetGitCommit()
{
#ifdef GIT_CUR_COMMIT
	return ADD_QUOTES(GIT_CUR_COMMIT);
#endif
	return "unavailable";
}

std::string GetGitBranch()
{
#ifdef GIT_BRANCH
	return ADD_QUOTES(GIT_BRANCH);
#endif
	return "unavailable";
}

std::string operator*(std::string const& in, size_t m) { //python style string multiplication
	std::string ret;

	ret.reserve(in.size() * m + 1); // + 1 for null terminator

	for (size_t i = 0; i < m; i++)
		ret += in;
	return ret;
}

bool compareStrings(const std::string lhs, const std::string rhs) { //for sorting strings by length
	return lhs.length() < rhs.length();
}

void ImpersonateName(__maybenull GameData_PlayerInfo* data)
{
	if (!data) return;
	app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(data);
	if (!(IsInGame() || IsInLobby() || outfit)) return;
	const auto& playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
	//prevent anticheat detection with aum impersonation
	int fillers = 1;

	std::vector<std::string> allNames = {};
	for (auto p : GetAllPlayerData()) allNames.push_back(convert_from_string(GameData_PlayerOutfit_get_PlayerName(GetPlayerOutfit(p), nullptr)));
	std::sort(allNames.begin(), allNames.end(), compareStrings);
	for (std::string n : allNames) {
		if (n == playerName + (std::string("­") * size_t(fillers))) fillers++;
	}

	if (IsHost() || !State.SafeMode) {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(playerName + (std::string("­") * size_t(fillers))));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(playerName + (std::string("­") * size_t(fillers))));
	}
	else if (IsNameValid(playerName) && playerName.length() <= size_t(12 - fillers)) {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(playerName + "­"));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(playerName + "­"));
	}
	else {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(GenerateRandomString()));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(GenerateRandomString()));
	}
}

void ImpersonateOutfit(GameData_PlayerOutfit* outfit)
{
	if (!(IsInGame() || IsInLobby() || outfit)) return;
	
	if (IsInGame()) {
		State.rpcQueue.push(new RpcSetHat(outfit->fields.HatId));
		State.rpcQueue.push(new RpcSetVisor(outfit->fields.VisorId));
		State.rpcQueue.push(new RpcSetSkin(outfit->fields.SkinId));
		State.rpcQueue.push(new RpcSetPet(outfit->fields.PetId));
		State.rpcQueue.push(new RpcSetNamePlate(outfit->fields.NamePlateId));
	}
	else if (IsInLobby()) {
		State.lobbyRpcQueue.push(new RpcSetHat(outfit->fields.HatId));
		State.lobbyRpcQueue.push(new RpcSetVisor(outfit->fields.VisorId));
		State.lobbyRpcQueue.push(new RpcSetSkin(outfit->fields.SkinId));
		State.lobbyRpcQueue.push(new RpcSetPet(outfit->fields.PetId));
		State.lobbyRpcQueue.push(new RpcSetNamePlate(outfit->fields.NamePlateId));
	}
}

Game::ColorId GetRandomColorId()
{
	Game::ColorId colorId;
	il2cpp::Array PlayerColors = app::Palette__TypeInfo->static_fields->PlayerColors;
	assert(PlayerColors.size() > 0);
	if (IsInGame() || IsInLobby())
	{
		auto players = GetAllPlayerControl();
		std::vector<Game::ColorId> availableColors = { };
		for (size_t i = 0; i < PlayerColors.size(); i++)
		{
			bool colorAvailable = true;
			for (PlayerControl* player : players)
			{
				app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
				if (outfit == NULL) continue;
				if (i == outfit->fields.ColorId)
				{
					colorAvailable = false;
					break;
				}
			}

			if (colorAvailable)
				availableColors.push_back((Game::ColorId)i);
		}
		if (availableColors.size() > 0)
			colorId = availableColors.at(randi(0, (int)availableColors.size() - 1));
		else
			colorId = players.size(); //gives u fortegreen when all colors are taken
	}
	else
	{
		colorId = randi(0, (int)PlayerColors.size() - 1);
	}
	return colorId;
}

std::string GetGradientUsername(std::string str) {
	std::vector<int> color1 = { int(State.NameColor1.x * 255), int(State.NameColor1.y * 255), int(State.NameColor1.z * 255), int(State.NameColor1.w * 255) };
	std::vector<int> color2 = { int(State.NameColor2.x * 255), int(State.NameColor2.y * 255), int(State.NameColor2.z * 255), int(State.NameColor2.w * 255) };
	if (color1 == color2) //if user doesn't want gradients, don't cause extra lag
		return std::format("<#{:02x}{:02x}{:02x}{:02x}>{}</color>", color1[0], color1[1], color1[2], color1[3], str);
	int nameLength = int(str.length());
	if (nameLength > 1) { //fix division by zero
		float stepR = float((color2[0] - color1[0]) / (nameLength - 1));
		float stepG = float((color2[1] - color1[1]) / (nameLength - 1));
		float stepB = float((color2[2] - color1[2]) / (nameLength - 1));
		float stepA = float((color2[3] - color1[3]) / (nameLength - 1));
		std::string gradientText = "";
		for (int i = 0; i < nameLength; i++)
		{
			int r = int(color1[0] + std::round(stepR * i));
			int g = int(color1[1] + std::round(stepG * i));
			int b = int(color1[2] + std::round(stepB * i));
			int a = int(color1[3] + std::round(stepA * i));
			//names look ugly af with white strikethrough
			std::string opener = "";
			if (State.UnderlineName) opener += "<u>";
			if (State.StrikethroughName) opener += "<s>";

			std::string closer = "";
			if (State.StrikethroughName) closer += "</s>";
			if (State.UnderlineName) closer += "</u>";

			std::string colorCode = std::format("<#{:02x}{:02x}{:02x}{:02x}>", r, g, b, a);
			gradientText += colorCode + opener + str[i] + closer + "</color>";
		}

		return gradientText;
	}
	else {
		int r = int((color1[0] + color2[0]) / 2);
		int g = int((color1[1] + color2[1]) / 2);
		int b = int((color1[2] + color2[2]) / 2);
		int a = int((color1[3] + color2[3]) / 2);
		std::string colorCode = std::format("<#{:02x}{:02x}{:02x}{:02x}>", r, g, b, a);

		std::string opener = "";
		if (State.UnderlineName) opener += "<u>";
		if (State.StrikethroughName) opener += "<s>";

		std::string closer = "";
		if (State.StrikethroughName) closer += "</s>";
		if (State.UnderlineName) closer += "</u>";

		std::string gradientText = colorCode + opener + str + closer + "</color>";
		return gradientText;
	}
}

void SaveOriginalAppearance()
{
	app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
	if (outfit == NULL) return;
	LOG_DEBUG("Set appearance values to current player");
	State.originalName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
	State.originalSkin = outfit->fields.SkinId;
	State.originalHat = outfit->fields.HatId;
	State.originalPet = outfit->fields.PetId;
	State.originalColor = outfit->fields.ColorId;
	State.activeImpersonation = false;
	State.originalVisor = outfit->fields.VisorId; 
	State.originalNamePlate = outfit->fields.NamePlateId;
}

void ResetOriginalAppearance()
{
	try {
		LOG_DEBUG("Reset appearance values to invalid");
		State.originalSkin = nullptr;
		State.originalHat = nullptr;
		State.originalPet = nullptr;
		State.originalColor = Game::NoColorId;
		State.originalVisor = nullptr;
		State.originalNamePlate = nullptr;
	}
	catch (...) {
		LOG_DEBUG("Failed to reset appearance due to exception");
	}
}

void ControlAppearance(bool randomize)
{
	try {
		std::queue<RPCInterface*>* queue = nullptr;
		if (IsInGame())
			queue = &State.rpcQueue;
		else if (IsInLobby())
			queue = &State.lobbyRpcQueue;
		if (randomize) {
			std::vector availableHats = { "hat_NoHat", "hat_AbominalHat", "hat_anchor", "hat_antenna", "hat_Antenna_Black", "hat_arrowhead", "hat_Astronaut-Blue", "hat_Astronaut-Cyan", "hat_Astronaut-Orange", "hat_astronaut", "hat_axe", "hat_babybean", "hat_Baguette", "hat_BananaGreen", "hat_BananaPurple", "hat_bandanaWBY", "hat_Bandana_Blue", "hat_Bandana_Green", "hat_Bandana_Pink", "hat_Bandana_Red", "hat_Bandana_White", "hat_Bandana_Yellow", "hat_baseball_Black", "hat_baseball_Green", "hat_baseball_Lightblue", "hat_baseball_LightGreen", "hat_baseball_Lilac", "hat_baseball_Orange", "hat_baseball_Pink", "hat_baseball_Purple", "hat_baseball_Red", "hat_baseball_White", "hat_baseball_Yellow", "hat_Basketball", "hat_bat_crewcolor", "hat_bat_green", "hat_bat_ice", "hat_beachball", "hat_Beanie_Black", "hat_Beanie_Blue", "hat_Beanie_Green", "hat_Beanie_Lightblue", "hat_Beanie_LightGreen", "hat_Beanie_LightPurple", "hat_Beanie_Pink", "hat_Beanie_Purple", "hat_Beanie_White", "hat_Beanie_Yellow", "hat_bearyCold", "hat_bone", "hat_Bowlingball", "hat_brainslug", "hat_BreadLoaf", "hat_bucket", "hat_bucketHat", "hat_bushhat", "hat_Butter", "hat_caiatl", "hat_caitlin", "hat_candycorn", "hat_captain", "hat_cashHat", "hat_cat_grey", "hat_cat_orange", "hat_cat_pink", "hat_cat_snow", "hat_chalice", "hat_cheeseBleu", "hat_cheeseMoldy", "hat_cheeseSwiss", "hat_ChefWhiteBlue", "hat_cherryOrange", "hat_cherryPink", "hat_Chocolate", "hat_chocolateCandy", "hat_chocolateMatcha", "hat_chocolateVanillaStrawb", "hat_clagger", "hat_clown_purple", "hat_comper", "hat_croissant", "hat_crownBean", "hat_crownDouble", "hat_crownTall", "hat_CuppaJoe", "hat_Deitied", "hat_devilhorns_black", "hat_devilhorns_crewcolor", "hat_devilhorns_green", "hat_devilhorns_murky", "hat_devilhorns_white", "hat_devilhorns_yellow", "hat_Doc_black", "hat_Doc_Orange", "hat_Doc_Purple", "hat_Doc_Red", "hat_Doc_White", "hat_Dodgeball", "hat_Dorag_Black", "hat_Dorag_Desert", "hat_Dorag_Jungle", "hat_Dorag_Purple", "hat_Dorag_Sky", "hat_Dorag_Snow", "hat_Dorag_Yellow", "hat_doubletophat", "hat_DrillMetal", "hat_DrillStone", "hat_DrillWood", "hat_EarmuffGreen", "hat_EarmuffsPink", "hat_EarmuffsYellow", "hat_EarnmuffBlue", "hat_eggGreen", "hat_eggYellow", "hat_enforcer", "hat_erisMorn", "hat_fairywings", "hat_fishCap", "hat_fishhed", "hat_fishingHat", "hat_flowerpot", "hat_frankenbolts", "hat_frankenbride", "hat_fungleFlower", "hat_geoff", "hat_glowstick", "hat_glowstickCyan", "hat_glowstickOrange", "hat_glowstickPink", "hat_glowstickPurple", "hat_glowstickYellow", "hat_goggles", "hat_Goggles_Black", "hat_Goggles_Chrome", "hat_GovtDesert", "hat_GovtHeadset", "hat_halospartan", "hat_hardhat", "hat_Hardhat_black", "hat_Hardhat_Blue", "hat_Hardhat_Green", "hat_Hardhat_Orange", "hat_Hardhat_Pink", "hat_Hardhat_Purple", "hat_Hardhat_Red", "hat_Hardhat_White", "hat_HardtopHat", "hat_headslug_Purple", "hat_headslug_Red", "hat_headslug_White", "hat_headslug_Yellow", "hat_Heart", "hat_heim", "hat_Herohood_Black", "hat_Herohood_Blue", "hat_Herohood_Pink", "hat_Herohood_Purple", "hat_Herohood_Red", "hat_Herohood_Yellow", "hat_hl_fubuki", "hat_hl_gura", "hat_hl_korone", "hat_hl_marine", "hat_hl_mio", "hat_hl_moona", "hat_hl_okayu", "hat_hl_pekora", "hat_hl_risu", "hat_hl_watson", "hat_hunter", "hat_IceCreamMatcha", "hat_IceCreamMint", "hat_IceCreamNeo", "hat_IceCreamStrawberry", "hat_IceCreamUbe", "hat_IceCreamVanilla", "hat_Igloo", "hat_Janitor", "hat_jayce", "hat_jinx", "hat_killerplant", "hat_lilShroom", "hat_maraSov", "hat_mareLwyd", "hat_military", "hat_MilitaryWinter", "hat_MinerBlack", "hat_MinerYellow", "hat_mira_bush", "hat_mira_case", "hat_mira_cloud", "hat_mira_flower", "hat_mira_flower_red", "hat_mira_gem", "hat_mira_headset_blue", "hat_mira_headset_pink", "hat_mira_headset_yellow", "hat_mira_leaf", "hat_mira_milk", "hat_mira_sign_blue", "hat_mohawk_bubblegum", "hat_mohawk_bumblebee", "hat_mohawk_purple_green", "hat_mohawk_rainbow", "hat_mummy", "hat_mushbuns", "hat_mushroomBeret", "hat_mysteryBones", "hat_NewYear2023", "hat_OrangeHat", "hat_osiris", "hat_pack01_Astronaut0001", "hat_pack02_Tengallon0001", "hat_pack02_Tengallon0002", "hat_pack03_Stickynote0004", "hat_pack04_Geoffmask0001", "hat_pack06holiday_candycane0001", "hat_PancakeStack", "hat_paperhat", "hat_Paperhat_Black", "hat_Paperhat_Blue", "hat_Paperhat_Cyan", "hat_Paperhat_Lightblue", "hat_Paperhat_Pink", "hat_Paperhat_Yellow", "hat_papermask", "hat_partyhat", "hat_pickaxe", "hat_Pineapple", "hat_PizzaSliceHat", "hat_pk01_BaseballCap", "hat_pk02_Crown", "hat_pk02_Eyebrows", "hat_pk02_HaloHat", "hat_pk02_HeroCap", "hat_pk02_PipCap", "hat_pk02_PlungerHat", "hat_pk02_ScubaHat", "hat_pk02_StickminHat", "hat_pk02_StrawHat", "hat_pk02_TenGallonHat", "hat_pk02_ThirdEyeHat", "hat_pk02_ToiletPaperHat", "hat_pk02_Toppat", "hat_pk03_Fedora", "hat_pk03_Goggles", "hat_pk03_Headphones", "hat_pk03_Security1", "hat_pk03_StrapHat", "hat_pk03_Traffic", "hat_pk04_Antenna", "hat_pk04_Archae", "hat_pk04_Balloon", "hat_pk04_Banana", "hat_pk04_Bandana", "hat_pk04_Beanie", "hat_pk04_Bear", "hat_pk04_BirdNest", "hat_pk04_CCC", "hat_pk04_Chef", "hat_pk04_DoRag", "hat_pk04_Fez", "hat_pk04_GeneralHat", "hat_pk04_HunterCap", "hat_pk04_JungleHat", "hat_pk04_MinerCap", "hat_pk04_MiniCrewmate", "hat_pk04_Pompadour", "hat_pk04_RamHorns", "hat_pk04_Slippery", "hat_pk04_Snowman", "hat_pk04_Vagabond", "hat_pk04_WinterHat", "hat_pk05_Burthat", "hat_pk05_Cheese", "hat_pk05_cheesetoppat", "hat_pk05_Cherry", "hat_pk05_davehat", "hat_pk05_Egg", "hat_pk05_Ellie", "hat_pk05_EllieToppat", "hat_pk05_Ellryhat", "hat_pk05_Fedora", "hat_pk05_Flamingo", "hat_pk05_FlowerPin", "hat_pk05_GeoffreyToppat", "hat_pk05_Helmet", "hat_pk05_HenryToppat", "hat_pk05_Macbethhat", "hat_pk05_Plant", "hat_pk05_RHM", "hat_pk05_Svenhat", "hat_pk05_Wizardhat", "hat_pk06_Candycanes", "hat_pk06_ElfHat", "hat_pk06_Lights", "hat_pk06_Present", "hat_pk06_Reindeer", "hat_pk06_Santa", "hat_pk06_Snowman", "hat_pk06_tree", "hat_pkHW01_BatWings", "hat_pkHW01_CatEyes", "hat_pkHW01_Horns", "hat_pkHW01_Machete", "hat_pkHW01_Mohawk", "hat_pkHW01_Pirate", "hat_pkHW01_PlagueHat", "hat_pkHW01_Pumpkin", "hat_pkHW01_ScaryBag", "hat_pkHW01_Witch", "hat_pkHW01_Wolf", "hat_Plunger_Blue", "hat_Plunger_Yellow", "hat_police", "hat_Ponytail", "hat_Pot", "hat_Present", "hat_Prototype", "hat_pusheenGreyHat", "hat_PusheenicornHat", "hat_pusheenMintHat", "hat_pusheenPinkHat", "hat_pusheenPurpleHat", "hat_pusheenSitHat", "hat_pusheenSleepHat", "hat_pyramid", "hat_rabbitEars", "hat_Ramhorn_Black", "hat_Ramhorn_Red", "hat_Ramhorn_White", "hat_ratchet", "hat_Records", "hat_RockIce", "hat_RockLava", "hat_Rubberglove", "hat_Rupert", "hat_russian", "hat_saint14", "hat_sausage", "hat_savathun", "hat_schnapp", "hat_screamghostface", "hat_Scrudge", "hat_sharkfin", "hat_shaxx", "hat_shovel", "hat_SlothHat", "hat_SnowbeanieGreen", "hat_SnowbeanieOrange", "hat_SnowBeaniePurple", "hat_SnowbeanieRed", "hat_Snowman", "hat_Soccer", "hat_Sorry", "hat_starBalloon", "hat_starhorse", "hat_Starless", "hat_StarTopper", "hat_stethescope", "hat_StrawberryLeavesHat", "hat_TenGallon_Black", "hat_TenGallon_White", "hat_ThomasC", "hat_tinFoil", "hat_titan", "hat_ToastButterHat", "hat_tombstone", "hat_tophat", "hat_ToppatHair", "hat_towelwizard", "hat_Traffic_Blue", "hat_traffic_purple", "hat_Traffic_Red", "hat_Traffic_Yellow", "hat_Unicorn", "hat_vi", "hat_viking", "hat_Visor", "hat_Voleyball", "hat_w21_candycane_blue", "hat_w21_candycane_bubble", "hat_w21_candycane_chocolate", "hat_w21_candycane_mint", "hat_w21_elf_pink", "hat_w21_elf_swe", "hat_w21_gingerbread", "hat_w21_holly", "hat_w21_krampus", "hat_w21_lights_white", "hat_w21_lights_yellow", "hat_w21_log", "hat_w21_mistletoe", "hat_w21_mittens", "hat_w21_nutcracker", "hat_w21_pinecone", "hat_w21_present_evil", "hat_w21_present_greenyellow", "hat_w21_present_redwhite", "hat_w21_present_whiteblue", "hat_w21_santa_evil", "hat_w21_santa_green", "hat_w21_santa_mint", "hat_w21_santa_pink", "hat_w21_santa_white", "hat_w21_santa_yellow", "hat_w21_snowflake", "hat_w21_snowman", "hat_w21_snowman_evil", "hat_w21_snowman_greenred", "hat_w21_snowman_redgreen", "hat_w21_snowman_swe", "hat_w21_winterpuff", "hat_wallcap", "hat_warlock", "hat_whitetophat", "hat_wigJudge", "hat_wigTall", "hat_WilfordIV", "hat_Winston", "hat_WinterGreen", "hat_WinterHelmet", "hat_WinterRed", "hat_WinterYellow", "hat_witch_green", "hat_witch_murky", "hat_witch_pink", "hat_witch_white", "hat_wolf_grey", "hat_wolf_murky", "hat_Zipper" };
			std::vector availableSkins = { "skin_None", "skin_Abominalskin", "skin_ApronGreen", "skin_Archae", "skin_Astro", "skin_Astronaut-Blueskin", "skin_Astronaut-Cyanskin", "skin_Astronaut-Orangeskin", "skin_Bananaskin", "skin_benoit", "skin_Bling", "skin_BlueApronskin", "skin_BlueSuspskin", "skin_Box1skin", "skin_BubbleWrapskin", "skin_Burlapskin", "skin_BushSign1skin", "skin_Bushskin", "skin_BusinessFem-Aquaskin", "skin_BusinessFem-Tanskin", "skin_BusinessFemskin", "skin_caitlin", "skin_Capt", "skin_CCC", "skin_ChefBlackskin", "skin_ChefBlue", "skin_ChefRed", "skin_clown", "skin_D2Cskin", "skin_D2Hunter", "skin_D2Osiris", "skin_D2Saint14", "skin_D2Shaxx", "skin_D2Titan", "skin_D2Warlock", "skin_enforcer", "skin_fairy", "skin_FishingSkinskin", "skin_fishmonger", "skin_FishSkinskin", "skin_General", "skin_greedygrampaskin", "skin_halospartan", "skin_Hazmat-Blackskin", "skin_Hazmat-Blueskin", "skin_Hazmat-Greenskin", "skin_Hazmat-Pinkskin", "skin_Hazmat-Redskin", "skin_Hazmat-Whiteskin", "skin_Hazmat", "skin_heim", "skin_hl_fubuki", "skin_hl_gura", "skin_hl_korone", "skin_hl_marine", "skin_hl_mio", "skin_hl_moona", "skin_hl_okayu", "skin_hl_pekora", "skin_hl_risu", "skin_hl_watson", "skin_Horse1skin", "skin_Hotdogskin", "skin_InnerTubeSkinskin", "skin_JacketGreenskin", "skin_JacketPurpleskin", "skin_JacketYellowskin", "skin_Janitorskin", "skin_jayce", "skin_jinx", "skin_LifeVestSkinskin", "skin_Mech", "skin_MechanicRed", "skin_Military", "skin_MilitaryDesert", "skin_MilitarySnowskin", "skin_Miner", "skin_MinerBlackskin", "skin_mummy", "skin_OrangeSuspskin", "skin_PinkApronskin", "skin_PinkSuspskin", "skin_Police", "skin_presentskin", "skin_prisoner", "skin_PrisonerBlue", "skin_PrisonerTanskin", "skin_pumpkin", "skin_PusheenGreyskin", "skin_Pusheenicornskin", "skin_PusheenMintskin", "skin_PusheenPinkskin", "skin_PusheenPurpleskin", "skin_ratchet", "skin_rhm", "skin_RockIceskin", "skin_RockLavaskin", "skin_Sack1skin", "skin_scarfskin", "skin_Science", "skin_Scientist-Blueskin", "skin_Scientist-Darkskin", "skin_screamghostface", "skin_Security", "skin_Skin_SuitRedskin", "skin_Slothskin", "skin_SportsBlueskin", "skin_SportsRedskin", "skin_SuitB", "skin_SuitW", "skin_SweaterBlueskin", "skin_SweaterPinkskin", "skin_Sweaterskin", "skin_SweaterYellowskin", "skin_Tarmac", "skin_ToppatSuitFem", "skin_ToppatVest", "skin_uglysweaterskin", "skin_vampire", "skin_vi", "skin_w21_deer", "skin_w21_elf", "skin_w21_msclaus", "skin_w21_nutcracker", "skin_w21_santa", "skin_w21_snowmate", "skin_w21_tree", "skin_Wall", "skin_Winter", "skin_witch", "skin_YellowApronskin", "skin_YellowSuspskin" };
			std::vector availableVisors = { "visor_EmptyVisor", "visor_anime", "visor_BaconVisor", "visor_BananaVisor", "visor_beautyMark", "visor_BillyG", "visor_Blush", "visor_Bomba", "visor_BubbleBumVisor", "visor_Candycane", "visor_Carrot", "visor_chimkin", "visor_clownnose", "visor_Crack", "visor_CucumberVisor", "visor_D2CGoggles", "visor_Dirty", "visor_Dotdot", "visor_doubleeyepatch", "visor_eliksni", "visor_erisBandage", "visor_eyeball", "visor_EyepatchL", "visor_EyepatchR", "visor_fishhook", "visor_Galeforce", "visor_heim", "visor_hl_ah", "visor_hl_bored", "visor_hl_hmph", "visor_hl_marine", "visor_hl_nothoughts", "visor_hl_nudge", "visor_hl_smug", "visor_hl_sweepy", "visor_hl_teehee", "visor_hl_wrong", "visor_IceBeard", "visor_IceCreamChocolateVisor", "visor_IceCreamMintVisor", "visor_IceCreamStrawberryVisor", "visor_IceCreamUbeVisor", "visor_is_beard", "visor_JanitorStache", "visor_jinx", "visor_Krieghaus", "visor_Lava", "visor_LolliBlue", "visor_LolliBrown", "visor_LolliOrange", "visor_lollipopCrew", "visor_lollipopLemon", "visor_lollipopLime", "visor_LolliRed", "visor_marshmallow", "visor_masque_blue", "visor_masque_green", "visor_masque_red", "visor_masque_white", "visor_mira_card_blue", "visor_mira_card_red", "visor_mira_glasses", "visor_mira_mask_black", "visor_mira_mask_blue", "visor_mira_mask_green", "visor_mira_mask_purple", "visor_mira_mask_red", "visor_mira_mask_white", "visor_Mouth", "visor_mummy", "visor_PiercingL", "visor_PiercingR", "visor_PizzaVisor", "visor_pk01_AngeryVisor", "visor_pk01_DumStickerVisor", "visor_pk01_FredVisor", "visor_pk01_HazmatVisor", "visor_pk01_MonoclesVisor", "visor_pk01_PaperMaskVisor", "visor_pk01_PlagueVisor", "visor_pk01_RHMVisor", "visor_pk01_Security1Visor", "visor_Plsno", "visor_polus_ice", "visor_pusheenGorgeousVisor", "visor_pusheenKissyVisor", "visor_pusheenKoolKatVisor", "visor_pusheenOmNomNomVisor", "visor_pusheenSmileVisor", "visor_pusheenYaaaaaayVisor", "visor_Reginald", "visor_Rudolph", "visor_savathun", "visor_Scar", "visor_SciGoggles", "visor_shopglasses", "visor_shuttershadesBlue", "visor_shuttershadesLime", "visor_shuttershadesPink", "visor_shuttershadesPurple", "visor_shuttershadesWhite", "visor_shuttershadesYellow", "visor_SkiGoggleBlack", "visor_SKiGogglesOrange", "visor_SkiGogglesWhite", "visor_SmallGlasses", "visor_SmallGlassesBlue", "visor_SmallGlassesRed", "visor_starfish", "visor_Stealthgoggles", "visor_Stickynote_Cyan", "visor_Stickynote_Green", "visor_Stickynote_Orange", "visor_Stickynote_Pink", "visor_Stickynote_Purple", "visor_Straw", "visor_sunscreenv", "visor_teary", "visor_ToastVisor", "visor_tvColorTest", "visor_vr_Vr-Black", "visor_vr_Vr-White", "visor_w21_carrot", "visor_w21_nutstache", "visor_w21_nye", "visor_w21_santabeard", "visor_wash", "visor_WinstonStache" };
			std::vector availablePets = { "pet_EmptyPet", "pet_Alien", "pet_Bedcrab", "pet_BredPet", "pet_Bush", "pet_Charles", "pet_Charles_Red", "pet_ChewiePet", "pet_clank", "pet_coaltonpet", "pet_Creb", "pet_Crewmate", "pet_Cube", "pet_D2GhostPet", "pet_D2PoukaPet", "pet_D2WormPet", "pet_Doggy", "pet_Ellie", "pet_frankendog", "pet_GuiltySpark", "pet_HamPet", "pet_Hamster", "pet_HolidayHamPet", "pet_Lava", "pet_nuggetPet", "pet_Pip", "pet_poro", "pet_Pusheen", "pet_Robot", "pet_Snow", "pet_Squig", "pet_Stickmin", "pet_Stormy", "pet_test", "pet_UFO", "pet_YuleGoatPet" };
			std::vector availableNamePlates = { "nameplate_NoPlate", "nameplate_airship_Toppat", "nameplate_airship_CCC", "nameplate_airship_Diamond", "nameplate_airship_Emerald", "nameplate_airship_Gems", "nameplate_airship_government", "nameplate_Airship_Hull", "nameplate_airship_Ruby", "nameplate_airship_Sky", "nameplate_Polus-Skyline", "nameplate_Polus-Snowmates", "nameplate_Polus_Colors", "nameplate_Polus_DVD", "nameplate_Polus_Ground", "nameplate_Polus_Lava", "nameplate_Polus_Planet", "nameplate_Polus_Snow", "nameplate_Polus_SpecimenBlue", "nameplate_Polus_SpecimenGreen", "nameplate_Polus_SpecimenPurple", "nameplate_is_yard", "nameplate_is_dig", "nameplate_is_game", "nameplate_is_ghost", "nameplate_is_green", "nameplate_is_sand", "nameplate_is_trees", "nameplate_Mira_Cafeteria", "nameplate_Mira_Glass", "nameplate_Mira_Tiles", "nameplate_Mira_Vines", "nameplate_Mira_Wood", "nameplate_hw_candy", "nameplate_hw_woods", "nameplate_hw_pumpkin" };
			//help me out with the nameplates, couldn't find them in the game assets
			std::string name = "";
			std::vector<std::string> validNames;
			for (std::string i : State.cyclerUserNames) {
				if (i.length() >= 13 || RemoveHtmlTags(i) != i)
					continue;
				validNames.push_back(i);
			}
			if (State.confuserNameGeneration == 0 || (State.cyclerNameGeneration == 2 && ((IsHost() || !State.SafeMode) ? State.cyclerUserNames.empty() : validNames.empty())))
				name = GenerateRandomString();
			else if (State.confuserNameGeneration == 1)
				name = GenerateRandomString(true);
			else if (State.confuserNameGeneration == 2) {
				if ((IsHost() || !State.SafeMode) && !State.cyclerUserNames.empty())
					name = State.cyclerUserNames[randi(0, State.cyclerUserNames.size() - 1)];
				else
					name = validNames[randi(0, validNames.size() - 1)];
			}
			else
				name = GenerateRandomString();

			int color = randi(0, 17);
			std::string hat = availableHats[randi(0, availableHats.size() - 1)];
			std::string visor = availableVisors[randi(0, availableVisors.size() - 1)];
			std::string skin = availableSkins[randi(0, availableSkins.size() - 1)];
			std::string pet = availablePets[randi(0, availablePets.size() - 1)];
			std::string nameplate = availableNamePlates[randi(0, availableNamePlates.size() - 1)];
			if (IsInGame() || IsInLobby()) {
				queue->push(new RpcSetName(name));
				queue->push(new RpcSetColor(color));
				queue->push(new RpcSetHat(convert_to_string(hat)));
				queue->push(new RpcSetSkin(convert_to_string(skin)));
				queue->push(new RpcSetVisor(convert_to_string(visor)));
				queue->push(new RpcSetPet(convert_to_string(pet)));
				queue->push(new RpcSetNamePlate(convert_to_string(nameplate)));
			}
		}
		else if (IsInGame() || IsInLobby()) {
			if (IsHost() || !State.SafeMode)
				queue->push(new RpcForceColor(*Game::pLocalPlayer, State.originalColor, true));
			else
				queue->push(new RpcSetColor(State.originalColor));
			queue->push(new RpcSetPet(State.originalPet));
			queue->push(new RpcSetSkin(State.originalSkin));
			queue->push(new RpcSetHat(State.originalHat));
			queue->push(new RpcSetVisor(State.originalVisor));
			queue->push(new RpcSetNamePlate(State.originalNamePlate));
			queue->push(new RpcSetName(State.originalName));
		}
	}
	catch (...) {
		LOG_DEBUG("Failed to control appearance due to exception");
	}
}

GameData_PlayerOutfit* GetPlayerOutfit(GameData_PlayerInfo* player, bool includeShapeshifted /* = false */) {
	if (!player) return nullptr;
	const il2cpp::Dictionary dic(player->fields.Outfits);
	if (includeShapeshifted) {
		auto playerOutfit = dic[PlayerOutfitType__Enum::Shapeshifted];
		if (playerOutfit && !convert_from_string(GameData_PlayerOutfit_get_PlayerName(playerOutfit, nullptr)).empty()) {
			return playerOutfit;
		}
	}
	return dic[PlayerOutfitType__Enum::Default];
}

bool PlayerIsImpostor(GameData_PlayerInfo* player) {

	if (player->fields.Role == nullptr) return false;

	RoleBehaviour* role = player->fields.Role;
	return role->fields.TeamType == RoleTeamTypes__Enum::Impostor;
}


Color GetRoleColor(RoleBehaviour* roleBehaviour) {
	if (roleBehaviour == nullptr) return Palette__TypeInfo->static_fields->White;

	app::Color c;
	switch (roleBehaviour->fields.Role) {
	default:
	case RoleTypes__Enum::CrewmateGhost:
		c = Palette__TypeInfo->static_fields->AcceptedGreen;
		break;
	case RoleTypes__Enum::Crewmate:
		c = Palette__TypeInfo->static_fields->White;
		break;
	case RoleTypes__Enum::Engineer:
		c = Palette__TypeInfo->static_fields->CrewmateBlue;
		break;
	case RoleTypes__Enum::GuardianAngel:
		c = Palette__TypeInfo->static_fields->Purple;
		break;
	case RoleTypes__Enum::Scientist:
		c = Palette__TypeInfo->static_fields->Blue;
		break;
	case RoleTypes__Enum::Impostor:
		c = Palette__TypeInfo->static_fields->ImpostorRed;
		break;
	case RoleTypes__Enum::Shapeshifter:
		c = Palette__TypeInfo->static_fields->Orange;
		break;
	case RoleTypes__Enum::ImpostorGhost:
		c = Palette__TypeInfo->static_fields->DisabledGrey;
		break;
	}
	return c;
}

std::string GetRoleName(RoleBehaviour* roleBehaviour, bool abbreviated /* = false */)
{
	if (roleBehaviour == nullptr) return (abbreviated ? "Unk" : "Unknown");

	switch (roleBehaviour->fields.Role)
	{
		case RoleTypes__Enum::Engineer:
			return (abbreviated ? "Eng" : "Engineer");
		case RoleTypes__Enum::GuardianAngel:
			return (abbreviated ? "GA" : "Guardian Angel");
		case RoleTypes__Enum::Impostor:
			return (abbreviated ? "Imp" : "Impostor");
		case RoleTypes__Enum::Scientist:
			return (abbreviated ? "Sci" : "Scientist");
		case RoleTypes__Enum::Shapeshifter:
			return (abbreviated ? "SS" : "Shapeshifter");
		case RoleTypes__Enum::Crewmate:
			return (abbreviated ? "Crew" : "Crewmate");
		case RoleTypes__Enum::CrewmateGhost:
			return (abbreviated ? "CG" : "Crewmate Ghost");
		case RoleTypes__Enum::ImpostorGhost:
			return (abbreviated ? "IG" : "Impostor Ghost");
		default:
			return (abbreviated ? "Unk" : "Unknown");
	}
}

RoleTypes__Enum GetRoleTypesEnum(RoleType role)
{
	if (role == RoleType::Shapeshifter) {
		return RoleTypes__Enum::Shapeshifter;
	}
	else if (role == RoleType::Impostor) {
		return RoleTypes__Enum::Impostor;
	}
	else if (role == RoleType::Engineer) {
		return RoleTypes__Enum::Engineer;
	}
	else if (role == RoleType::Scientist) {
		return RoleTypes__Enum::Scientist;
	}
	return RoleTypes__Enum::Crewmate;
}

float GetDistanceBetweenPoints_Unity(const Vector2& p1, const Vector2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

float GetDistanceBetweenPoints_ImGui(const ImVec2& p1, const ImVec2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

void DoPolylineSimplification(std::vector<ImVec2>& inPoints, std::vector<std::chrono::system_clock::time_point>& inTimeStamps, std::vector<ImVec2>& outPoints, std::vector<std::chrono::system_clock::time_point>& outTimeStamps, float sqDistanceThreshold, bool clearInputs)
{
	sqDistanceThreshold = sqDistanceThreshold - FLT_EPSILON;
	size_t numPendingPoints = inPoints.size();
	if (numPendingPoints < 2)
		return;

	Profiler::BeginSample("PolylineSimplification");
	ImVec2 prevPoint = inPoints[0], point = inPoints[0];
	std::chrono::system_clock::time_point timestamp = inTimeStamps[0];
	size_t numNewPointsAdded = 0;

	// always add the first point
	outPoints.push_back(point);
	outTimeStamps.push_back(timestamp);
	numNewPointsAdded++;
	for (size_t index = 1; index < numPendingPoints; index++)
	{
		point = inPoints[index];
		timestamp = inTimeStamps[index];
		float diffX = point.x - prevPoint.x, diffY = point.y - prevPoint.y;
		if ((diffX * diffX + diffY * diffY) >= sqDistanceThreshold)
		{
			prevPoint = point;
			// add the point if it's beyond the distance threshold of prev point.
			outPoints.push_back(point);
			outTimeStamps.push_back(timestamp);
			numNewPointsAdded++;
		}
	}
	// add the last point if it's not also the first point nor has already been added as the last point
	if ((point.x != prevPoint.x) || (point.y != prevPoint.y))
	{
		outPoints.push_back(point);
		outTimeStamps.push_back(timestamp);
		numNewPointsAdded++;
	}

	if (clearInputs)
	{
		inPoints.clear();
		inTimeStamps.clear();
	}
	Profiler::EndSample("PolylineSimplification");
}

float getMapXOffsetSkeld(float x)
{
	GameOptions options;
	return (options.GetByte(app::ByteOptionNames__Enum::MapId) == 3) ? (-1) * x : x;
}

bool Object_1_IsNotNull(app::Object_1* obj)
{
	return app::Object_1_op_Implicit(obj, nullptr);
}

bool Object_1_IsNull(app::Object_1* obj)
{
	return !Object_1_IsNotNull(obj);
}

std::string GetPlayerName() {
	auto player = app::DataManager_get_Player(nullptr);
	static FieldInfo* field = il2cpp_class_get_field_from_name(player->Il2CppClass.klass, "customization");
	LOG_ASSERT(field != nullptr);
	auto customization = il2cpp_field_get_value_object(field, player);
	LOG_ASSERT(customization != nullptr);
	static FieldInfo* field2 = il2cpp_class_get_field_from_name(customization->Il2CppClass.klass, "name");
	auto name = il2cpp_field_get_value_object(field2, customization);
	LOG_ASSERT(name != nullptr);
	return convert_from_string(reinterpret_cast<String*>(name));
}

void SetPlayerName(std::string_view name) {
	auto player = app::DataManager_get_Player(nullptr);
	static FieldInfo* field = il2cpp_class_get_field_from_name(player->Il2CppClass.klass, "customization");
	LOG_ASSERT(field != nullptr);
	auto customization = il2cpp_field_get_value_object(field, player);
	LOG_ASSERT(customization != nullptr);
	app::PlayerCustomizationData_set_Name(customization, convert_to_string(name), nullptr);
}

//TODO: Workaround
#define GET_VIRTUAL_INVOKE(obj, method) \
	((VirtualInvokeData*)(&obj->klass->vtable))[ \
		(obj->klass->interfaceOffsets ? obj->klass->interfaceOffsets[0].offset : 0) \
		+ offsetof(decltype(obj->klass->vtable), method) \
		/ sizeof(VirtualInvokeData)]

GameLogicOptions::GameLogicOptions() {
	auto mgr = app::GameManager_get_Instance(nullptr);
	if (mgr == nullptr)
		return;
	auto logic = app::GameManager_get_LogicOptions(mgr, nullptr);
	LOG_ASSERT(logic != nullptr);
	auto& func = GET_VIRTUAL_INVOKE(logic, __unknown_4);
	_options = ((app::IGameOptions * (*)(void*, const void*))(func.methodPtr))(logic, func.method);
	LOG_ASSERT(_options != nullptr);
}

GameOptions::GameOptions() : _options(nullptr) {
	auto mgr = app::GameOptionsManager_get_Instance(nullptr);
	if (mgr == nullptr) // see issue 477.
		return;
	if (app::GameOptionsManager_get_HasOptions(mgr, nullptr)) {
		_options = app::GameOptionsManager_get_CurrentGameOptions(mgr, nullptr);
		LOG_ASSERT(_options != nullptr);
	}
}

GameOptions& GameOptions::SetByte(app::ByteOptionNames__Enum option, uint8_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetByte);
	((void(*)(void*, app::ByteOptionNames__Enum, uint8_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetFloat(app::FloatOptionNames__Enum option, float value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetFloat);
	((void(*)(void*, app::FloatOptionNames__Enum, float, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetBool(app::BoolOptionNames__Enum option, bool value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetBool);
	((void(*)(void*, app::BoolOptionNames__Enum, bool, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetInt(app::Int32OptionNames__Enum option, int32_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetInt);
	((void(*)(void*, app::Int32OptionNames__Enum, int32_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetUInt(app::UInt32OptionNames__Enum option, uint32_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetUInt);
	((void(*)(void*, app::UInt32OptionNames__Enum, uint32_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

uint8_t GameOptions::GetByte(app::ByteOptionNames__Enum option, uint8_t defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetByte);
	uint8_t value;
	bool succ = ((bool(*)(void*, app::ByteOptionNames__Enum, uint8_t*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

float GameOptions::GetFloat(app::FloatOptionNames__Enum option, float defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetFloat);
	float value;
	bool succ = ((bool(*)(void*, app::FloatOptionNames__Enum, float*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

bool GameOptions::GetBool(app::BoolOptionNames__Enum option, bool defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetBool);
	bool value;
	bool succ = ((bool(*)(void*, app::BoolOptionNames__Enum, bool*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

int32_t GameOptions::GetInt(app::Int32OptionNames__Enum option, int32_t defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetInt);
	int32_t value;
	bool succ = ((bool(*)(void*, app::Int32OptionNames__Enum, int32_t*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

app::GameModes__Enum GameOptions::GetGameMode() const {
	if (!_options) return app::GameModes__Enum::None;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_GameMode);
	return ((app::GameModes__Enum(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetMaxPlayers() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_MaxPlayers);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

uint8_t GameOptions::GetMapId() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_MapId);
	return ((uint8_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetNumImpostors() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_NumImpostors);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetTotalTaskCount() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_TotalTaskCount);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

RoleOptions GameOptions::GetRoleOptions() const {
	auto& func = GET_VIRTUAL_INVOKE(_options, get_RoleOptions);
	return RoleOptions(((app::IRoleOptionsCollection*(*)(void*, const void*))(func.methodPtr))(_options, func.method));
}

float GameOptions::GetPlayerSpeedMod() const {
	return GetFloat(app::FloatOptionNames__Enum::PlayerSpeedMod, 1.0F);
}

float GameOptions::GetKillCooldown() const {
	return GetFloat(app::FloatOptionNames__Enum::KillCooldown, 1.0F);
}

float GameOptions::GetGACooldown() const {
	return GetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 1.0F);
}

RoleOptions& RoleOptions::SetRoleRate(app::RoleTypes__Enum role, int32_t maxCount, int32_t chance) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetRoleRate);
	((void(*)(void*, app::RoleTypes__Enum, int32_t, int32_t, const void*))(func.methodPtr))
		(_options, role, maxCount, chance, func.method);
	return *this;
}

RoleOptions& RoleOptions::SetRoleRecommended(app::RoleTypes__Enum role) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetRoleRecommended);
	((void(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
	return *this;
}

int32_t RoleOptions::GetNumPerGame(app::RoleTypes__Enum role) const {
	auto& func = GET_VIRTUAL_INVOKE(_options, GetNumPerGame);
	return ((int32_t(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
}

int32_t RoleOptions::GetChancePerGame(app::RoleTypes__Enum role) const {
	auto& func = GET_VIRTUAL_INVOKE(_options, GetChancePerGame);
	return ((int32_t(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
}

void SaveGameOptions() {
	SaveGameOptions(GameOptions());
}

void SaveGameOptions(const class GameOptions& gameOptions) {
	/*State.PlayerSpeed = State.PrevPlayerSpeed = gameOptions.GetPlayerSpeedMod();
	State.GACooldown = State.PrevGACooldown = gameOptions.GetGACooldown();
	State.KillDistance = State.PrevKillDistance = gameOptions.GetInt(app::Int32OptionNames__Enum::KillDistance);
	State.TaskBarUpdates = State.PrevTaskBarUpdates = gameOptions.GetInt(app::Int32OptionNames__Enum::TaskBarMode);
	State.VisualTasks = State.PrevVisualTasks = gameOptions.GetBool(app::BoolOptionNames__Enum::VisualTasks);*/
	State.mapHostChoice = gameOptions.GetMapId();
	State.impostors_amount = gameOptions.GetNumImpostors();
}
