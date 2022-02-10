#include "pch-il2cpp.h"
#include "replay.hpp"
#include "DirectX.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace Replay
{
	void SquareConstraint(ImGuiSizeCallbackData* data)
	{
		data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.y);
	}

	void Init()
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render()
	{
		if (!init)
			Replay::Init();

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F + 30, (float)maps[MapType].mapImage.imageHeight * 0.5F + 100), ImGuiCond_None);

		ImGui::Begin("Replay", &State.ShowReplay, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

		ImGui::BeginChild("console#filter", ImVec2(490, 20), true);
		//ImGui::Text("Filter\t");
		//ImGui::SameLine();
		////CUSTOMLIXTBOXINTMULTIPLE
		ImGui::EndChild();
		ImGui::Separator();

		ImGui::BeginChild("ReplayMap");

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 winpos = ImGui::GetWindowPos();

		ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView,
			ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F),
			(State.FlipSkeld && MapType == 0) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
			State.SelectedReplayMapColor);

		ImGui::Text(std::string("X Window: " + std::to_string(ImGui::GetWindowSize().x)).c_str());
		ImGui::Text(std::string("Y Window: " + std::to_string(ImGui::GetWindowSize().y)).c_str());

		ImGui::EndChild();

		ImGui::End();
	}
}