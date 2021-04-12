#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"

void dControllerManager_CloseOverlayMenu(ControllerManager* __this, String* menuName, MethodInfo* method)
{
	ControllerManager_CloseOverlayMenu(__this, menuName, method);
	if (convert_from_string(menuName) == "MeetingHub(Clone)")
	{
		ControllerManager_ResetAll(__this, NULL);
		LOG_INFO("Reset ControllerManager to fix Innersloth movement bug");
	}
}