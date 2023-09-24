#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include "utility.h"
#include "replay.hpp"
#include "profiler.h"
#include <sstream>
#include "esp.hpp"

void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method)
{

    if (!IsInLobby()) {
        State.LobbyTimer = -1;
    }

    if (IsInLobby() && State.LobbyTimer > 0) {
        State.LobbyTimer--;
    }

    if (!IsInGame()) {
        if (State.PlayMedbayScan) {
            State.PlayMedbayScan = false;
        }
        if (State.PlayWeaponsAnimation) {
            State.PlayWeaponsAnimation = false;
        }
    }

    State.MenuThemeColor.w = 1.f;

    if (IsInGame() || IsInLobby()) { //removed hotkeynoclip cuz even if noclip setting is saved and turned on it doesn't work
        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
            if (State.NoClip)
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
        }
        else
            app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
    }

    if (!IsInGame()) {

        State.InMeeting = false;
        State.DisableLights = false;
        State.CloseAllDoors = false;
        State.SpamReport = false;

        if (!IsInLobby()) {
            State.selectedPlayer = PlayerSelection();
            State.EnableZoom = false; //intended as we don't want stuff like the taskbar and danger meter disappearing on game start
            State.FreeCam = false; //moving after game start / on joining new game
            State.ChatFocused = false; //failsafe
        }
    }
    else {
        if (!State.rpcQueue.empty()) {
            auto rpc = State.rpcQueue.front();
            //Looks like there is a check on Task completion when u are dead.
            //The maximum amount of Tasks that can be completed per Update is at 6 (but it's 1 cuz u still get kicked).
            static auto maxProcessedTasks = 0;
            if (!State.SafeMode) {
                maxProcessedTasks = 765; //max tasks per task type = 255, # task types = 3, max tasks = 765 simple math
            }
            else {
                maxProcessedTasks = 1; //originally 6
            }
			auto processedTaskCompletes = 0;
			if (dynamic_cast<RpcCompleteTask*>(rpc))
			{
				if (processedTaskCompletes < maxProcessedTasks)
				{
					State.rpcQueue.pop();
					rpc->Process();
					processedTaskCompletes++;
				}
			}
			else
			{
				State.rpcQueue.pop();
				rpc->Process();
			}
            delete rpc;
        }

        if (State.CloseAllDoors) {
            for (auto door : State.mapDoors) {
                State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
            }
            State.CloseAllDoors = false;
        }

        if (State.MoveInVent && (((*Game::pLocalPlayer)->fields.inVent) || (*Game::pLocalPlayer)->fields.shapeshifting)) {
            (*Game::pLocalPlayer)->fields.moveable = true;
        }
    }

    if (IsInGame() || IsInLobby()) {
        if (State.AlwaysMove && !State.ChatFocused)
            (*Game::pLocalPlayer)->fields.moveable = true;
        if (State.FakeAlive && GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
            if (IsInGame())
                State.rpcQueue.push(new RpcRevive(*Game::pLocalPlayer));
            else if (IsInLobby())
                State.lobbyRpcQueue.push(new RpcRevive(*Game::pLocalPlayer));
        }
    }

    if (State.SnipeColor && (IsInGame() || IsInLobby())) {
        if ((IsColorAvailable(State.SelectedColorId) || !State.SafeMode) && GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer))->fields.ColorId != State.SelectedColorId) {
            std::queue<RPCInterface*>* queue = nullptr;
            if (IsInGame())
                queue = &State.rpcQueue;
            else if (IsInLobby())
                queue = &State.lobbyRpcQueue;

            if (State.SafeMode) {
                queue->push(new RpcSetColor(State.SelectedColorId));
                LOG_INFO("Successfully sniped your desired color!");
            }
            else {
                queue->push(new RpcForceColor(*Game::pLocalPlayer, State.SelectedColorId));
                LOG_INFO("Successfully sniped your desired color!");
            }
        }
    }
    
    if (State.SetLevel && (IsInGame() || IsInLobby())) {
        if (IsInGame() && (GetPlayerData(*Game::pLocalPlayer)->fields.PlayerLevel + 1) != State.FakeLevel)
            State.rpcQueue.push(new RpcSetLevel(*Game::pLocalPlayer, (State.FakeLevel - 1)));
        else if (IsInLobby() && (GetPlayerData(*Game::pLocalPlayer)->fields.PlayerLevel + 1) != State.FakeLevel)
            State.lobbyRpcQueue.push(new RpcSetLevel(*Game::pLocalPlayer, (State.FakeLevel - 1)));
    }

    if (IsInLobby()) {
        if (State.originalName == "-") {
            app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
            if (outfit != NULL) {
                State.originalName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
                auto petId = outfit->fields.PetId;
                auto skinId = outfit->fields.SkinId;
                auto hatId = outfit->fields.HatId;
                auto visorId = outfit->fields.VisorId;
                auto namePlateId = outfit->fields.NamePlateId;
                State.originalPet = petId;
                State.originalSkin = skinId;
                State.originalHat = hatId;
                State.originalVisor = visorId;
                State.originalNamePlate = namePlateId;
            }
        }

        if (!State.lobbyRpcQueue.empty()) {
            auto rpc = State.lobbyRpcQueue.front();
            State.lobbyRpcQueue.pop();

            rpc->Process();
            delete rpc;
        }
    }

    if (!IsInGame() && !State.rpcQueue.empty()) {
        State.rpcQueue = {};
    }
    if (!IsInLobby() && !State.lobbyRpcQueue.empty()) {
        State.lobbyRpcQueue = {};
    }

    if ((IsInGame() || IsInLobby()) && GameOptions().GetGameMode() == GameModes__Enum::Normal) {
        if (State.NoAbilityCD) {
            GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::EngineerCooldown, 0);
            GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::ScientistCooldown, 0);
            GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 0);
            GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::EngineerInVentMaxTime, 0);
            GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::ScientistBatteryCharge, 69420);
            if (GameLogicOptions().GetKillCooldown() > 0)
                (*Game::pLocalPlayer)->fields.killTimer = 0;
            else
                GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::KillCooldown, 0.0042069f);
            if (IsHost() || !State.SafeMode) {
                GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::ShapeshifterCooldown, 0);
                GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::ShapeshifterDuration, 0);
            }
        }
    }
    if ((IsInGame() || IsInLobby()) && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && State.NoAbilityCD) {
        auto localData = GetPlayerData(*Game::pLocalPlayer);
        app::RoleBehaviour* playerRole = localData->fields.Role;
        app::RoleTypes__Enum role = playerRole != nullptr ? (playerRole)->fields.Role : app::RoleTypes__Enum::Crewmate;
        (*Game::pLocalPlayer)->fields.killTimer = 0;
        if (role == RoleTypes__Enum::Engineer)
        {
            app::EngineerRole* engineerRole = (app::EngineerRole*)playerRole;
            if (engineerRole->fields.cooldownSecondsRemaining > 0.0f)
                engineerRole->fields.cooldownSecondsRemaining = 0.01f; //This will be deducted below zero on the next FixedUpdate call
            engineerRole->fields.inVentTimeRemaining = 30.0f; //Can be anything as it will always be written
        }

    }

    if (State.FakeRoleToggle && (IsInGame() || IsInLobby())) {
        auto localData = GetPlayerData(*Game::pLocalPlayer);
        std::queue<RPCInterface*>* queue = nullptr;
        if (IsInGame())
            queue = &State.rpcQueue;
        else if (IsInLobby())
            queue = &State.lobbyRpcQueue;
        if (State.FakeRole == 0 && localData->fields.RoleType != RoleTypes__Enum::Crewmate) {
            queue->push(new SetRole(RoleTypes__Enum::Crewmate));
        }
        else if (State.FakeRole == 1 && localData->fields.RoleType != RoleTypes__Enum::Scientist) {
            queue->push(new SetRole(RoleTypes__Enum::Scientist));
        }
        else if (State.FakeRole == 2 && localData->fields.RoleType != RoleTypes__Enum::Engineer) {
            queue->push(new SetRole(RoleTypes__Enum::Engineer));
        }
        else if (State.FakeRole == 3 && localData->fields.RoleType != RoleTypes__Enum::Impostor) {
            queue->push(new SetRole(RoleTypes__Enum::Impostor));
        }
        else if (State.FakeRole == 4 && localData->fields.RoleType != RoleTypes__Enum::Shapeshifter) {
            queue->push(new SetRole(RoleTypes__Enum::Shapeshifter));
        }
        else if (State.FakeRole == 5 && localData->fields.RoleType != RoleTypes__Enum::CrewmateGhost) {
            queue->push(new SetRole(RoleTypes__Enum::CrewmateGhost));
        }
        else if (State.FakeRole == 6 && localData->fields.RoleType != RoleTypes__Enum::GuardianAngel) {
            queue->push(new SetRole(RoleTypes__Enum::GuardianAngel));
        }
        else if (State.FakeRole == 7 && localData->fields.RoleType != RoleTypes__Enum::ImpostorGhost) {
            queue->push(new SetRole(RoleTypes__Enum::ImpostorGhost));
        }
        else {
            queue->push(new SetRole(RoleTypes__Enum::Crewmate));
        }
    }

    static int weaponsDelay = 0;

    if (weaponsDelay <= 0 && IsInGame()) {
        if (State.PlayWeaponsAnimation == true) {
            State.rpcQueue.push(new RpcPlayAnimation(6));
            weaponsDelay = 50; //Should be approximately 1 second
        }
    }
    else {
        weaponsDelay--;
    }

    if (State.Cycler && State.CycleName) {
        State.SetName = false;
        State.ServerSideCustomName = false;
    }

    if (State.CycleForEveryone) {
        if(State.CycleName)
            State.ForceNameForEveryone = false;
        if(State.RandomColor)
            State.ForceColorForEveryone = false;
    }

    if (!IsHost()) {
        State.DisableMeetings = false;
        State.DisableSabotages = false;
        State.NoGameEnd = false;
        State.ForceColorForEveryone = false;
    }

    if (!IsHost() && State.SafeMode) {
        State.CycleForEveryone = false;
        State.ForceNameForEveryone = false;
        State.TeleportEveryone = false;
    }

    if (State.CycleTimer <= 0.19f) {
        State.CycleTimer = 0.2f;
        State.Save();
    }

    if (State.CycleDuration <= 10) {
        State.CycleDuration = 10;
        State.Save();
    }

    static int reportDelay = 0; //If we spam too many name changes, we're banned
    if (reportDelay <= 0 && State.SpamReport && IsInGame()) {
        if (State.InMeeting)
            State.rpcQueue.push(new RpcForceMeeting(*Game::pLocalPlayer, PlayerSelection(*Game::pLocalPlayer)));
        else
            State.rpcQueue.push(new RpcReportPlayer(PlayerSelection(*Game::pLocalPlayer)));
        reportDelay = 50; //Should be approximately 1 second
    }
    else {
        reportDelay--;
    }
    
    static int nameChangeCycleDelay = 0; //If we spam too many name changes, we're banned

    if (nameChangeCycleDelay <= 0 && State.SetName && !State.activeImpersonation && !State.ServerSideCustomName) {
        if ((((IsInGame() || IsInLobby()) && (convert_from_string(GameData_PlayerOutfit_get_PlayerName(GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer)), nullptr)) != State.userName)) || ((!IsInGame() && !IsInLobby()) && GetPlayerName() != State.userName)) && !State.userName.empty()) {
            SetPlayerName(State.userName);
            LOG_INFO("Name mismatch, setting name to \"" + State.userName + "\"");
            if (IsInGame())
                State.rpcQueue.push(new RpcSetName(State.userName));
            else if (IsInLobby())
                State.lobbyRpcQueue.push(new RpcSetName(State.userName));
            nameChangeCycleDelay = 10; //Should be approximately 0.2 second
        }
    }
    else {
        nameChangeCycleDelay--;
    }


    static int nameCtr = 1;

    static float cycleNameDelay = 0; //If we spam too many name changes, we're banned
    static float colorChangeCycleDelay = 0; //If we spam too many color changes, we're banned?

    static float hatChangeCycler = 0; //controls the hat string
    static float hatChangeCycleDelay = 0; //controls the actual hat cycler

    static float skinChangeCycler = 0; //controls the skin string
    static float skinChangeCycleDelay = 0; //controls the actual skin cycler

    static float visorChangeCycler = 0; //controls the visor string
    static float visorChangeCycleDelay = 0; //controls the actual visor cycler

    static float petChangeCycler = 0; //controls the pet string
    static float petChangeCycleDelay = 0; //controls the actual pet cycler

    static float namePlateChangeCycler = 0; //controls the nameplate string
    static float namePlateChangeCycleDelay = 0; //controls the actual nameplate cycler
    
    if (State.Cycler && (!State.InMeeting || State.CycleInMeeting)) {
        if (cycleNameDelay <= 0 && State.CycleName && !State.activeImpersonation && !State.CycleForEveryone) {
            if (!State.userName1.empty() && !State.userName2.empty()) {
                if (nameCtr == 2) {
                    if (IsInGame())
                        State.rpcQueue.push(new RpcSetName(State.userName2));
                    else if (IsInLobby())
                        State.lobbyRpcQueue.push(new RpcSetName(State.userName2));
                    cycleNameDelay = State.CycleDuration;
                    nameCtr = 1;
                }
                else if (nameCtr == 1) {
                    if (IsInGame())
                        State.rpcQueue.push(new RpcSetName(State.userName1));
                    else if (IsInLobby())
                        State.lobbyRpcQueue.push(new RpcSetName(State.userName1));
                    cycleNameDelay = State.CycleDuration;
                    nameCtr = 2;
                }
            }
        }
        else {
            cycleNameDelay--;
        }

        if (colorChangeCycleDelay <= 0 && State.RandomColor && !State.activeImpersonation && !State.CycleForEveryone) {
            if (IsInGame()) {
                State.RandomColorId = GetRandomColorId();
                State.rpcQueue.push(new RpcSetColor(State.RandomColorId));
            }
            else if (IsInLobby()) {
                State.RandomColorId = GetRandomColorId();
                State.lobbyRpcQueue.push(new RpcSetColor(State.RandomColorId));
            }
            colorChangeCycleDelay = State.CycleDuration; //idk how long this is
        }
        else if (colorChangeCycleDelay > 0) {
            colorChangeCycleDelay--;
        }
        
        if (hatChangeCycler <= 0 && State.RandomHat && !State.activeImpersonation) {
            std::vector availableHats = { "hat_NoHat", "hat_bushhat", "hat_captain", "hat_doubletophat", "hat_flowerpot", "hat_military", "hat_MilitaryWinter", "hat_GovtDesert", "hat_police", "hat_Rupert", "hat_partyhat", "hat_tophat", "hat_towelwizard", "hat_russian", "hat_viking", "hat_wallcap", "hat_pk06_Snowman", "hat_pk06_Reindeer", "hat_pk06_Lights", "hat_pk06_Santa", "hat_pk06_tree", "hat_pk06_Present", "hat_pk06_Candycanes", "hat_pk06_ElfHat", "hats_newyears2018", "hat_whitetophat", "hat_pk02_Crown", "hat_pk02_Eyebrows", "hat_pk02_HaloHat", "hat_pk02_PipCap", "hat_pk02_ScubaHat", "hat_pk02_StickminHat", "hat_pk02_StrawHat", "hat_pk02_ThirdEyeHat", "hat_pk02_ToiletPaperHat", "hat_pk02_Toppat", "hat_pk03_Fedora", "hat_pk03_StrapHat", "hat_pk04_Banana", "hat_pk04_Bear", "hat_pk05_Cheese", "hat_pk05_Cherry", "hat_pk05_Egg", "hat_pk05_Fedora", "hat_pk05_Flamingo", "hat_pk05_FlowerPin", "hat_pk05_Helmet", "hat_pk05_Plant", "hat_pkHW01_PlagueHat", "hat_pkHW01_CatEyes", "hat_pkHW01_Horns", "hat_pkHW01_BatWings", "hat_pkHW01_Mohawk", "hat_pkHW01_Pumpkin", "hat_pkHW01_ScaryBag", "hat_pkHW01_Witch", "hat_pkHW01_Wolf", "hat_pkHW01_Pirate", "hat_pkHW01_Machete", "hat_pk04_Archae", "hat_pk04_Balloon", "hat_pk04_BirdNest", "hat_pk04_Chef", "hat_pk04_CCC", "hat_pk04_Fez", "hat_pk04_GeneralHat", "hat_pk04_Pompadour", "hat_pk04_HunterCap", "hat_pk04_JungleHat", "hat_pk04_MiniCrewmate", "hat_pk04_Vagabond", "hat_pk04_Snowman", "hat_pk05_davehat", "hat_pk05_Ellie", "hat_pk05_Svenhat", "hat_pk05_Burthat", "hat_pk05_Ellryhat", "hat_pk05_Wizardhat", "hat_pk05_cheesetoppat", "hat_pk05_Macbethhat", "hat_pk05_HenryToppat", "hat_pk05_EllieToppat", "hat_pk05_GeoffreyToppat", "hat_Chocolate", "hat_Heart", "hat_Ponytail", "hat_Rubberglove", "hat_Unicorn", "hat_Zipper", "hat_CuppaJoe", "hat_HardtopHat", "hat_Prototype", "hat_Records", "hat_ThomasC", "hat_ToppatHair", "hat_WilfordIV", "hat_Winston", "hat_AbominalHat", "hat_EarmuffGreen", "hat_EarmuffsPink", "hat_EarmuffsYellow", "hat_EarnmuffBlue", "hat_pk04_MinerCap", "hat_MinerBlack", "hat_MinerYellow", "hat_RockIce", "hat_RockLava", "hat_SnowbeanieGreen", "hat_SnowbeanieOrange", "hat_SnowBeaniePurple", "hat_SnowbeanieRed", "hat_WinterHelmet", "hat_pk04_WinterHat", "hat_WinterGreen", "hat_WinterRed", "hat_WinterYellow", "hat_Voleyball", "hat_Basketball", "hat_Bowlingball", "hat_Deitied", "hat_Dodgeball", "hat_DrillMetal", "hat_DrillStone", "hat_DrillWood", "hat_Janitor", "hat_Pot", "hat_Soccer", "hat_Visor", "hat_mira_bush", "hat_mira_case", "hat_mira_cloud", "hat_mira_flower", "hat_mira_flower_red", "hat_mira_gem", "hat_pk03_Headphones", "hat_GovtHeadset", "hat_mira_headset_blue", "hat_mira_headset_pink", "hat_mira_headset_yellow", "hat_mira_leaf", "hat_mira_milk", "hat_pk04_Slippery", "hat_mira_sign_blue", "hat_pk03_Security1", "hat_pk04_Antenna", "hat_Antenna_Black", "hat_astronaut", "hat_Astronaut-Blue", "hat_Astronaut-Cyan", "hat_Astronaut-Orange", "hat_pk04_Bandana", "hat_Bandana_Blue", "hat_Bandana_Green", "hat_Bandana_Pink", "hat_Bandana_Red", "hat_Bandana_White", "hat_Bandana_Yellow", "hat_pk01_BaseballCap", "hat_baseball_Black", "hat_baseball_Green", "hat_baseball_Lightblue", "hat_baseball_LightGreen", "hat_baseball_Lilac", "hat_baseball_Orange", "hat_baseball_Pink", "hat_baseball_Purple", "hat_baseball_Red", "hat_baseball_White", "hat_baseball_Yellow", "hat_pk04_Beanie", "hat_Beanie_Black", "hat_Beanie_Blue", "hat_Beanie_Green", "hat_Beanie_Lightblue", "hat_Beanie_LightGreen", "hat_Beanie_LightPurple", "hat_Beanie_Pink", "hat_Beanie_Purple", "hat_Beanie_White", "hat_Beanie_Yellow", "hat_stethescope", "hat_Doc_black", "hat_Doc_Orange", "hat_Doc_Purple", "hat_Doc_Red", "hat_Doc_White", "hat_pk04_DoRag", "hat_Dorag_Black", "hat_Dorag_Desert", "hat_Dorag_Jungle", "hat_Dorag_Purple", "hat_Dorag_Sky", "hat_Dorag_Snow", "hat_Dorag_Yellow", "hat_pk03_Goggles", "hat_goggles", "hat_Goggles_Black", "hat_Goggles_Chrome", "hat_hardhat", "hat_Hardhat_black", "hat_Hardhat_Blue", "hat_Hardhat_Green", "hat_Hardhat_Orange", "hat_Hardhat_Pink", "hat_Hardhat_Purple", "hat_Hardhat_Red", "hat_Hardhat_White", "hat_brainslug", "hat_headslug_Purple", "hat_headslug_Red", "hat_headslug_Yellow", "hat_headslug_White", "hat_pk02_HeroCap", "hat_Herohood_Black", "hat_Herohood_Blue", "hat_Herohood_Pink", "hat_Herohood_Purple", "hat_Herohood_Red", "hat_Herohood_White", "hat_Herohood_Yellow", "hat_paperhat", "hat_Paperhat_Black", "hat_Paperhat_Blue", "hat_Paperhat_Cyan", "hat_Paperhat_Lightblue", "hat_Paperhat_Pink", "hat_Paperhat_Yellow", "hat_pk02_PlungerHat", "hat_Plunger_Blue", "hat_Plunger_Yellow", "hat_pk04_RamHorns", "hat_Ramhorn_Black", "hat_Ramhorn_Red", "hat_Ramhorn_White", "hat_pk02_TenGallonHat", "hat_TenGallon_Black", "hat_TenGallon_White", "hat_pk03_Traffic", "hat_Traffic_Blue", "hat_Traffic_Red", "hat_Traffic_Yellow", "hat_traffic_purple", "hat_devilhorns_yellow", "hat_arrowhead", "hat_axe", "hat_papermask", "hat_bat_crewcolor", "hat_bat_green", "hat_bat_ice", "hat_bone", "hat_candycorn", "hat_cat_grey", "hat_cat_orange", "hat_cat_pink", "hat_cat_snow", "hat_clown_purple", "hat_devilhorns_crewcolor", "hat_devilhorns_green", "hat_devilhorns_murky", "hat_devilhorns_white", "hat_devilhorns_black", "hat_fairywings", "hat_fishhed", "hat_frankenbolts", "hat_frankenbride", "hat_glowstick", "hat_mohawk_bubblegum", "hat_mohawk_bumblebee", "hat_mohawk_purple_green", "hat_mohawk_rainbow", "hat_mummy", "hat_tombstone", "hat_witch_green", "hat_witch_murky", "hat_witch_pink", "hat_witch_white", "hat_wolf_murky", "hat_wolf_grey", "hat_vi", "hat_caitlin", "hat_clagger", "hat_comper", "hat_enforcer", "hat_heim", "hat_jayce", "hat_jinx" };
            assert(availableHats.size() > 0);
            State.cyclerHat = convert_to_string(availableHats[randi(0, availableHats.size() - 1)]);
        }
        else if (hatChangeCycler > 0) {
            hatChangeCycler--;
        }

        if (hatChangeCycleDelay <= 0 && State.RandomHat && !State.activeImpersonation) {
            if (IsInGame()) {
                State.rpcQueue.push(new RpcSetHat(State.cyclerHat));
                hatChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
            else if (IsInLobby()) {
                State.lobbyRpcQueue.push(new RpcSetHat(State.cyclerHat));
                hatChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
        }
        else if (hatChangeCycleDelay > 0) {
            hatChangeCycleDelay--;
        }

        if (skinChangeCycler <= 0 && State.RandomSkin && !State.activeImpersonation) {
            std::vector availableSkins = { "skin_None", "skin_Capt", "skin_Police", "skin_Wall", "skin_Security", "skin_Tarmac", "skin_Archae", "skin_CCC", "skin_rhm", "skin_Bling", "skin_General", "skin_Mech", "skin_MechanicRed", "skin_MilitaryDesert", "skin_Military", "skin_prisoner", "skin_PrisonerBlue", "skin_PrisonerTanskin", "skin_SuitB", "skin_SuitW", "skin_Skin_SuitRedskin", "skin_ToppatSuitFem", "skin_ToppatVest", "skin_SweaterYellowskin", "skin_Winter", "skin_JacketGreenskin", "skin_JacketPurpleskin", "skin_JacketYellowskin", "skin_Abominalskin", "skin_MilitarySnowskin", "skin_Miner", "skin_MinerBlackskin", "skin_RockIceskin", "skin_RockLavaskin", "skin_SweaterBlueskin", "skin_SweaterPinkskin", "skin_Sweaterskin", "skin_SportsRedskin", "skin_D2Cskin", "skin_Janitorskin", "skin_SportsBlueskin", "skin_Bushskin", "skin_BusinessFemskin", "skin_BusinessFem-Aquaskin", "skin_BusinessFem-Tanskin", "skin_Hazmat", "skin_Hazmat-Blackskin", "skin_Hazmat-Blueskin", "skin_Hazmat-Greenskin", "skin_Hazmat-Pinkskin", "skin_Hazmat-Redskin", "skin_Hazmat-Whiteskin", "skin_Astro", "skin_Astronaut-Blueskin", "skin_Astronaut-Cyanskin", "skin_Astronaut-Orangeskin", "skin_Science", "skin_Scientist-Blueskin", "skin_Scientist-Darkskin", "skin_clown", "skin_fairy", "skin_fishmonger", "skin_mummy", "skin_pumpkin", "skin_vampire", "skin_witch", "skin_caitlin", "skin_enforcer", "skin_heim", "skin_jayce", "skin_jinx", "skin_vi" };
            assert(availableSkins.size() > 0);
            State.cyclerSkin = convert_to_string(availableSkins[randi(0, availableSkins.size() - 1)]);
        }
        else if (skinChangeCycler > 0) {
            skinChangeCycler--;
        }

        if (skinChangeCycleDelay <= 0 && State.RandomSkin && !State.activeImpersonation) {
            if (IsInGame()) {
                State.rpcQueue.push(new RpcSetSkin(State.cyclerSkin));
                skinChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
            else if (IsInLobby()) {
                State.lobbyRpcQueue.push(new RpcSetSkin(State.cyclerSkin));
                skinChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
        }
        else if (skinChangeCycleDelay > 0) {
            skinChangeCycleDelay--;
        }

        if (visorChangeCycler <= 0 && State.RandomVisor && !State.activeImpersonation) {
            std::vector availableVisors = { "visor_EmptyVisor", "visor_pk01_FredVisor", "hat_geoff", "visor_pk01_MonoclesVisor", "visor_pk01_PaperMaskVisor", "visor_pk01_PlagueVisor", "visor_pk01_RHMVisor", "visor_pk01_Security1Visor", "visor_pk01_AngeryVisor", "visor_BillyG", "visor_Galeforce", "visor_Krieghaus", "visor_Reginald", "visor_Scar", "visor_WinstonStache", "visor_SkiGogglesWhite", "visor_Lava", "visor_polus_ice", "visor_SkiGoggleBlack", "visor_SKiGogglesOrange", "visor_shopglasses", "visor_D2CGoggles", "visor_is_beard", "visor_JanitorStache", "visor_Mouth", "visor_mira_card_blue", "visor_mira_card_red", "visor_mira_glasses", "visor_pk01_HazmatVisor", "visor_mira_mask_black", "visor_mira_mask_blue", "visor_mira_mask_green", "visor_mira_mask_purple", "visor_mira_mask_red", "visor_mira_mask_white", "visor_pk01_DumStickerVisor", "visor_Stickynote_Cyan", "visor_Stickynote_Green", "visor_Stickynote_Orange", "visor_Stickynote_Pink", "visor_Stickynote_Purple", "visor_Blush", "visor_Bomba", "visor_Carrot", "visor_Crack", "visor_Dirty", "visor_Dotdot", "visor_EyepatchL", "visor_EyepatchR", "visor_LolliBlue", "visor_LolliBrown", "visor_LolliOrange", "visor_LolliRed", "visor_PiercingL", "visor_PiercingR", "visor_SciGoggles", "visor_SmallGlassesBlue", "visor_SmallGlasses", "visor_SmallGlassesRed", "visor_Straw", "visor_eyeball", "visor_clownnose", "visor_masque_blue", "visor_masque_green", "visor_masque_red", "visor_masque_white", "visor_mummy", "visor_heim", "visor_jinx" };
            assert(availableVisors.size() > 0);
            State.cyclerVisor = convert_to_string(availableVisors[randi(0, availableVisors.size() - 1)]);
        }
        else if (visorChangeCycler > 0) {
            visorChangeCycler--;
        }

        if (visorChangeCycleDelay <= 0 && State.RandomVisor && !State.activeImpersonation) {
            if (IsInGame()) {
                State.rpcQueue.push(new RpcSetVisor(State.cyclerVisor));
                visorChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
            else if (IsInLobby()) {
                State.lobbyRpcQueue.push(new RpcSetVisor(State.cyclerVisor));
                visorChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
        }
        else if (visorChangeCycleDelay > 0) {
            visorChangeCycleDelay--;
        }

        if (petChangeCycler <= 0 && State.RandomPet && !State.activeImpersonation) {
            std::vector availablePets = { "pet_EmptyPet", "pet_Alien", "pet_Crewmate", "pet_Doggy", "pet_Stickmin", "pet_Hamster", "pet_Robot", "pet_UFO", "pet_Ellie", "pet_Squig", "pet_Bedcrab", "pet_test", "pet_Lava", "pet_Snow", "pet_Charles", "pet_Charles_Red", "pet_Cube", "pet_Bush", "pet_frankendog", "pet_poro" };
            assert(availablePets.size() > 0);
            State.cyclerPet = convert_to_string(availablePets[randi(0, availablePets.size() - 1)]);
        }
        else if (petChangeCycler > 0) {
            petChangeCycler--;
        }

        if (petChangeCycleDelay <= 0 && State.RandomPet && !State.activeImpersonation) {
            if (IsInGame()) {
                State.rpcQueue.push(new RpcSetPet(State.cyclerPet));
                petChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
            else if (IsInLobby()) {
                State.lobbyRpcQueue.push(new RpcSetPet(State.cyclerPet));
                petChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
        }
        else if (petChangeCycleDelay > 0) {
            petChangeCycleDelay--;
        }

        if (namePlateChangeCycler <= 0 && State.RandomNamePlate && !State.activeImpersonation) {
            std::vector availableNamePlates = { "nameplate_NoPlate", "nameplate_airship_Toppat", "nameplate_airship_CCC", "nameplate_airship_Diamond", "nameplate_airship_Emerald", "nameplate_airship_Gems", "nameplate_airship_government", "nameplate_Airship_Hull", "nameplate_airship_Ruby", "nameplate_airship_Sky", "nameplate_Polus-Skyline", "nameplate_Polus-Snowmates", "nameplate_Polus_Colors", "nameplate_Polus_DVD", "nameplate_Polus_Ground", "nameplate_Polus_Lava", "nameplate_Polus_Planet", "nameplate_Polus_Snow", "nameplate_Polus_SpecimenBlue", "nameplate_Polus_SpecimenGreen", "nameplate_Polus_SpecimenPurple", "nameplate_is_yard", "nameplate_is_dig", "nameplate_is_game", "nameplate_is_ghost", "nameplate_is_green", "nameplate_is_sand", "nameplate_is_trees", "nameplate_Mira_Cafeteria", "nameplate_Mira_Glass", "nameplate_Mira_Tiles", "nameplate_Mira_Vines", "nameplate_Mira_Wood", "nameplate_hw_candy", "nameplate_hw_woods", "nameplate_hw_pumpkin" };
            assert(availableNamePlates.size() > 0);
            State.cyclerNamePlate = convert_to_string(availableNamePlates[randi(0, availableNamePlates.size() - 1)]);
        }
        else if (namePlateChangeCycler > 0) {
            namePlateChangeCycler--;
        }

        if (namePlateChangeCycleDelay <= 0 && State.RandomNamePlate && !State.activeImpersonation) {
            if (IsInGame()) {
                State.rpcQueue.push(new RpcSetNamePlate(State.cyclerNamePlate));
                namePlateChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
            else if (IsInLobby()) {
                State.lobbyRpcQueue.push(new RpcSetNamePlate(State.cyclerNamePlate));
                namePlateChangeCycleDelay = State.CycleDuration; //idk how long this is
            }
        }
        else if (namePlateChangeCycleDelay > 0) {
            namePlateChangeCycleDelay--;
        }
    }
    else {
        cycleNameDelay = 0; //If we spam too many name changes, we're banned
        colorChangeCycleDelay = 0; //If we spam too many color changes, we're banned?

        hatChangeCycler = 0; //controls the hat string
        hatChangeCycleDelay = 0; //controls the actual hat cycler

        skinChangeCycler = 0; //controls the skin string
        skinChangeCycleDelay = 0; //controls the actual skin cycler

        visorChangeCycler = 0; //controls the visor string
        visorChangeCycleDelay = 0; //controls the actual visor cycler

        petChangeCycler = 0; //controls the pet string
        petChangeCycleDelay = 0; //controls the actual pet cycler

        namePlateChangeCycler = 0; //controls the nameplate string
        namePlateChangeCycleDelay = 0; //controls the actual nameplate cycler
    }

    State.RgbNameColor += 0.025f;
    constexpr auto d_pi = 2.f * 3.14159265358979323846f;
    while (State.RgbNameColor > d_pi) State.RgbNameColor -= d_pi;
    const auto calculate = [](float value) {return std::sin(value) * .5f + .5f; };
    auto color_r = calculate(State.RgbNameColor + 0.f);
    auto color_g = calculate(State.RgbNameColor + 4.f);
    auto color_b = calculate(State.RgbNameColor + 2.f);
    State.rgbCode = std::format("<#{:02x}{:02x}{:02x}>", int(color_r * 255), int(color_g * 255), int(color_b * 255));

    if (State.RgbMenuTheme) {
        State.RgbColor.x = color_r;
        State.RgbColor.y = color_g;
        State.RgbColor.z = color_b;
    }

    static int attachDelay = 0; //If we spam too many name changes, we're banned
    auto playerToAttach = State.playerToAttach.validate();

    if (attachDelay <= 0 && State.ActiveAttach && State.playerToAttach.has_value()) {
        if (IsInGame())
            State.rpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(playerToAttach.get_PlayerControl())));
        else if (IsInLobby())
            State.lobbyRpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(playerToAttach.get_PlayerControl())));
        attachDelay = 25; //Should be approximately 0.5 second
    }
    else {
        attachDelay--;
    }

    // Shift + Right-click Teleport
    if ((IsInGame() && !State.InMeeting) && State.ShiftRightClickTP && ImGui::IsKeyDown(VK_SHIFT) && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !(State.TeleportEveryone && (ImGui::IsKeyPressed(VK_CONTROL) || ImGui::IsKeyDown(VK_CONTROL)))) {
        ImVec2 mouse = ImGui::GetMousePos();
        Vector2 target = {
            (mouse.x - DirectX::GetWindowSize().x / 2) + DirectX::GetWindowSize().x / 2,
            ((mouse.y - DirectX::GetWindowSize().y / 2) - DirectX::GetWindowSize().y / 2) * -1.0f
        };
        State.rpcQueue.push(new RpcSnapTo(ScreenToWorld(target)));
    }
	else if (IsInLobby() && State.ShiftRightClickTP && ImGui::IsKeyDown(VK_SHIFT) && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !(State.TeleportEveryone && (ImGui::IsKeyPressed(VK_CONTROL) || ImGui::IsKeyDown(VK_CONTROL)))) {
		ImVec2 mouse = ImGui::GetMousePos();
        Vector2 target = {
            (mouse.x - DirectX::GetWindowSize().x / 2) + DirectX::GetWindowSize().x / 2,
            ((mouse.y - DirectX::GetWindowSize().y / 2) - DirectX::GetWindowSize().y / 2) * -1.0f
        };
        State.lobbyRpcQueue.push(new RpcSnapTo(ScreenToWorld(target)));
    }
    InnerNetClient_Update(__this, method);
}

void dAmongUsClient_OnGameJoined(AmongUsClient* __this, String* gameIdString, MethodInfo* method) {
    Log.Debug("Joined lobby " + convert_from_string(gameIdString));
    if (State.confuser && State.confuseOnJoin)
        ControlAppearance(true);
    AmongUsClient_OnGameJoined(__this, gameIdString, method);
}

void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method) {
    if (data->fields.Character) { // Don't use Object_1_IsNotNull().
        auto playerInfo = GetPlayerData(data->fields.Character);

        if (reason == DisconnectReasons__Enum::Banned)
            Log.Debug(ToString(data->fields.Character) + " has been banned by host (" + GetHostUsername() + ").");
        else if (reason == DisconnectReasons__Enum::Kicked)
            Log.Debug(ToString(data->fields.Character) + " has been kicked by host (" + GetHostUsername() + ").");
        else if (reason == DisconnectReasons__Enum::Hacking)
            Log.Debug(ToString(data->fields.Character) + " has been banned for hacking.");
        else if (reason == DisconnectReasons__Enum::Error)
            Log.Debug(ToString(data->fields.Character) + " has been disconnected due to error.");
        else
            Log.Debug(ToString(data->fields.Character) + " has left the game.");

        auto it = std::find(State.aumUsers.begin(), State.aumUsers.end(), data->fields.Character->fields.PlayerId);
        if (it != State.aumUsers.end())
            State.aumUsers.erase(it);

        if (auto evtPlayer = GetEventPlayer(playerInfo); evtPlayer) {
            synchronized(Replay::replayEventMutex) {
        	    State.liveReplayEvents.emplace_back(std::make_unique<DisconnectEvent>(evtPlayer.value()));
            }
        }
    }
    else {
        //Found this happens on game ending occasionally
        //Log.Info(std::format("Client {} has left the game.", data->fields.Id));
    }

    AmongUsClient_OnPlayerLeft(__this, data, reason, method);
}

bool bogusTransformSnap(PlayerSelection& _player, Vector2 newPosition)
{
    const auto& player = _player.validate();
    if (!player.has_value())
        Log.Debug("bogusTransformSnap received invalid player!");
    if (!player.has_value()) return false; //Error getting playercontroller
    if (player.is_LocalPlayer()) return false; //We are not going to log ourselves
    if (player.get_PlayerControl()->fields.inVent) return false; //Vent buttons are warps
    if (GameObject_get_layer(app::Component_get_gameObject((Component_1*)player.get_PlayerControl(), NULL), NULL) == LayerMask_NameToLayer(convert_to_string("Ghost"), NULL))
        return false; //For some reason the playercontroller is not marked dead at this point, so we check what layer the player is on
    auto currentPosition = PlayerControl_GetTruePosition(player.get_PlayerControl(), NULL);
    auto distanceToTarget = (int32_t)Vector2_Distance(currentPosition, newPosition, NULL); //rounding off as the smallest kill distance is zero
    auto killDistance = std::clamp(GameOptions().GetInt(app::Int32OptionNames__Enum::KillDistance), 0, 2);
    auto initialSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), true);
    auto meetingSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), false);
    if (Equals(initialSpawnLocation, newPosition)) return false;
    if (Equals(meetingSpawnLocation, newPosition)) return false;  //You are warped to your spawn at meetings and start of games
    if (IsAirshipSpawnLocation(newPosition)) return false;
    if (PlayerIsImpostor(player.get_PlayerData()) && distanceToTarget <= killDistance) 
        return false;
    std::ostringstream ss;

    ss << "From " << +currentPosition.x << "," << +currentPosition.y << " to " << +newPosition.x << "," << +newPosition.y << std::endl;
    ss << "Range to target " << +distanceToTarget << ", KillDistance: " << +killDistance << std::endl;
    ss << "Initial Spawn Location " << +initialSpawnLocation.x << "," << +initialSpawnLocation.y << std::endl;
    ss << "Meeting Spawn Location " << +meetingSpawnLocation.x << "," << +meetingSpawnLocation.y << std::endl;
    ss << "-------";
    Log.Debug(ss.str());
    return true; //We have ruled out all possible scenarios.  Off with his head!
}

