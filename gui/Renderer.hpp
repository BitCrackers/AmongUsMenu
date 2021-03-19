#pragma once

#include "RenderCmd.hpp"

#include <utility>
#include <assert.h>

class ImGuiRenderer
{
public:
	using RenderCommandFunc = void(*)(void*);

	template<typename Function>
	static void Submit(Function&& function)
	{
		auto renderCmd = [](void* ptr) {
			auto pFunction = (Function*)ptr;
			(*pFunction)();

			//static_assert(std::is_trivially_destructible_v<Function>, "Function must be trivially destructible");
			pFunction->~Function();
		};
		auto storageBuffer = GetCmdQueue().Allocate(renderCmd, sizeof(function));
		new (storageBuffer) Function(std::forward<Function>(function));
	}

	static void ExecuteQueue();
private:
	static RenderCmdQueue& GetCmdQueue();
};