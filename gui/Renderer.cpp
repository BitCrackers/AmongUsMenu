#include "Renderer.hpp"
#include "RenderCmd.hpp"

static RenderCmdQueue s_CmdQueue;

void ImGuiRenderer::ExecuteQueue()
{
	s_CmdQueue.Execute();
}

RenderCmdQueue& ImGuiRenderer::GetCmdQueue()
{
	return s_CmdQueue;
}