void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method) {
    //Leave this out until we fix it.
    
    if (!IsInGame()) {
        CustomNetworkTransform_SnapTo(__this, position, minSid, method);
        return;
    }

    for (auto p : GetAllPlayerControl()) {
        if (p->fields.NetTransform == __this) {
            PlayerSelection pSel = PlayerSelection(p);
            if (bogusTransformSnap(pSel, position))
            {
                synchronized(Replay::replayEventMutex) {
                    State.liveReplayEvents.emplace_back(std::make_unique<CheatDetectedEvent>(GetEventPlayer(GetPlayerData(p)).value(), CHEAT_ACTIONS::CHEAT_TELEPORT));
                }
            }
            break;
        }
    }
    

    CustomNetworkTransform_SnapTo(__this, position, minSid, method);
}

static void onGameEnd() {
    LOG_DEBUG("Reset All");
    Replay::Reset();
    State.aumUsers.clear();
    State.activeImpersonation = false;
    State.FollowerCam = nullptr;
    State.EnableZoom = false;
    State.FreeCam = false;
    State.MatchEnd = std::chrono::system_clock::now();

    drawing_t& instance = Esp::GetDrawing();
    synchronized(instance.m_DrawingMutex) {
        instance.m_Players = {};
    }
}

void dAmongUsClient_OnGameEnd(AmongUsClient* __this, Object* endGameResult, MethodInfo* method) {
    onGameEnd();
    AmongUsClient_OnGameEnd(__this, endGameResult, method);
}

