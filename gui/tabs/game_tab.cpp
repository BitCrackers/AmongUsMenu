#include "pch-il2cpp.h"
#include "game_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"
#include "esp.hpp"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			GameOptions options;
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (SteppedSliderFloat("Player Speed Multiplier", &State.PlayerSpeed, 0.f, 10.f, 0.05f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.PrevPlayerSpeed = State.PlayerSpeed;
			}
			if (SteppedSliderFloat("Kill Distance", &State.KillDistance, 0.f, 20.f, 0.1f, "%.1f m", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.PrevKillDistance = State.KillDistance;
			}
			/*if (GameOptions().GetGameMode() == GameModes__Enum::Normal) {
				if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES, 225 * State.dpiScale))
					State.PrevTaskBarUpdates = State.TaskBarUpdates;
			}*/
			if (ImGui::Checkbox("No Ability Cooldown", &State.NoAbilityCD)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Multiply Speed", &State.MultiplySpeed)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Modify Kill Distance", &State.ModifyKillDistance)) {
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

			uint8_t validColorId = 0;
			if ((size_t)State.SelectedColorId < COLORS.size()) {
				validColorId = (uint8_t)State.SelectedColorId;
				State.Save();
			}
			if (IsHost() || !State.SafeMode) {
				ImGui::SameLine(87 * State.dpiScale);
				CustomListBoxInt(" ", &State.SelectedColorId, HOSTCOLORS, 85.0f * State.dpiScale);
			}
			else {
				ImGui::SameLine(87 * State.dpiScale);
				if ((size_t)State.SelectedColorId >= COLORS.size()) {
					State.SelectedColorId = (int)validColorId;
					State.Save();
				}
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
			if (ImGui::InputTextMultiline("\n\n\n\n\nChat Message", *msgBuffer, IM_ARRAYSIZE(msgBuffer))) {
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
			ImGui::SameLine();
			if (ImGui::Checkbox("Spam", &State.ChatSpam))
			{
				State.Save();
			}
			if (!State.SafeMode && State.ChatSpam && ImGui::Checkbox("Spam by Everyone", &State.ChatSpamEveryone))
			{
				State.Save();
			}

			/*if (IsInGame() && ImGui::Button("Boot Everyone from Vents")) {
				int minCount = 0;
				int maxCount = 0;
				if (State.mapType == Settings::MapType::Ship)
					maxCount = 13;
				else if (State.mapType == Settings::MapType::Hq) {
					minCount = 1; maxCount = 11;
				}
				else if (State.mapType == Settings::MapType::Pb || State.mapType == Settings::MapType::Airship)
					maxCount = 11;
				else if (State.mapType == Settings::MapType::Fungle)
					maxCount = 10;
				int i = maxCount;
				if (i >= minCount) {
					State.rpcQueue.push(new RpcBootFromVent(i)); --i;
				}
			}*/
			
			if (ImGui::Checkbox("Cycler", &State.Cycler)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Cycle in Meeting", &State.CycleInMeeting)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Cycle Between Players", &State.CycleBetweenPlayers)) {
				State.Save();
			}

			if (SteppedSliderFloat("Cycle Timer", &State.CycleTimer, 0.2f, 1.f, 0.02f, "%.2fs", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.PrevCycleTimer = State.CycleTimer;
				State.CycleDuration = State.CycleTimer * 50;
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (ImGui::CollapsingHeader("Cycler Options")) {
				/* {
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
				}*/

				if (ImGui::CollapsingHeader("Cycler Name Options")) {
					if (CustomListBoxInt("Random Name Generation", &State.cyclerNameGeneration, NAMEGENERATION, 75 * State.dpiScale)) {
						State.Save();
					}
					if (State.cyclerNameGeneration == 2) {
						if (State.cyclerUserNames.empty())
							ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username generation will fall back to word combo as you have no names in the cycler.");
						static std::string newName = "";
						char* newNameBuffer[255]{ const_cast<char*>(newName.c_str()) };
						if (ImGui::InputText("New Name", *newNameBuffer, IM_ARRAYSIZE(newNameBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
							newName = std::string(*newNameBuffer);
						ImGui::SameLine();
						if (ImGui::Button("Add Name")) {
							State.cyclerUserNames.push_back((std::string)*newNameBuffer);
							State.Save();
							newName = "";
						}
						if (!(IsHost() || !State.SafeMode)) {
							if (newName.length() >= (size_t)13)
								ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username is too long, gets detected by anticheat. This name will be ignored.");
							else if (!IsNameValid(newName))
								ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username contains characters blocked by anticheat. This name will be ignored.");
						}
						if (!State.cyclerUserNames.empty()) {
							int selectedNameIndex = 0;
							selectedNameIndex = std::clamp(selectedNameIndex, 0, (int)State.cyclerUserNames.size() - 1);
							std::vector<const char*> nameVector(State.cyclerUserNames.size(), nullptr);
							for (size_t i = 0; i < State.cyclerUserNames.size(); i++) {
								nameVector[i] = State.cyclerUserNames[i].c_str();
							}
							CustomListBoxInt("Select Name to Delete", &selectedNameIndex, nameVector);
							ImGui::SameLine();
							if (ImGui::Button("Delete"))
								State.cyclerUserNames.erase(State.cyclerUserNames.begin() + selectedNameIndex);
						}
					}
				}

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

			if (ImGui::CollapsingHeader("Confuser Options")) {
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
					std::vector availableHats = { "hat_NoHat", "hat_AbominalHat", "hat_anchor", "hat_antenna", "hat_Antenna_Black", "hat_arrowhead", "hat_Astronaut-Blue", "hat_Astronaut-Cyan", "hat_Astronaut-Orange", "hat_astronaut", "hat_axe", "hat_babybean", "hat_Baguette", "hat_BananaGreen", "hat_BananaPurple", "hat_bandanaWBY", "hat_Bandana_Blue", "hat_Bandana_Green", "hat_Bandana_Pink", "hat_Bandana_Red", "hat_Bandana_White", "hat_Bandana_Yellow", "hat_baseball_Black", "hat_baseball_Green", "hat_baseball_Lightblue", "hat_baseball_LightGreen", "hat_baseball_Lilac", "hat_baseball_Orange", "hat_baseball_Pink", "hat_baseball_Purple", "hat_baseball_Red", "hat_baseball_White", "hat_baseball_Yellow", "hat_Basketball", "hat_bat_crewcolor", "hat_bat_green", "hat_bat_ice", "hat_beachball", "hat_Beanie_Black", "hat_Beanie_Blue", "hat_Beanie_Green", "hat_Beanie_Lightblue", "hat_Beanie_LightGreen", "hat_Beanie_LightPurple", "hat_Beanie_Pink", "hat_Beanie_Purple", "hat_Beanie_White", "hat_Beanie_Yellow", "hat_bearyCold", "hat_bone", "hat_Bowlingball", "hat_brainslug", "hat_BreadLoaf", "hat_bucket", "hat_bucketHat", "hat_bushhat", "hat_Butter", "hat_caiatl", "hat_caitlin", "hat_candycorn", "hat_captain", "hat_cashHat", "hat_cat_grey", "hat_cat_orange", "hat_cat_pink", "hat_cat_snow", "hat_chalice", "hat_cheeseBleu", "hat_cheeseMoldy", "hat_cheeseSwiss", "hat_ChefWhiteBlue", "hat_cherryOrange", "hat_cherryPink", "hat_Chocolate", "hat_chocolateCandy", "hat_chocolateMatcha", "hat_chocolateVanillaStrawb", "hat_clagger", "hat_clown_purple", "hat_comper", "hat_croissant", "hat_crownBean", "hat_crownDouble", "hat_crownTall", "hat_CuppaJoe", "hat_Deitied", "hat_devilhorns_black", "hat_devilhorns_crewcolor", "hat_devilhorns_green", "hat_devilhorns_murky", "hat_devilhorns_white", "hat_devilhorns_yellow", "hat_Doc_black", "hat_Doc_Orange", "hat_Doc_Purple", "hat_Doc_Red", "hat_Doc_White", "hat_Dodgeball", "hat_Dorag_Black", "hat_Dorag_Desert", "hat_Dorag_Jungle", "hat_Dorag_Purple", "hat_Dorag_Sky", "hat_Dorag_Snow", "hat_Dorag_Yellow", "hat_doubletophat", "hat_DrillMetal", "hat_DrillStone", "hat_DrillWood", "hat_EarmuffGreen", "hat_EarmuffsPink", "hat_EarmuffsYellow", "hat_EarnmuffBlue", "hat_eggGreen", "hat_eggYellow", "hat_enforcer", "hat_erisMorn", "hat_fairywings", "hat_fishCap", "hat_fishhed", "hat_fishingHat", "hat_flowerpot", "hat_frankenbolts", "hat_frankenbride", "hat_fungleFlower", "hat_geoff", "hat_glowstick", "hat_glowstickCyan", "hat_glowstickOrange", "hat_glowstickPink", "hat_glowstickPurple", "hat_glowstickYellow", "hat_goggles", "hat_Goggles_Black", "hat_Goggles_Chrome", "hat_GovtDesert", "hat_GovtHeadset", "hat_halospartan", "hat_hardhat", "hat_Hardhat_black", "hat_Hardhat_Blue", "hat_Hardhat_Green", "hat_Hardhat_Orange", "hat_Hardhat_Pink", "hat_Hardhat_Purple", "hat_Hardhat_Red", "hat_Hardhat_White", "hat_HardtopHat", "hat_headslug_Purple", "hat_headslug_Red", "hat_headslug_White", "hat_headslug_Yellow", "hat_Heart", "hat_heim", "hat_Herohood_Black", "hat_Herohood_Blue", "hat_Herohood_Pink", "hat_Herohood_Purple", "hat_Herohood_Red", "hat_Herohood_Yellow", "hat_hl_fubuki", "hat_hl_gura", "hat_hl_korone", "hat_hl_marine", "hat_hl_mio", "hat_hl_moona", "hat_hl_okayu", "hat_hl_pekora", "hat_hl_risu", "hat_hl_watson", "hat_hunter", "hat_IceCreamMatcha", "hat_IceCreamMint", "hat_IceCreamNeo", "hat_IceCreamStrawberry", "hat_IceCreamUbe", "hat_IceCreamVanilla", "hat_Igloo", "hat_Janitor", "hat_jayce", "hat_jinx", "hat_killerplant", "hat_lilShroom", "hat_maraSov", "hat_mareLwyd", "hat_military", "hat_MilitaryWinter", "hat_MinerBlack", "hat_MinerYellow", "hat_mira_bush", "hat_mira_case", "hat_mira_cloud", "hat_mira_flower", "hat_mira_flower_red", "hat_mira_gem", "hat_mira_headset_blue", "hat_mira_headset_pink", "hat_mira_headset_yellow", "hat_mira_leaf", "hat_mira_milk", "hat_mira_sign_blue", "hat_mohawk_bubblegum", "hat_mohawk_bumblebee", "hat_mohawk_purple_green", "hat_mohawk_rainbow", "hat_mummy", "hat_mushbuns", "hat_mushroomBeret", "hat_mysteryBones", "hat_NewYear2023", "hat_OrangeHat", "hat_osiris", "hat_pack01_Astronaut0001", "hat_pack02_Tengallon0001", "hat_pack02_Tengallon0002", "hat_pack03_Stickynote0004", "hat_pack04_Geoffmask0001", "hat_pack06holiday_candycane0001", "hat_PancakeStack", "hat_paperhat", "hat_Paperhat_Black", "hat_Paperhat_Blue", "hat_Paperhat_Cyan", "hat_Paperhat_Lightblue", "hat_Paperhat_Pink", "hat_Paperhat_Yellow", "hat_papermask", "hat_partyhat", "hat_pickaxe", "hat_Pineapple", "hat_PizzaSliceHat", "hat_pk01_BaseballCap", "hat_pk02_Crown", "hat_pk02_Eyebrows", "hat_pk02_HaloHat", "hat_pk02_HeroCap", "hat_pk02_PipCap", "hat_pk02_PlungerHat", "hat_pk02_ScubaHat", "hat_pk02_StickminHat", "hat_pk02_StrawHat", "hat_pk02_TenGallonHat", "hat_pk02_ThirdEyeHat", "hat_pk02_ToiletPaperHat", "hat_pk02_Toppat", "hat_pk03_Fedora", "hat_pk03_Goggles", "hat_pk03_Headphones", "hat_pk03_Security1", "hat_pk03_StrapHat", "hat_pk03_Traffic", "hat_pk04_Antenna", "hat_pk04_Archae", "hat_pk04_Balloon", "hat_pk04_Banana", "hat_pk04_Bandana", "hat_pk04_Beanie", "hat_pk04_Bear", "hat_pk04_BirdNest", "hat_pk04_CCC", "hat_pk04_Chef", "hat_pk04_DoRag", "hat_pk04_Fez", "hat_pk04_GeneralHat", "hat_pk04_HunterCap", "hat_pk04_JungleHat", "hat_pk04_MinerCap", "hat_pk04_MiniCrewmate", "hat_pk04_Pompadour", "hat_pk04_RamHorns", "hat_pk04_Slippery", "hat_pk04_Snowman", "hat_pk04_Vagabond", "hat_pk04_WinterHat", "hat_pk05_Burthat", "hat_pk05_Cheese", "hat_pk05_cheesetoppat", "hat_pk05_Cherry", "hat_pk05_davehat", "hat_pk05_Egg", "hat_pk05_Ellie", "hat_pk05_EllieToppat", "hat_pk05_Ellryhat", "hat_pk05_Fedora", "hat_pk05_Flamingo", "hat_pk05_FlowerPin", "hat_pk05_GeoffreyToppat", "hat_pk05_Helmet", "hat_pk05_HenryToppat", "hat_pk05_Macbethhat", "hat_pk05_Plant", "hat_pk05_RHM", "hat_pk05_Svenhat", "hat_pk05_Wizardhat", "hat_pk06_Candycanes", "hat_pk06_ElfHat", "hat_pk06_Lights", "hat_pk06_Present", "hat_pk06_Reindeer", "hat_pk06_Santa", "hat_pk06_Snowman", "hat_pk06_tree", "hat_pkHW01_BatWings", "hat_pkHW01_CatEyes", "hat_pkHW01_Horns", "hat_pkHW01_Machete", "hat_pkHW01_Mohawk", "hat_pkHW01_Pirate", "hat_pkHW01_PlagueHat", "hat_pkHW01_Pumpkin", "hat_pkHW01_ScaryBag", "hat_pkHW01_Witch", "hat_pkHW01_Wolf", "hat_Plunger_Blue", "hat_Plunger_Yellow", "hat_police", "hat_Ponytail", "hat_Pot", "hat_Present", "hat_Prototype", "hat_pusheenGreyHat", "hat_PusheenicornHat", "hat_pusheenMintHat", "hat_pusheenPinkHat", "hat_pusheenPurpleHat", "hat_pusheenSitHat", "hat_pusheenSleepHat", "hat_pyramid", "hat_rabbitEars", "hat_Ramhorn_Black", "hat_Ramhorn_Red", "hat_Ramhorn_White", "hat_ratchet", "hat_Records", "hat_RockIce", "hat_RockLava", "hat_Rubberglove", "hat_Rupert", "hat_russian", "hat_saint14", "hat_sausage", "hat_savathun", "hat_schnapp", "hat_screamghostface", "hat_Scrudge", "hat_sharkfin", "hat_shaxx", "hat_shovel", "hat_SlothHat", "hat_SnowbeanieGreen", "hat_SnowbeanieOrange", "hat_SnowBeaniePurple", "hat_SnowbeanieRed", "hat_Snowman", "hat_Soccer", "hat_Sorry", "hat_starBalloon", "hat_starhorse", "hat_Starless", "hat_StarTopper", "hat_stethescope", "hat_StrawberryLeavesHat", "hat_TenGallon_Black", "hat_TenGallon_White", "hat_ThomasC", "hat_tinFoil", "hat_titan", "hat_ToastButterHat", "hat_tombstone", "hat_tophat", "hat_ToppatHair", "hat_towelwizard", "hat_Traffic_Blue", "hat_traffic_purple", "hat_Traffic_Red", "hat_Traffic_Yellow", "hat_Unicorn", "hat_vi", "hat_viking", "hat_Visor", "hat_Voleyball", "hat_w21_candycane_blue", "hat_w21_candycane_bubble", "hat_w21_candycane_chocolate", "hat_w21_candycane_mint", "hat_w21_elf_pink", "hat_w21_elf_swe", "hat_w21_gingerbread", "hat_w21_holly", "hat_w21_krampus", "hat_w21_lights_white", "hat_w21_lights_yellow", "hat_w21_log", "hat_w21_mistletoe", "hat_w21_mittens", "hat_w21_nutcracker", "hat_w21_pinecone", "hat_w21_present_evil", "hat_w21_present_greenyellow", "hat_w21_present_redwhite", "hat_w21_present_whiteblue", "hat_w21_santa_evil", "hat_w21_santa_green", "hat_w21_santa_mint", "hat_w21_santa_pink", "hat_w21_santa_white", "hat_w21_santa_yellow", "hat_w21_snowflake", "hat_w21_snowman", "hat_w21_snowman_evil", "hat_w21_snowman_greenred", "hat_w21_snowman_redgreen", "hat_w21_snowman_swe", "hat_w21_winterpuff", "hat_wallcap", "hat_warlock", "hat_whitetophat", "hat_wigJudge", "hat_wigTall", "hat_WilfordIV", "hat_Winston", "hat_WinterGreen", "hat_WinterHelmet", "hat_WinterRed", "hat_WinterYellow", "hat_witch_green", "hat_witch_murky", "hat_witch_pink", "hat_witch_white", "hat_wolf_grey", "hat_wolf_murky", "hat_Zipper" };
					std::vector availableSkins = { "skin_None", "skin_Abominalskin", "skin_ApronGreen", "skin_Archae", "skin_Astro", "skin_Astronaut-Blueskin", "skin_Astronaut-Cyanskin", "skin_Astronaut-Orangeskin", "skin_Bananaskin", "skin_benoit", "skin_Bling", "skin_BlueApronskin", "skin_BlueSuspskin", "skin_Box1skin", "skin_BubbleWrapskin", "skin_Burlapskin", "skin_BushSign1skin", "skin_Bushskin", "skin_BusinessFem-Aquaskin", "skin_BusinessFem-Tanskin", "skin_BusinessFemskin", "skin_caitlin", "skin_Capt", "skin_CCC", "skin_ChefBlackskin", "skin_ChefBlue", "skin_ChefRed", "skin_clown", "skin_D2Cskin", "skin_D2Hunter", "skin_D2Osiris", "skin_D2Saint14", "skin_D2Shaxx", "skin_D2Titan", "skin_D2Warlock", "skin_enforcer", "skin_fairy", "skin_FishingSkinskin", "skin_fishmonger", "skin_FishSkinskin", "skin_General", "skin_greedygrampaskin", "skin_halospartan", "skin_Hazmat-Blackskin", "skin_Hazmat-Blueskin", "skin_Hazmat-Greenskin", "skin_Hazmat-Pinkskin", "skin_Hazmat-Redskin", "skin_Hazmat-Whiteskin", "skin_Hazmat", "skin_heim", "skin_hl_fubuki", "skin_hl_gura", "skin_hl_korone", "skin_hl_marine", "skin_hl_mio", "skin_hl_moona", "skin_hl_okayu", "skin_hl_pekora", "skin_hl_risu", "skin_hl_watson", "skin_Horse1skin", "skin_Hotdogskin", "skin_InnerTubeSkinskin", "skin_JacketGreenskin", "skin_JacketPurpleskin", "skin_JacketYellowskin", "skin_Janitorskin", "skin_jayce", "skin_jinx", "skin_LifeVestSkinskin", "skin_Mech", "skin_MechanicRed", "skin_Military", "skin_MilitaryDesert", "skin_MilitarySnowskin", "skin_Miner", "skin_MinerBlackskin", "skin_mummy", "skin_OrangeSuspskin", "skin_PinkApronskin", "skin_PinkSuspskin", "skin_Police", "skin_presentskin", "skin_prisoner", "skin_PrisonerBlue", "skin_PrisonerTanskin", "skin_pumpkin", "skin_PusheenGreyskin", "skin_Pusheenicornskin", "skin_PusheenMintskin", "skin_PusheenPinkskin", "skin_PusheenPurpleskin", "skin_ratchet", "skin_rhm", "skin_RockIceskin", "skin_RockLavaskin", "skin_Sack1skin", "skin_scarfskin", "skin_Science", "skin_Scientist-Blueskin", "skin_Scientist-Darkskin", "skin_screamghostface", "skin_Security", "skin_Skin_SuitRedskin", "skin_Slothskin", "skin_SportsBlueskin", "skin_SportsRedskin", "skin_SuitB", "skin_SuitW", "skin_SweaterBlueskin", "skin_SweaterPinkskin", "skin_Sweaterskin", "skin_SweaterYellowskin", "skin_Tarmac", "skin_ToppatSuitFem", "skin_ToppatVest", "skin_uglysweaterskin", "skin_vampire", "skin_vi", "skin_w21_deer", "skin_w21_elf", "skin_w21_msclaus", "skin_w21_nutcracker", "skin_w21_santa", "skin_w21_snowmate", "skin_w21_tree", "skin_Wall", "skin_Winter", "skin_witch", "skin_YellowApronskin", "skin_YellowSuspskin" };
					std::vector availableVisors = { "visor_EmptyVisor", "visor_anime", "visor_BaconVisor", "visor_BananaVisor", "visor_beautyMark", "visor_BillyG", "visor_Blush", "visor_Bomba", "visor_BubbleBumVisor", "visor_Candycane", "visor_Carrot", "visor_chimkin", "visor_clownnose", "visor_Crack", "visor_CucumberVisor", "visor_D2CGoggles", "visor_Dirty", "visor_Dotdot", "visor_doubleeyepatch", "visor_eliksni", "visor_erisBandage", "visor_eyeball", "visor_EyepatchL", "visor_EyepatchR", "visor_fishhook", "visor_Galeforce", "visor_heim", "visor_hl_ah", "visor_hl_bored", "visor_hl_hmph", "visor_hl_marine", "visor_hl_nothoughts", "visor_hl_nudge", "visor_hl_smug", "visor_hl_sweepy", "visor_hl_teehee", "visor_hl_wrong", "visor_IceBeard", "visor_IceCreamChocolateVisor", "visor_IceCreamMintVisor", "visor_IceCreamStrawberryVisor", "visor_IceCreamUbeVisor", "visor_is_beard", "visor_JanitorStache", "visor_jinx", "visor_Krieghaus", "visor_Lava", "visor_LolliBlue", "visor_LolliBrown", "visor_LolliOrange", "visor_lollipopCrew", "visor_lollipopLemon", "visor_lollipopLime", "visor_LolliRed", "visor_marshmallow", "visor_masque_blue", "visor_masque_green", "visor_masque_red", "visor_masque_white", "visor_mira_card_blue", "visor_mira_card_red", "visor_mira_glasses", "visor_mira_mask_black", "visor_mira_mask_blue", "visor_mira_mask_green", "visor_mira_mask_purple", "visor_mira_mask_red", "visor_mira_mask_white", "visor_Mouth", "visor_mummy", "visor_PiercingL", "visor_PiercingR", "visor_PizzaVisor", "visor_pk01_AngeryVisor", "visor_pk01_DumStickerVisor", "visor_pk01_FredVisor", "visor_pk01_HazmatVisor", "visor_pk01_MonoclesVisor", "visor_pk01_PaperMaskVisor", "visor_pk01_PlagueVisor", "visor_pk01_RHMVisor", "visor_pk01_Security1Visor", "visor_Plsno", "visor_polus_ice", "visor_pusheenGorgeousVisor", "visor_pusheenKissyVisor", "visor_pusheenKoolKatVisor", "visor_pusheenOmNomNomVisor", "visor_pusheenSmileVisor", "visor_pusheenYaaaaaayVisor", "visor_Reginald", "visor_Rudolph", "visor_savathun", "visor_Scar", "visor_SciGoggles", "visor_shopglasses", "visor_shuttershadesBlue", "visor_shuttershadesLime", "visor_shuttershadesPink", "visor_shuttershadesPurple", "visor_shuttershadesWhite", "visor_shuttershadesYellow", "visor_SkiGoggleBlack", "visor_SKiGogglesOrange", "visor_SkiGogglesWhite", "visor_SmallGlasses", "visor_SmallGlassesBlue", "visor_SmallGlassesRed", "visor_starfish", "visor_Stealthgoggles", "visor_Stickynote_Cyan", "visor_Stickynote_Green", "visor_Stickynote_Orange", "visor_Stickynote_Pink", "visor_Stickynote_Purple", "visor_Straw", "visor_sunscreenv", "visor_teary", "visor_ToastVisor", "visor_tvColorTest", "visor_vr_Vr-Black", "visor_vr_Vr-White", "visor_w21_carrot", "visor_w21_nutstache", "visor_w21_nye", "visor_w21_santabeard", "visor_wash", "visor_WinstonStache" };
					std::vector availablePets = { "pet_EmptyPet", "pet_Alien", "pet_Bedcrab", "pet_BredPet", "pet_Bush", "pet_Charles", "pet_Charles_Red", "pet_ChewiePet", "pet_clank", "pet_coaltonpet", "pet_Creb", "pet_Crewmate", "pet_Cube", "pet_D2GhostPet", "pet_D2PoukaPet", "pet_D2WormPet", "pet_Doggy", "pet_Ellie", "pet_frankendog", "pet_GuiltySpark", "pet_HamPet", "pet_Hamster", "pet_HolidayHamPet", "pet_Lava", "pet_nuggetPet", "pet_Pip", "pet_poro", "pet_Pusheen", "pet_Robot", "pet_Snow", "pet_Squig", "pet_Stickmin", "pet_Stormy", "pet_test", "pet_UFO", "pet_YuleGoatPet" };
					std::vector availableNamePlates = { "nameplate_NoPlate", "nameplate_cliffs", "nameplate_grill", "nameplate_plant", "nameplate_sandcastle", "nameplate_zipline", "nameplate_pusheen_01", "nameplate_pusheen_02", "nameplate_pusheen_03", "nameplate_pusheen_04", "nameplate_flagAro", "nameplate_flagMlm", "nameplate_hunter", "nameplate_Polus_DVD", "nameplate_Polus_Ground", "nameplate_Polus_Lava", "nameplate_Polus_Planet", "nameplate_Polus_Snow", "nameplate_Polus_SpecimenBlue", "nameplate_Polus_SpecimenGreen", "nameplate_Polus_SpecimenPurple", "nameplate_is_yard", "nameplate_is_dig", "nameplate_is_game", "nameplate_is_ghost", "nameplate_is_green", "nameplate_is_sand", "nameplate_is_trees", "nameplate_Mira_Cafeteria", "nameplate_Mira_Glass", "nameplate_Mira_Tiles", "nameplate_Mira_Vines", "nameplate_Mira_Wood", "nameplate_hw_candy", "nameplate_hw_woods", "nameplate_hw_pumpkin" };
					//help me out with the nameplates, couldn't find them in the game assets
					for (auto player : GetAllPlayerControl()) {
						std::string name = "";
						if (State.confuserNameGeneration == 0 || (State.cyclerNameGeneration == 2 && State.cyclerUserNames.empty()))
							name = GenerateRandomString();
						else if (State.confuserNameGeneration == 1)
							name = GenerateRandomString(true);
						else if (State.confuserNameGeneration == 2) {
							if (!State.cyclerUserNames.empty())
								name = State.cyclerUserNames[randi(0, State.cyclerUserNames.size() - 1)] + "<size=0>" + std::to_string(player->fields.PlayerId) + "</size>";
						}
						else
							name = GenerateRandomString();
						queue->push(new RpcForceName(player, name));
						if (IsHost())
							queue->push(new RpcForceColor(player, randi(0, 17), true));
						else
							queue->push(new RpcForceColor(player, GetRandomColorId()));
						queue->push(new RpcForceHat(player, convert_to_string(availableHats[randi(0, availableHats.size() - 1)])));
						queue->push(new RpcForceSkin(player, convert_to_string(availableSkins[randi(0, availableSkins.size() - 1)])));
						queue->push(new RpcForceVisor(player, convert_to_string(availableVisors[randi(0, availableVisors.size() - 1)])));
						queue->push(new RpcForcePet(player, convert_to_string(availablePets[randi(0, availablePets.size() - 1)])));
						queue->push(new RpcForceNamePlate(player, convert_to_string(availableNamePlates[randi(0, availableNamePlates.size() - 1)])));
					}
				}
				if (ImGui::CollapsingHeader("Confuser Name Options")) {
					if (CustomListBoxInt("Random Name Generation", &State.confuserNameGeneration, NAMEGENERATION, 75 * State.dpiScale)) {
						State.Save();
					}
					if (State.confuserNameGeneration == 2) {
						if (State.cyclerUserNames.empty())
							ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username generation will fall back to word combo as you have no names in the cycler.");
						static std::string newName = "";
						char* newNameBuffer[255]{ const_cast<char*>(newName.c_str()) };
						if (ImGui::InputText("New Name", *newNameBuffer, IM_ARRAYSIZE(newNameBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
							newName = std::string(*newNameBuffer);
						ImGui::SameLine();
						if (ImGui::Button("Add Name")) {
							State.cyclerUserNames.push_back((std::string)*newNameBuffer);
							State.Save();
							newName = "";
						}
						if (!(IsHost() || !State.SafeMode)) {
							if (newName.length() >= (size_t)13)
								ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username is too long, gets detected by anticheat. This name will be ignored.");
							else if (!IsNameValid(newName))
								ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username contains characters blocked by anticheat. This name will be ignored.");
						}
						if (!State.cyclerUserNames.empty()) {
							int selectedNameIndex = 0;
							selectedNameIndex = std::clamp(selectedNameIndex, 0, (int)State.cyclerUserNames.size() - 1);
							std::vector<const char*> nameVector(State.cyclerUserNames.size(), nullptr);
							for (size_t i = 0; i < State.cyclerUserNames.size(); i++) {
								nameVector[i] = State.cyclerUserNames[i].c_str();
							}
							CustomListBoxInt("Select Name to Delete", &selectedNameIndex, nameVector);
							ImGui::SameLine();
							if (ImGui::Button("Delete"))
								State.cyclerUserNames.erase(State.cyclerUserNames.begin() + selectedNameIndex);
						}
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

			/*if (IsInGame() && (*Game::pLocalPlayer)->fields.inVent && ImGui::Button("Force Exit Vent"))
			{
				State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, true));
			}*/

			if (ImGui::Checkbox("Spam Report", &State.SpamReport)) {
				State.Save();
			}

			ImGui::SameLine();
			if ((IsInGame() || IsInLobby()) && ImGui::Button("Force Disconnect")) {
				Replay::Reset();
				State.aumUsers.clear();
				State.chatMessages.clear();
				State.activeImpersonation = false;
				State.FollowerCam = nullptr;
				State.EnableZoom = false;
				State.FreeCam = false;
				State.MatchEnd = std::chrono::system_clock::now();
				std::fill(State.assignedRoles.begin(), State.assignedRoles.end(), RoleType::Random); //Clear Pre assigned roles to avoid bugs.
				State.engineers_amount = 0;
				State.scientists_amount = 0;
				State.shapeshifters_amount = 0;
				State.impostors_amount = 0;
				State.crewmates_amount = 0; //We need to reset these. Or if the host doesn't turn on host tab ,these value won't update.
				State.IsRevived = false;
				State.protectMonitor.clear();

				drawing_t& instance = Esp::GetDrawing();
				synchronized(instance.m_DrawingMutex) {
					instance.m_Players = {};
				}
				InnerNetClient_DisconnectInternal((InnerNetClient*)(*Game::pAmongUsClient), DisconnectReasons__Enum::IntentionalLeaving, convert_to_string("Forcibly disconnected."), NULL);
				InnerNetClient_EnqueueDisconnect((InnerNetClient*)(*Game::pAmongUsClient), DisconnectReasons__Enum::IntentionalLeaving, convert_to_string("Forcibly disconnected."), NULL);
			}

			if (!State.SafeMode && State.InMeeting && ImGui::Button("End Meeting")) {
				State.rpcQueue.push(new RpcEndMeeting());
				State.InMeeting = false;
			}

			if ((IsHost() || !State.SafeMode) && ImGui::Checkbox("Force Name for Everyone", &State.ForceNameForEveryone)) {
				State.Save();
			}
			char* nameBufferHost[255]{ const_cast<char*>(State.hostUserName.c_str()) };
			if ((IsHost() || !State.SafeMode) && ImGui::InputText("Username", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
				State.hostUserName = std::string(*nameBufferHost);
			}

			if (IsInGame() || IsInLobby())
			{
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				ImGui::Separator();
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

				std::string hostText = std::format("Host: {}", RemoveHtmlTags(GetHostUsername()));
				ImGui::Text(const_cast<char*>(hostText.c_str()));

				if (options.GetGameMode() == GameModes__Enum::Normal)
				{
					auto allPlayers = GetAllPlayerControl();
					RoleRates roleRates = RoleRates(options, (int)allPlayers.size());
					// this should be all the major ones. if people want more they're simple enough to add.
					ImGui::Text("Visual Tasks: %s", (options.GetBool(app::BoolOptionNames__Enum::VisualTasks) ? "On" : "Off"));
					std::vector<std::string> updateModes = { "Always", "Meetings", "Never", "Other" };
					auto TaskBarUpdates = updateModes[std::clamp(options.GetInt(app::Int32OptionNames__Enum::TaskBarMode), 0, 3)];
					ImGui::Text("Task Bar Updates: %s", TaskBarUpdates);
					ImGui::Text("Confirm Ejects: %s", (options.GetBool(app::BoolOptionNames__Enum::ConfirmImpostor) ? "On" : "Off"));
					std::vector<std::string> killDistances = { "Short", "Medium", "Long", "Other"}; //proper kill distance check
					auto killDistance = killDistances[std::clamp(options.GetInt(app::Int32OptionNames__Enum::KillDistance), 0, 3)];
					ImGui::Text("Kill Distance: %s", killDistance);

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Engineers: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Engineer));
					ImGui::Text("Engineer Chance: %d%", options.GetRoleOptions().GetChancePerGame(RoleTypes__Enum::Engineer));
					ImGui::Text("Engineer Vent Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::EngineerCooldown, 1.0F));
					ImGui::Text("Engineer Duration in Vent: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::EngineerInVentMaxTime, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Scientists: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Scientist));
					ImGui::Text("Scientist Chance: %d%", options.GetRoleOptions().GetChancePerGame(RoleTypes__Enum::Scientist));
					ImGui::Text("Scientist Vitals Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ScientistCooldown, 1.0F));
					ImGui::Text("Scientist Battery Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ScientistBatteryCharge, 1.0F));

					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3)* State.dpiScale);

					ImGui::Text("Max Guardian Angels: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::GuardianAngel));
					ImGui::Text("Guardian Angel Chance: %d%", options.GetRoleOptions().GetChancePerGame(RoleTypes__Enum::GuardianAngel));
					ImGui::Text("Guardian Angel Protect Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 1.0F));
					ImGui::Text("Guardian Angel Protection Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Shapeshifters: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Shapeshifter));
					ImGui::Text("Shapeshifter Chance: %d%", options.GetRoleOptions().GetChancePerGame(RoleTypes__Enum::Shapeshifter));
					ImGui::Text("Shapeshifter Shift Cooldown: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterCooldown, 1.0F));
					ImGui::Text("Shapeshifter Shift Duration: %.2f s", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterDuration, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
				}
				else if (options.GetGameMode() == GameModes__Enum::HideNSeek) {

					int ImpostorId = options.GetInt(app::Int32OptionNames__Enum::ImpostorPlayerID);
					if (ImpostorId < 0) {
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
