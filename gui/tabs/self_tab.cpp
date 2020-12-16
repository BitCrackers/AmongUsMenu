#include "self_tab.h"

namespace SelfTab {
	void Render() {
		if (ImGui::BeginTabItem("Self")) {
			ImGui::Dummy(ImVec2(4, 4));
			ImGui::Checkbox("Max Vision", &State.MaxVision);
			ImGui::Checkbox("Wallhack", &State.Wallhack);

			if (ImGui::Checkbox("Freecam", &State.FreeCam))
			{
				if (IsInGame())
				{
					State.playerToFollow = PlayerSelection();
				}
			}
			ImGui::SameLine();
			HotKey(State.KeyBinds.Toggle_Freecam);

			ImGui::SameLine(145.0f);
			SteppedSliderFloat("  ", &State.FreeCamSpeed, 0.5f, 3.f, 0.25f, "%.2fx Speed", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

			ImGui::Checkbox("Zoom", &State.EnableZoom);
			ImGui::SameLine();
			HotKey(State.KeyBinds.Toggle_Zoom);

			ImGui::SameLine(145.0f);
			SteppedSliderFloat("   ", &State.CameraHeight, 1.0f, 20.0f, 1.0f, "%.2fx Zoom", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive);
			ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages);

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors);
			ImGui::Checkbox("See Ghosts", &State.ShowGhosts);
			ImGui::Checkbox("Unlock Vents", &State.UnlockVents);

			if (ImGui::Checkbox("No Clip", &State.NoClip)) {
				if (State.LobbyTimer == 0 || !IsInLobby())
				{
					if (!IsInGame() && !IsInLobby()) State.NoClip = false;
					else {
						if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
							if (State.NoClip)
								app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
							else
								app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
						}
					}
				}
				else State.NoClip = false;
			}
			ImGui::SameLine();
			HotKey(State.KeyBinds.Toggle_Noclip);

			if (ImGui::Checkbox("Move While in Vent", &State.MoveInVent) && IsInGame())
			{
				if (!State.MoveInVent && (State.InMeeting || (*Game::pLocalPlayer)->fields.inVent))
				{
					(*Game::pLocalPlayer)->fields.moveable = false;
				}
			}

			ImGui::EndTabItem();
		}
	}
}