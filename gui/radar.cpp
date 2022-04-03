#include "pch-il2cpp.h"
#include "radar.hpp"
#include "DirectX.h"
#include "utility.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace Radar {
	ImU32 GetRadarPlayerColor(GameData_PlayerInfo* playerData) {
		return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4((GetPlayerColor(GetPlayerOutfit(playerData)->fields.ColorId))));
	}

	ImU32 GetRadarPlayerColorStatus(GameData_PlayerInfo* playerData) {
		if (playerData->fields.IsDead)
			return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->HalfWhite));
		else if (State.RevealRoles
			&& playerData->fields.Role != nullptr
			&& playerData->fields.Role->fields.TeamType == RoleTeamTypes__Enum::Impostor)
			return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role)));
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

		Settings::MapType MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5f + 10.f, (float)maps[MapType].mapImage.imageHeight * 0.5f + 10.f) * State.dpiScale, ImGuiCond_None);

		if(State.LockRadar)
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		else
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration);

		ImVec2 winpos = ImGui::GetWindowPos();

		ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView,
			ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F) * State.dpiScale,
			ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
			State.SelectedColor);

		for (auto player : GetAllPlayerControl()) {
			auto playerData = GetPlayerData(player);

			if (!playerData || (!State.ShowRadar_Ghosts && playerData->fields.IsDead))
				continue;

			if (State.RadarDrawIcons)
				drawPlayerIcon(player, winpos, GetRadarPlayerColor(playerData));
			else
				drawPlayerDot(player, winpos, GetRadarPlayerColor(playerData), GetRadarPlayerColorStatus(playerData));
		}

		if (State.ShowRadar_DeadBodies) {
			for (auto deadBody : GetAllDeadBodies()) {
				auto playerData = GetPlayerDataById(deadBody->fields.ParentId);

				if (State.RadarDrawIcons)
					drawDeadPlayerIcon(deadBody, winpos, GetRadarPlayerColor(playerData));
				else
					drawDeadPlayerDot(deadBody, winpos, GetRadarPlayerColor(playerData));
			}
		}

		if (State.ShowRadar_RightClick_Teleport)
			OnClick();

		ImGui::End();
	}
}