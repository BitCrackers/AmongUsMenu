#include "Renderer.hpp"
#include "RenderCmd.hpp"
#include "DirectX.h"
#include "logger.h"

static RenderCmdQueue s_CmdQueue;

void ImGuiRenderer::ExecuteQueue()
{
	WaitForSingleObject(DirectX::hRenderSemaphore, INFINITE);
	s_CmdQueue.Execute();
	ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);
}

RenderCmdQueue& ImGuiRenderer::GetCmdQueue()
{
	return s_CmdQueue;
}