#include "host_tab.h"

namespace HostTab {
	void Render() {
		if (IsHost() && IsInLobby()) {
			if (ImGui::BeginTabItem("Host")) {
				ImGui::Text("Select Impostors:");
				ImGui::BeginChild("host#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("Choose Impostors", ImVec2(200, 150));
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected) continue;

					std::string playerName = convert_from_string(playerData->fields.PlayerName);

					PlayerControl* playerCtrl = GetPlayerControlById(playerData->fields.PlayerId);

					bool impostor = std::find(State.impostors.begin(), State.impostors.end(), playerCtrl) != State.impostors.end();
					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.13f, 0.14f, 0.17f, 1.00f));
					if (ImGui::Checkbox(std::string("##" + playerName + "_CheckBox").c_str(), &impostor)) {
						if (!(std::find(State.impostors.begin(), State.impostors.end(), playerCtrl) != State.impostors.end())) {
							bool set = false;

							for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
								if (State.impostors[i] == nullptr) {
									State.impostors[i] = playerCtrl;
									set = true;
									break;
								}
							}

							if (!set) {
								if ((*Game::pGameOptionsData)->fields.NumImpostors > 2) {
									State.impostors[2] = State.impostors[1];
								}
								if ((*Game::pGameOptionsData)->fields.NumImpostors > 1) {
									State.impostors[1] = State.impostors[0];
								}
								State.impostors[0] = playerCtrl;
							}
						}
						else {
							for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
								if (State.impostors[i] == playerCtrl) {
									State.impostors[i] = nullptr;
									break;
								}
							}
						}

					}
					ImGui::PopStyleColor();
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();

					ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)),playerName.c_str());
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("host#actions", ImVec2(200, 0), true);
				if (CustomListBoxInt("Impostors", &State.impostors_amount, IMPOSTOR_AMOUNTS, 75)) {
					if (!IsInGame()) (*Game::pGameOptionsData)->fields.NumImpostors = (State.impostors_amount + 1);
				}
				if (CustomListBoxInt("Map", &State.map, MAP_NAMES, 75)) {
					if (!IsInGame()) (*Game::pGameOptionsData)->fields.MapId = State.map;
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}