void dInnerNetClient_DisconnectInternal(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    // IsInGame() || IsInLobby()
    if (__this->fields.GameState == InnerNetClient_GameStates__Enum::Started
        || __this->fields.GameState == InnerNetClient_GameStates__Enum::Joined
        || __this->fields.NetworkMode == NetworkModes__Enum::FreePlay) {
        onGameEnd();
    }
    InnerNetClient_DisconnectInternal(__this, reason, stringReason, method);
}

void dInnerNetClient_EnqueueDisconnect(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    State.FollowerCam = nullptr;
    onGameEnd(); //removed antiban cuz it glitches the game
    return InnerNetClient_EnqueueDisconnect(__this, reason, stringReason, method);
}

void dGameManager_RpcEndGame(GameManager* __this, GameOverReason__Enum endReason, bool showAd, MethodInfo* method) {
    if (IsHost() && State.NoGameEnd)
        return;
    return GameManager_RpcEndGame(__this, endReason, showAd, method);
}

void dKillOverlay_ShowKillAnimation_1(KillOverlay* __this, GameData_PlayerInfo* killer, GameData_PlayerInfo* victim, MethodInfo* method) {
    if (State.DisableKillAnimation)
        return;
    return KillOverlay_ShowKillAnimation_1(__this, killer, victim, method);
}