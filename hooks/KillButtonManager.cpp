#include "_hooks.hpp"
void dKillButtonManager_SetCoolDown(KillButtonManager* __this, float timer, float maxTimer, MethodInfo* method)
{
	State.KillCooldownExpired = (timer <= 0.0f);
	KillButtonManager_SetCoolDown(__this, timer, maxTimer, method);
}