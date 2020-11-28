#include "radar.hpp"

using namespace app;

namespace Radar {
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
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !(*Game::pLocalPlayer)->fields.inVent) {
			ImVec2 mouse = ImGui::GetMousePos();
			ImVec2 winpos = ImGui::GetWindowPos();
			ImVec2 winsize = ImGui::GetWindowSize();
			int MapType = (*Game::pShipStatus)->fields.Type;

			if (mouse.x < winpos.x
				|| mouse.x > winpos.x + winsize.x
				|| mouse.y < winpos.y
				|| mouse.y > winpos.y + winsize.y)
				return;

			Vector2 target = {
				(mouse.x - winpos.x - maps[MapType].x_offset) / maps[MapType].scale,
				((mouse.y - winpos.y - maps[MapType].y_offset) * -1.F) / maps[MapType].scale
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

		int MapType = (*Game::pShipStatus)->fields.Type;
		ImGui::SetNextWindowSize(ImVec2((float)maps[MapType].width * 0.5F + 10, (float)maps[MapType].height * 0.5F + 10), ImGuiCond_Once);
		ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 winpos = ImGui::GetWindowPos();
		ImVec2 winsize = ImGui::GetWindowSize();

		ImGui::Image((void*)maps[MapType].buffer, ImVec2((float)maps[MapType].width * 0.5F, (float)maps[MapType].height * 0.5F), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));

		for (auto player : GetAllPlayerControl()) {
			auto playerData = GetPlayerData(player);

			if (!playerData || (!State.ShowRadar_Ghosts && playerData->fields.IsDead))
				continue;

			Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

			float radX = maps[MapType].x_offset + (playerPos.x * maps[MapType].scale) + winpos.x;
			float radY = maps[MapType].y_offset - (playerPos.y * maps[MapType].scale) + winpos.y;

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

		if (State.ShowRadar_RightClick_Teleport)
			OnClick();

		ImGui::End();
	}
}