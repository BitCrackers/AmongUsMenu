#include "pch-il2cpp.h"
#include "radar.hpp"
#include "DirectX.h"
#include "utility.h"
#include "state.hpp"

namespace Radar {
	ImU32 GetRadarPlayerColor(GameData_PlayerInfo* playerData) {
		return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4((GetPlayerColor(GetPlayerOutfit(playerData)->fields.ColorId))));
	}

	ImU32 GetRadarPlayerColorStatus(GameData_PlayerInfo* playerData) {
		if (playerData->fields.IsDead)
			return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->HalfWhite));
		else if (State.RevealRoles && playerData->fields.Role != nullptr && playerData->fields.Role->fields.StringName != StringNames__Enum::Crewmate)
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

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5f + 10.f, (float)maps[MapType].mapImage.imageHeight * 0.5f + 10.f), ImGuiCond_None);

		if(State.LockRadar)
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		else
			ImGui::Begin("Radar", &State.ShowRadar, ImGuiWindowFlags_NoDecoration);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 winpos = ImGui::GetWindowPos();

		ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView,
			ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F),
			ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
			State.SelectedColor);

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

			IconTexture icon = icons.at(ICON_TYPES::PLAYER);
			float radX = maps[MapType].x_offset + (playerPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + winpos.x;
			float radY = maps[MapType].y_offset - (playerPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + winpos.y;
			float radXMax = maps[MapType].x_offset + (playerPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + winpos.x;
			float radYMax = maps[MapType].y_offset - (playerPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + winpos.y;

			drawList->AddImage((void*)icon.iconImage.shaderResourceView,
				ImVec2(radX, radY),
				ImVec2(radXMax, radYMax),
				ImVec2(0.0f, 1.0f),
				ImVec2(1.0f, 0.0f),
				GetRadarPlayerColor(playerData));

			if (playerData->fields.IsDead)
				drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView,
					ImVec2(radX, radY),
					ImVec2(radXMax, radYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
		}

		if (State.ShowRadar_DeadBodies) {
			for (auto deadBody : GetAllDeadBodies()) {
				auto playerData = GetPlayerDataById(deadBody->fields.ParentId);

				Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

				IconTexture icon = icons.at(ICON_TYPES::PLAYER); // TODO: replace with dead body icon
				float radX = maps[MapType].x_offset + (bodyPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + winpos.x;
				float radY = maps[MapType].y_offset - (bodyPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + winpos.y;
				float radXMax = maps[MapType].x_offset + (bodyPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + winpos.x;
				float radYMax = maps[MapType].y_offset - (bodyPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + winpos.y;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(radX, radY),
					ImVec2(radXMax, radYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f),
					GetRadarPlayerColor(playerData));
			}
		}

		if (State.ShowRadar_RightClick_Teleport)
			OnClick();

		ImGui::End();
	}
}