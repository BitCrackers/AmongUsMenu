#include "pch-il2cpp.h"
#include "radar.hpp"
#include "DirectX.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"

namespace Radar {
	std::mutex radarEventMutex;

	ImU32 GetRadarPlayerColor(GameData_PlayerInfo* playerData) {
		return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)));
	}

	ImU32 GetRadarPlayerColorStatus(GameData_PlayerInfo* playerData) {
		if (playerData->fields.IsDead)
			return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->HalfWhite));
		else if (playerData->fields.IsImpostor && State.RevealImpostors)
			return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->ImpostorRed));
		else
			return ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 0));
	}

	void SquareConstraint(ImGuiSizeCallbackData* data)
	{
		data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.y);
	}

	void OnClick() {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
			ImVec2 mouse = ImGui::GetMousePos();
			ImVec2 winpos = ImGui::GetWindowPos();
			ImVec2 winsize = ImGui::GetWindowSize();
			int MapType = State.mapType;

			if (mouse.x < winpos.x
				|| mouse.x > winpos.x + winsize.x
				|| mouse.y < winpos.y
				|| mouse.y > winpos.y + winsize.y)
				return;

			float xOffset = maps[MapType].x_offset;
			float yOffset = maps[MapType].y_offset;

			if (MapType == 0 && State.FlipSkeld) {
				xOffset -= 50;
			}

			Vector2 target = {
				(mouse.x - winpos.x - xOffset) / maps[MapType].scale,
				((mouse.y - winpos.y - yOffset) * -1.F) / maps[MapType].scale
			};

			State.rpcQueue.push(new RpcSnapTo(target));
		}
	}

	void Init() {
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);
		ImGui::SetNextWindowBgAlpha(0.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			Radar::Init();

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F + 10, (float)maps[MapType].mapImage.imageHeight * 0.5F + 10), ImGuiCond_None);

		if(State.LockRadar)
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		else
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 winpos = ImGui::GetWindowPos();
		ImVec2 winsize = ImGui::GetWindowSize();

		if (State.FlipSkeld && MapType == 0) {
			ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView, ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F), ImVec2(1.0f, 0.0f), ImVec2(0.0f, 1.0f), State.SelectedColor);
		}
		else {
			ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView, ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), State.SelectedColor);
		}

		for (auto player : GetAllPlayerControl()) {
			auto playerData = GetPlayerData(player);

			if (!playerData || (!State.ShowRadar_Ghosts && playerData->fields.IsDead))
				continue;

			Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

			float xOffset = maps[MapType].x_offset;
			float yOffset = maps[MapType].y_offset;

			if (MapType == 0 && State.FlipSkeld) {
				xOffset -= 50;
			}

			float radX = xOffset + (playerPos.x * maps[MapType].scale) + winpos.x;
			float radY = yOffset - (playerPos.y * maps[MapType].scale) + winpos.y;

			drawList->AddCircleFilled(ImVec2(radX, radY), 4.5F, GetRadarPlayerColor(playerData));
			drawList->AddCircle(ImVec2(radX, radY), 4.5F + 0.5F, GetRadarPlayerColorStatus(playerData), 0, 2.0F);
		}

		if (State.ShowRadar_DeadBodies) {
			for (auto deadBody : GetAllDeadBodies()) {
				auto playerData = GetPlayerDataById(deadBody->fields.ParentId);

				Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

				float radX = maps[MapType].x_offset + (bodyPos.x * maps[MapType].scale) + winpos.x;
				float radY = maps[MapType].y_offset - (bodyPos.y * maps[MapType].scale) + winpos.y;

				drawList->AddText(ImGui::GetFont(), 16, ImVec2(radX - 5.F, radY - 6.75F), GetRadarPlayerColor(playerData), "X");
			}
		}

		// event drawing
		if (State.selectedPlayer.has_value()) {
			std::lock_guard<std::mutex> lock(Radar::radarEventMutex);
			for (int i = 1; i != EVENT_TYPES_SIZE; i++) {
				if (i == EVENT_VOTE) continue;
				for (unsigned int j = 0; j < State.events[State.selectedPlayer.get_PlayerId()][i].size(); j++) {
					const auto e = State.events[State.selectedPlayer.get_PlayerId()][i][j];
					float radX = maps[MapType].x_offset + (e->getPosition().x * maps[MapType].scale) + winpos.x;
					float radY = maps[MapType].y_offset - (e->getPosition().y * maps[MapType].scale) + winpos.y;
					if (i != EVENT_WALK) drawList->AddCircleFilled(ImVec2(radX, radY), 4.5F, e->getColor());
					else {
						if (j + 1 < State.events[State.selectedPlayer.get_PlayerId()][i].size()) {
							const auto e2 = State.events[State.selectedPlayer.get_PlayerId()][i][j + 1];
							float radX2 = maps[MapType].x_offset + (e2->getPosition().x * maps[MapType].scale) + winpos.x;
							float radY2 = maps[MapType].y_offset - (e2->getPosition().y * maps[MapType].scale) + winpos.y;

							drawList->AddLine(ImVec2(radX, radY), ImVec2(radX2, radY2), e->getColor());
						}
					}
				}
			}
		}

		if (State.ShowRadar_RightClick_Teleport)
			OnClick();

		ImGui::End();
	}
}