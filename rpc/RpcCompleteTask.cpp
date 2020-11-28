#include "_rpc.h"
#include "utility.h"
#include "state.hpp"

RpcCompleteTask::RpcCompleteTask(uint32_t taskId)
{
	this->taskId = taskId;
}

void RpcCompleteTask::Process()
{
	auto tasks = GetNormalPlayerTasks(*Game::pLocalPlayer);

	for (auto task : tasks) {
		if (task->fields._._Id_k__BackingField == taskId && !NormalPlayerTask_get_IsComplete(task, NULL)) {
			CompleteTask(task);
		}
	}
}