#include "pch-il2cpp.h"
#include "game_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			GameOptions options;
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.f, 10.f, 0.05f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				if(IsInGame() || IsInLobby())
					GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::PlayerSpeedMod, State.PlayerSpeed);
				State.PrevPlayerSpeed = State.PlayerSpeed;
			}
			if (CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE, 225 * State.dpiScale)) {
				if (IsInGame() || IsInLobby())
					GameLogicOptions().SetInt(app::Int32OptionNames__Enum::KillDistance, State.KillDistance);
				State.PrevKillDistance = State.KillDistance;
			}
			if (GameOptions().GetGameMode() == GameModes__Enum::Normal) {
				if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES, 225 * State.dpiScale)) {
					GameLogicOptions().SetInt(app::Int32OptionNames__Enum::TaskBarMode, State.TaskBarUpdates);
					State.PrevTaskBarUpdates = State.TaskBarUpdates;
				}
			}
			if (ImGui::Checkbox("No Ability Cooldown", &State.NoAbilityCD)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			if ((!IsHost() && State.SafeMode) && ImGui::Button("Set Color") && (IsInGame() || IsInLobby()))
			{
				bool colorAvailable = true;

				for (PlayerControl* player : GetAllPlayerControl())
				{
					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
					if (outfit == NULL) continue;
					if (State.SelectedColorId == outfit->fields.ColorId && !IsHost())
					{
						colorAvailable = false;
						break;
					}
				}

				if (colorAvailable) {
					if (IsInGame())
						State.rpcQueue.push(new RpcSetColor(State.SelectedColorId));
					else if (IsInLobby())
						State.lobbyRpcQueue.push(new RpcSetColor(State.SelectedColorId));
				}
			}

			if ((IsHost() || !State.SafeMode) && ImGui::Button("Set Color") && (IsInGame() || IsInLobby()))
			{
				if (IsInGame())
					State.rpcQueue.push(new RpcForceColor(*Game::pLocalPlayer, State.SelectedColorId, true));
				else if (IsInLobby())
					State.lobbyRpcQueue.push(new RpcForceColor(*Game::pLocalPlayer, State.SelectedColorId, true));
			}

			if (IsHost() || !State.SafeMode) {
				ImGui::SameLine(87 * State.dpiScale);
				CustomListBoxInt(" ", &State.SelectedColorId, HOSTCOLORS, 85.0f * State.dpiScale);
			}
			else {
				ImGui::SameLine(87 * State.dpiScale);
				CustomListBoxInt(" ", &State.SelectedColorId, COLORS, 85.0f * State.dpiScale);
			}

			ImGui::SameLine(215 * State.dpiScale);
			if (ImGui::Button("Random Color"))
			{
				State.SelectedColorId = GetRandomColorId();
			}

			ImGui::SameLine();
			if (ImGui::Checkbox("Snipe Color", &State.SnipeColor)) {
				State.Save();
			}

			char* msgBuffer[255]{ const_cast<char*>(State.chatMessage.c_str()) };
			if (ImGui::InputTextMultiline("\n\nChat Message", *msgBuffer, IM_ARRAYSIZE(msgBuffer))) {
				State.chatMessage = std::string(*msgBuffer);
			}
			if (State.ChatCooldown >= 3.f) {
				ImGui::SameLine();
				if (ImGui::Button("Send"))
				{
					if (IsInGame()) {
						State.rpcQueue.push(new RpcSendChat(*Game::pLocalPlayer, State.chatMessage));
						State.MessageSent = true;
					}
					else if (IsInLobby()) {
						State.lobbyRpcQueue.push(new RpcSendChat(*Game::pLocalPlayer, State.chatMessage));
						State.MessageSent = true;
					}
				}
			}
			if (!State.SafeMode) {
				ImGui::SameLine();
				if (ImGui::Checkbox("Spam", &State.ChatSpam))
				{
					State.Save();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Spam by Everyone", &State.ChatSpamEveryone))
				{
					State.Save();
				}
			}

			if ((IsInGame() || IsInLobby()) && ImGui::Button("Destroy Map")) {
				if (IsInGame())
					State.rpcQueue.push(new DestroyMap());
				else if (IsInLobby())
					State.lobbyRpcQueue.push(new DestroyMap());
			}
			
			if (ImGui::Checkbox("Cycler", &State.Cycler)) {
				State.Save();
			}

			ImGui::SameLine(120.0f * State.dpiScale);
			if (ImGui::Checkbox("Cycle in Meeting", &State.CycleInMeeting)) {
				State.Save();
			}

			if (SteppedSliderFloat("Cycle Timer", &State.CycleTimer, 0.2f, 1.f, 0.02f, "%.2fs", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.PrevCycleTimer = State.CycleTimer;
				State.CycleDuration = State.CycleTimer * 50;
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			{
				if (IsHost() || State.SafeMode == false) {
					char* nameBufferHost[255]{ const_cast<char*>(State.userName1.c_str()) };
					if (ImGui::InputText("Cycler Name #1", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
						State.userName1 = std::string(*nameBufferHost);
					}
				}
				else {
					char* nameBuffer[13]{ const_cast<char*>(State.userName1.c_str()) };
					if (ImGui::InputText("Cycler Name #1", *nameBuffer, IM_ARRAYSIZE(nameBuffer))) {
						State.userName1 = std::string(*nameBuffer);
					}
				}
			}

			{
				if (IsHost() || State.SafeMode == false) {
					char* nameBufferHost[255]{ const_cast<char*>(State.userName2.c_str()) };
					if (ImGui::InputText("Cycler Name #2", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
						State.userName2 = std::string(*nameBufferHost);
					}
				}
				else {
					char* nameBuffer[13]{ const_cast<char*>(State.userName2.c_str()) };
					if (ImGui::InputText("Cycler Name #2", *nameBuffer, IM_ARRAYSIZE(nameBuffer))) {
						State.userName2 = std::string(*nameBuffer);
					}
				}
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Checkbox("Cycle Name", &State.CycleName)) {
				State.Save();
			}


			ImGui::SameLine(120.0f * State.dpiScale);
			if (ImGui::Checkbox("Cycle Color", &State.RandomColor)) {
				State.Save();
			}

			ImGui::SameLine(240.0f * State.dpiScale);
			if (ImGui::Checkbox("Cycle Hat", &State.RandomHat)) {
				State.Save();
			}

			if (ImGui::Checkbox("Cycle Visor", &State.RandomVisor)) {
				State.Save();
			}

			ImGui::SameLine(120.0f * State.dpiScale);
			if (ImGui::Checkbox("Cycle Skin", &State.RandomSkin)) {
				State.Save();
			}

			ImGui::SameLine(240.0f * State.dpiScale);
			if (ImGui::Checkbox("Cycle Pet", &State.RandomPet)) {
				State.Save();
			}

			if (ImGui::Checkbox("Cycle Nameplate", &State.RandomNamePlate)) {
				State.Save();
			}

			
			
			if (IsHost() || !State.SafeMode) {
				ImGui::SameLine(140.0f * State.dpiScale);
				if (ImGui::Checkbox("Cycle for Everyone (name & color only)", &State.CycleForEveryone)) {
					State.Save();
				}
			}

			if ((IsInGame() || IsInLobby()) && ImGui::Button("Reset Appearance"))
			{
				ControlAppearance(false);
			}
			if (State.ShowKeybinds && (IsInGame() || IsInLobby())) {
				ImGui::SameLine();
				HotKey(State.KeyBinds.Reset_Appearance);
			}
			if (IsInGame() || IsInLobby())
			{
				if (ImGui::Button("Save Appearance"))
					SaveOriginalAppearance();
			}
			if (State.ShowKeybinds && (IsInGame() || IsInLobby())) {
				ImGui::SameLine();
				HotKey(State.KeyBinds.Save_Appearance);
			}
			
			if (ImGui::Checkbox("Confuser (Randomize Appearance at Will)", &State.confuser)) {
				State.Save();
			}

			if (State.confuser && ImGui::CollapsingHeader("Confuser Options")) {
				if ((IsInGame() || IsInLobby()) && ImGui::Button("Confuse Now")) {
					ControlAppearance(true);
				}
				if (IsInGame() || IsInLobby()) {
					if (State.ShowKeybinds) {
						ImGui::SameLine();
						HotKey(State.KeyBinds.Randomize_Appearance);
					}
					if (IsHost() || !State.SafeMode)
						ImGui::SameLine();
				}
				if ((IsInGame() || IsInLobby()) && (IsHost() || !State.SafeMode) && ImGui::Button("Randomize Everyone")) {
					std::queue<RPCInterface*>* queue = nullptr;
					if (IsInGame())
						queue = &State.rpcQueue;
					else if (IsInLobby())
						queue = &State.lobbyRpcQueue;
					std::vector availableHats = { "hat_NoHat", "hat_bushhat", "hat_captain", "hat_doubletophat", "hat_flowerpot", "hat_military", "hat_MilitaryWinter", "hat_GovtDesert", "hat_police", "hat_Rupert", "hat_partyhat", "hat_tophat", "hat_towelwizard", "hat_russian", "hat_viking", "hat_wallcap", "hat_pk06_Snowman", "hat_pk06_Reindeer", "hat_pk06_Lights", "hat_pk06_Santa", "hat_pk06_tree", "hat_pk06_Present", "hat_pk06_Candycanes", "hat_pk06_ElfHat", "hats_newyears2018", "hat_whitetophat", "hat_pk02_Crown", "hat_pk02_Eyebrows", "hat_pk02_HaloHat", "hat_pk02_PipCap", "hat_pk02_ScubaHat", "hat_pk02_StickminHat", "hat_pk02_StrawHat", "hat_pk02_ThirdEyeHat", "hat_pk02_ToiletPaperHat", "hat_pk02_Toppat", "hat_pk03_Fedora", "hat_pk03_StrapHat", "hat_pk04_Banana", "hat_pk04_Bear", "hat_pk05_Cheese", "hat_pk05_Cherry", "hat_pk05_Egg", "hat_pk05_Fedora", "hat_pk05_Flamingo", "hat_pk05_FlowerPin", "hat_pk05_Helmet", "hat_pk05_Plant", "hat_pkHW01_PlagueHat", "hat_pkHW01_CatEyes", "hat_pkHW01_Horns", "hat_pkHW01_BatWings", "hat_pkHW01_Mohawk", "hat_pkHW01_Pumpkin", "hat_pkHW01_ScaryBag", "hat_pkHW01_Witch", "hat_pkHW01_Wolf", "hat_pkHW01_Pirate", "hat_pkHW01_Machete", "hat_pk04_Archae", "hat_pk04_Balloon", "hat_pk04_BirdNest", "hat_pk04_Chef", "hat_pk04_CCC", "hat_pk04_Fez", "hat_pk04_GeneralHat", "hat_pk04_Pompadour", "hat_pk04_HunterCap", "hat_pk04_JungleHat", "hat_pk04_MiniCrewmate", "hat_pk04_Vagabond", "hat_pk04_Snowman", "hat_pk05_davehat", "hat_pk05_Ellie", "hat_pk05_Svenhat", "hat_pk05_Burthat", "hat_pk05_Ellryhat", "hat_pk05_Wizardhat", "hat_pk05_cheesetoppat", "hat_pk05_Macbethhat", "hat_pk05_HenryToppat", "hat_pk05_EllieToppat", "hat_pk05_GeoffreyToppat", "hat_Chocolate", "hat_Heart", "hat_Ponytail", "hat_Rubberglove", "hat_Unicorn", "hat_Zipper", "hat_CuppaJoe", "hat_HardtopHat", "hat_Prototype", "hat_Records", "hat_ThomasC", "hat_ToppatHair", "hat_WilfordIV", "hat_Winston", "hat_AbominalHat", "hat_EarmuffGreen", "hat_EarmuffsPink", "hat_EarmuffsYellow", "hat_EarnmuffBlue", "hat_pk04_MinerCap", "hat_MinerBlack", "hat_MinerYellow", "hat_RockIce", "hat_RockLava", "hat_SnowbeanieGreen", "hat_SnowbeanieOrange", "hat_SnowBeaniePurple", "hat_SnowbeanieRed", "hat_WinterHelmet", "hat_pk04_WinterHat", "hat_WinterGreen", "hat_WinterRed", "hat_WinterYellow", "hat_Voleyball", "hat_Basketball", "hat_Bowlingball", "hat_Deitied", "hat_Dodgeball", "hat_DrillMetal", "hat_DrillStone", "hat_DrillWood", "hat_Janitor", "hat_Pot", "hat_Soccer", "hat_Visor", "hat_mira_bush", "hat_mira_case", "hat_mira_cloud", "hat_mira_flower", "hat_mira_flower_red", "hat_mira_gem", "hat_pk03_Headphones", "hat_GovtHeadset", "hat_mira_headset_blue", "hat_mira_headset_pink", "hat_mira_headset_yellow", "hat_mira_leaf", "hat_mira_milk", "hat_pk04_Slippery", "hat_mira_sign_blue", "hat_pk03_Security1", "hat_pk04_Antenna", "hat_Antenna_Black", "hat_astronaut", "hat_Astronaut-Blue", "hat_Astronaut-Cyan", "hat_Astronaut-Orange", "hat_pk04_Bandana", "hat_Bandana_Blue", "hat_Bandana_Green", "hat_Bandana_Pink", "hat_Bandana_Red", "hat_Bandana_White", "hat_Bandana_Yellow", "hat_pk01_BaseballCap", "hat_baseball_Black", "hat_baseball_Green", "hat_baseball_Lightblue", "hat_baseball_LightGreen", "hat_baseball_Lilac", "hat_baseball_Orange", "hat_baseball_Pink", "hat_baseball_Purple", "hat_baseball_Red", "hat_baseball_White", "hat_baseball_Yellow", "hat_pk04_Beanie", "hat_Beanie_Black", "hat_Beanie_Blue", "hat_Beanie_Green", "hat_Beanie_Lightblue", "hat_Beanie_LightGreen", "hat_Beanie_LightPurple", "hat_Beanie_Pink", "hat_Beanie_Purple", "hat_Beanie_White", "hat_Beanie_Yellow", "hat_stethescope", "hat_Doc_black", "hat_Doc_Orange", "hat_Doc_Purple", "hat_Doc_Red", "hat_Doc_White", "hat_pk04_DoRag", "hat_Dorag_Black", "hat_Dorag_Desert", "hat_Dorag_Jungle", "hat_Dorag_Purple", "hat_Dorag_Sky", "hat_Dorag_Snow", "hat_Dorag_Yellow", "hat_pk03_Goggles", "hat_goggles", "hat_Goggles_Black", "hat_Goggles_Chrome", "hat_hardhat", "hat_Hardhat_black", "hat_Hardhat_Blue", "hat_Hardhat_Green", "hat_Hardhat_Orange", "hat_Hardhat_Pink", "hat_Hardhat_Purple", "hat_Hardhat_Red", "hat_Hardhat_White", "hat_brainslug", "hat_headslug_Purple", "hat_headslug_Red", "hat_headslug_Yellow", "hat_headslug_White", "hat_pk02_HeroCap", "hat_Herohood_Black", "hat_Herohood_Blue", "hat_Herohood_Pink", "hat_Herohood_Purple", "hat_Herohood_Red", "hat_Herohood_White", "hat_Herohood_Yellow", "hat_paperhat", "hat_Paperhat_Black", "hat_Paperhat_Blue", "hat_Paperhat_Cyan", "hat_Paperhat_Lightblue", "hat_Paperhat_Pink", "hat_Paperhat_Yellow", "hat_pk02_PlungerHat", "hat_Plunger_Blue", "hat_Plunger_Yellow", "hat_pk04_RamHorns", "hat_Ramhorn_Black", "hat_Ramhorn_Red", "hat_Ramhorn_White", "hat_pk02_TenGallonHat", "hat_TenGallon_Black", "hat_TenGallon_White", "hat_pk03_Traffic", "hat_Traffic_Blue", "hat_Traffic_Red", "hat_Traffic_Yellow", "hat_traffic_purple", "hat_devilhorns_yellow", "hat_arrowhead", "hat_axe", "hat_papermask", "hat_bat_crewcolor", "hat_bat_green", "hat_bat_ice", "hat_bone", "hat_candycorn", "hat_cat_grey", "hat_cat_orange", "hat_cat_pink", "hat_cat_snow", "hat_clown_purple", "hat_devilhorns_crewcolor", "hat_devilhorns_green", "hat_devilhorns_murky", "hat_devilhorns_white", "hat_devilhorns_black", "hat_fairywings", "hat_fishhed", "hat_frankenbolts", "hat_frankenbride", "hat_glowstick", "hat_mohawk_bubblegum", "hat_mohawk_bumblebee", "hat_mohawk_purple_green", "hat_mohawk_rainbow", "hat_mummy", "hat_tombstone", "hat_witch_green", "hat_witch_murky", "hat_witch_pink", "hat_witch_white", "hat_wolf_murky", "hat_wolf_grey", "hat_vi", "hat_caitlin", "hat_clagger", "hat_comper", "hat_enforcer", "hat_heim", "hat_jayce", "hat_jinx" };
					std::vector availableSkins = { "skin_None", "skin_Capt", "skin_Police", "skin_Wall", "skin_Security", "skin_Tarmac", "skin_Archae", "skin_CCC", "skin_rhm", "skin_Bling", "skin_General", "skin_Mech", "skin_MechanicRed", "skin_MilitaryDesert", "skin_Military", "skin_prisoner", "skin_PrisonerBlue", "skin_PrisonerTanskin", "skin_SuitB", "skin_SuitW", "skin_Skin_SuitRedskin", "skin_ToppatSuitFem", "skin_ToppatVest", "skin_SweaterYellowskin", "skin_Winter", "skin_JacketGreenskin", "skin_JacketPurpleskin", "skin_JacketYellowskin", "skin_Abominalskin", "skin_MilitarySnowskin", "skin_Miner", "skin_MinerBlackskin", "skin_RockIceskin", "skin_RockLavaskin", "skin_SweaterBlueskin", "skin_SweaterPinkskin", "skin_Sweaterskin", "skin_SportsRedskin", "skin_D2Cskin", "skin_Janitorskin", "skin_SportsBlueskin", "skin_Bushskin", "skin_BusinessFemskin", "skin_BusinessFem-Aquaskin", "skin_BusinessFem-Tanskin", "skin_Hazmat", "skin_Hazmat-Blackskin", "skin_Hazmat-Blueskin", "skin_Hazmat-Greenskin", "skin_Hazmat-Pinkskin", "skin_Hazmat-Redskin", "skin_Hazmat-Whiteskin", "skin_Astro", "skin_Astronaut-Blueskin", "skin_Astronaut-Cyanskin", "skin_Astronaut-Orangeskin", "skin_Science", "skin_Scientist-Blueskin", "skin_Scientist-Darkskin", "skin_clown", "skin_fairy", "skin_fishmonger", "skin_mummy", "skin_pumpkin", "skin_vampire", "skin_witch", "skin_caitlin", "skin_enforcer", "skin_heim", "skin_jayce", "skin_jinx", "skin_vi" };
					std::vector availableVisors = { "visor_EmptyVisor", "visor_pk01_FredVisor", "hat_geoff", "visor_pk01_MonoclesVisor", "visor_pk01_PaperMaskVisor", "visor_pk01_PlagueVisor", "visor_pk01_RHMVisor", "visor_pk01_Security1Visor", "visor_pk01_AngeryVisor", "visor_BillyG", "visor_Galeforce", "visor_Krieghaus", "visor_Reginald", "visor_Scar", "visor_WinstonStache", "visor_SkiGogglesWhite", "visor_Lava", "visor_polus_ice", "visor_SkiGoggleBlack", "visor_SKiGogglesOrange", "visor_shopglasses", "visor_D2CGoggles", "visor_is_beard", "visor_JanitorStache", "visor_Mouth", "visor_mira_card_blue", "visor_mira_card_red", "visor_mira_glasses", "visor_pk01_HazmatVisor", "visor_mira_mask_black", "visor_mira_mask_blue", "visor_mira_mask_green", "visor_mira_mask_purple", "visor_mira_mask_red", "visor_mira_mask_white", "visor_pk01_DumStickerVisor", "visor_Stickynote_Cyan", "visor_Stickynote_Green", "visor_Stickynote_Orange", "visor_Stickynote_Pink", "visor_Stickynote_Purple", "visor_Blush", "visor_Bomba", "visor_Carrot", "visor_Crack", "visor_Dirty", "visor_Dotdot", "visor_EyepatchL", "visor_EyepatchR", "visor_LolliBlue", "visor_LolliBrown", "visor_LolliOrange", "visor_LolliRed", "visor_PiercingL", "visor_PiercingR", "visor_SciGoggles", "visor_SmallGlassesBlue", "visor_SmallGlasses", "visor_SmallGlassesRed", "visor_Straw", "visor_eyeball", "visor_clownnose", "visor_masque_blue", "visor_masque_green", "visor_masque_red", "visor_masque_white", "visor_mummy", "visor_heim", "visor_jinx" };
					std::vector availablePets = { "pet_EmptyPet", "pet_Alien", "pet_Crewmate", "pet_Doggy", "pet_Stickmin", "pet_Hamster", "pet_Robot", "pet_UFO", "pet_Ellie", "pet_Squig", "pet_Bedcrab", "pet_test", "pet_Lava", "pet_Snow", "pet_Charles", "pet_Charles_Red", "pet_Cube", "pet_Bush", "pet_frankendog", "pet_poro" };
					std::vector availableNamePlates = { "nameplate_NoPlate", "nameplate_airship_Toppat", "nameplate_airship_CCC", "nameplate_airship_Diamond", "nameplate_airship_Emerald", "nameplate_airship_Gems", "nameplate_airship_government", "nameplate_Airship_Hull", "nameplate_airship_Ruby", "nameplate_airship_Sky", "nameplate_Polus-Skyline", "nameplate_Polus-Snowmates", "nameplate_Polus_Colors", "nameplate_Polus_DVD", "nameplate_Polus_Ground", "nameplate_Polus_Lava", "nameplate_Polus_Planet", "nameplate_Polus_Snow", "nameplate_Polus_SpecimenBlue", "nameplate_Polus_SpecimenGreen", "nameplate_Polus_SpecimenPurple", "nameplate_is_yard", "nameplate_is_dig", "nameplate_is_game", "nameplate_is_ghost", "nameplate_is_green", "nameplate_is_sand", "nameplate_is_trees", "nameplate_Mira_Cafeteria", "nameplate_Mira_Glass", "nameplate_Mira_Tiles", "nameplate_Mira_Vines", "nameplate_Mira_Wood", "nameplate_hw_candy", "nameplate_hw_woods", "nameplate_hw_pumpkin" };
					for (auto player : GetAllPlayerControl()) {
						queue->push(new RpcForceName(player, GenerateRandomString()));
						queue->push(new RpcForceColor(player, randi(0, 17)));
						queue->push(new RpcForceHat(player, convert_to_string(availableHats[randi(0, availableHats.size() - 1)])));
						queue->push(new RpcForceSkin(player, convert_to_string(availableSkins[randi(0, availableSkins.size() - 1)])));
						queue->push(new RpcForceVisor(player, convert_to_string(availableVisors[randi(0, availableVisors.size() - 1)])));
						queue->push(new RpcForcePet(player, convert_to_string(availablePets[randi(0, availablePets.size() - 1)])));
						queue->push(new RpcForceNamePlate(player, convert_to_string(availableNamePlates[randi(0, availableNamePlates.size() - 1)])));
					}
				}
				ImGui::Text("Confuse when:");
				if (ImGui::Checkbox("Joining Lobby", &State.confuseOnJoin)) {
					State.Save();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Game Starts", &State.confuseOnStart)) {
					State.Save();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Killing", &State.confuseOnKill)) {
					State.Save();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Venting", &State.confuseOnVent)) {
					State.Save();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Meeting", &State.confuseOnMeeting)) {
					State.Save();
				}
			}
			
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Checkbox("Console", &State.ShowConsole)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Game Chat", &State.ShowChat)) {
				State.Save();
			}
			if (State.ShowKeybinds) {
				ImGui::SameLine();
				if (HotKey(State.KeyBinds.Toggle_Chat)) {
					State.Save();
				}
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			static int framesPassed = -1;
			Vector2 previousPlayerPosition = {0.0f, 0.0f};

			if (IsHost() && IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ImGui::Button("Revive Yourself"))
			{
				previousPlayerPosition = GetTrueAdjustedPosition(*Game::pLocalPlayer);
				app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
				State.rpcQueue.push(new RpcRevive(*Game::pLocalPlayer));
				State.rpcQueue.push(new RpcForceColor(*Game::pLocalPlayer, outfit->fields.ColorId, true));
				framesPassed = 40;
			}
			
			if (framesPassed == 20)
			{
				State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, false));
				if (State.mapType == Settings::MapType::Ship) {
					/*if (options.GetByte(app::ByteOptionNames__Enum::MapId) == 3)
						State.rpcQueue.push(new RpcSnapTo({ -9.38308f, -6.0749207f }));
					else*/
						State.rpcQueue.push(new RpcSnapTo({ 9.38308f, -6.0749207f }));
				}
				else if (State.mapType == Settings::MapType::Hq)
					State.rpcQueue.push(new RpcSnapTo({ 23.769283f, -1.576561f }));
				else if (State.mapType == Settings::MapType::Pb)
					State.rpcQueue.push(new RpcSnapTo({ 6.8989105f, -14.047455f }));
				else if (State.mapType == Settings::MapType::Airship)
					State.rpcQueue.push(new RpcSnapTo({ -22.099f, -1.152f }));
				framesPassed--;
			}
			else if (framesPassed == 0)
			{
				//State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, true)); for showing you as alive to ALL players
				framesPassed--;
			}
			else framesPassed--;

			if (IsInGame() && (*Game::pLocalPlayer)->fields.inVent && ImGui::Button("Force Exit Vent"))
			{
				State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, true));
			}
			
			if ((State.mapType == Settings::MapType::Airship) && IsHost() && IsInGame() && ImGui::Button("Switch Moving Platform Side"))
			{
				State.rpcQueue.push(new RpcUsePlatform());
			}

			if (ImGui::Checkbox("Spam Report", &State.SpamReport)) {
				State.Save();
			}

			if ((IsHost() || !State.SafeMode) && State.InMeeting && ImGui::Button("End Meeting")) {
				State.rpcQueue.push(new RpcEndMeeting());
				State.InMeeting = false;
			}

			if (IsHost()) {
				if (ImGui::Checkbox("Disable Game Ending", &State.NoGameEnd)) {
					State.Save();
				}
			}
			if (IsHost()) {
				CustomListBoxInt("End Reason", &State.SelectedGameEndReasonId, GAMEENDREASON, 120.0f * State.dpiScale);

				if (IsInMultiplayerGame())
					ImGui::SameLine();

				if (IsInMultiplayerGame() && ImGui::Button("End Game")) {
					if (State.SelectedGameEndReasonId == 0)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HumansByVote));
					else if (State.SelectedGameEndReasonId == 1)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HumansByTask));
					else if (State.SelectedGameEndReasonId == 2)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::ImpostorByVote));
					else if (State.SelectedGameEndReasonId == 3)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::ImpostorByKill));
					else if (State.SelectedGameEndReasonId == 4)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::ImpostorBySabotage));
					else if (State.SelectedGameEndReasonId == 5)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::ImpostorDisconnect));
					else if (State.SelectedGameEndReasonId == 6)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HumansDisconnect));
					else if (State.SelectedGameEndReasonId == 7)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HideAndSeek_ByTimer));
					else if (State.SelectedGameEndReasonId == 8)
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HideAndSeek_ByKills));
					else
						State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum::HumansDisconnect));
				}
			}

			if ((IsHost() || !State.SafeMode) && ImGui::Checkbox("Force Name for Everyone", &State.ForceNameForEveryone)) {
				State.Save();
			}
			char* nameBufferHost[255]{ const_cast<char*>(State.hostUserName.c_str()) };
			if ((IsHost() || !State.SafeMode) && ImGui::InputText("Username", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
				State.hostUserName = std::string(*nameBufferHost);
			}
			
			if (IsHost()) {
				CustomListBoxInt(" ­", &State.HostSelectedColorId, HOSTCOLORS, 85.0f * State.dpiScale);
				ImGui::SameLine();
			}
			
			if (IsHost() && ImGui::Checkbox("Force Color for Everyone", &State.ForceColorForEveryone)) {
				State.Save();
			}

			if (IsInGame() || IsInLobby())
			{
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				ImGui::Separator();
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

				std::string hostText = std::format("Host: {}", GetHostUsername());
				ImGui::Text(const_cast<char*>(hostText.c_str()));

				if (options.GetGameMode() == GameModes__Enum::Normal)
				{
					auto allPlayers = GetAllPlayerControl();
					RoleRates roleRates = RoleRates(options, (int)allPlayers.size());
					// this should be all the major ones. if people want more they're simple enough to add.
					ImGui::Text("Visual Tasks: %s", (options.GetBool(app::BoolOptionNames__Enum::VisualTasks) ? "On" : "Off"));
					int TaskBarUpdates = options.GetInt(app::Int32OptionNames__Enum::TaskBarMode);
					if (TaskBarUpdates == 0)
						ImGui::Text("Taskbar Update Mode: Always");
					else if (TaskBarUpdates == 1)
						ImGui::Text("Taskbar Update Mode: Meetings");
					else if (TaskBarUpdates == 2)
						ImGui::Text("Taskbar Update Mode: Never");
					else
						ImGui::Text("Taskbar Update Mode: Other");
					ImGui::Text("Confirm Ejects: %s", (options.GetBool(app::BoolOptionNames__Enum::ConfirmImpostor) ? "On" : "Off"));
					ImGui::Text("Kill Cooldown: %.2f s", options.GetKillCooldown());
					int KillDistance = options.GetInt(app::Int32OptionNames__Enum::KillDistance);
					if (KillDistance == 0)
						ImGui::Text("Kill Distance: Short");
					else if (KillDistance == 1)
						ImGui::Text("Kill Distance: Medium");
					else if (KillDistance == 2)
						ImGui::Text("Kill Distance: Long");
					else
						ImGui::Text("Kill Distance: Other");

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Engineers: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Engineer));
					ImGui::Text("Engineer Vent Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::EngineerCooldown, 1.0F));
					ImGui::Text("Engineer Duration in Vent: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::EngineerInVentMaxTime, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Scientists: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Scientist));
					ImGui::Text("Scientist Vitals Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ScientistCooldown, 1.0F));
					ImGui::Text("Scientist Battery Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ScientistBatteryCharge, 1.0F));

					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);

					ImGui::Text("Max Guardian Angels: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::GuardianAngel));
					ImGui::Text("Guardian Angel Protect Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 1.0F));
					ImGui::Text("Guardian Angel Protection Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Shapeshifters: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Shapeshifter));
					ImGui::Text("Shapeshifter Shift Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterCooldown, 1.0F));
					ImGui::Text("Shapeshifter Shift Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterDuration, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
				}
				else if (options.GetGameMode() == GameModes__Enum::HideNSeek) {

					int ImpostorId = options.GetInt(app::Int32OptionNames__Enum::ImpostorPlayerID);
					if (ImpostorId <= -1) {
						ImGui::Text("Impostor: Round-robin");
					}
					else {
						std::string ImpostorName = std::format("Selected Impostor: {}", convert_from_string(GameData_PlayerOutfit_get_PlayerName(GetPlayerOutfit(GetPlayerDataById(ImpostorId)), nullptr)));
						ImGui::Text(const_cast<char*>(ImpostorName.c_str()));
					}
					ImGui::Text("Flashlight Mode: %s", (options.GetBool(app::BoolOptionNames__Enum::UseFlashlight) ? "On" : "Off"));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Vent Uses: %d", options.GetInt(app::Int32OptionNames__Enum::CrewmateVentUses));
					ImGui::Text("Duration in Vent: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::CrewmateTimeInVent, 1.0F));
					
					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);

					ImGui::Text("Hiding Time: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::EscapeTime, 1.0F));
					ImGui::Text("Final Hiding Time: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::FinalEscapeTime, 1.0F));
					ImGui::Text("Final Impostor Speed: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::SeekerFinalSpeed, 1.0F));
				}
			}
			ImGui::EndTabItem();
		}
	}
}
