#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"

void dControllerManager_CloseOverlayMenu(ControllerManager* __this, String* menuName, MethodInfo* method)
{
	auto strMenuName = convert_from_string(menuName);
	STREAM_DEBUG("Closing " << strMenuName);
	
	ControllerManager_CloseOverlayMenu(__this, menuName, method);
	if (strMenuName == "MeetingHub(Clone)")
		ControllerManager_ResetAll(__this, NULL);
}