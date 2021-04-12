#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"

void dControllerManager_CloseOverlayMenu(ControllerManager* __this, String* menuName, MethodInfo* method)
{
	auto currentMenuName = __this->fields.CurrentUiState->fields.MenuName;

	//This bug is present as Innersloth somehow cloned MeetingHub, and it does not reset controller input upon closing
	ControllerManager_CloseOverlayMenu(__this, menuName, method);
	if (convert_from_string(menuName) == "ChatUi" && convert_from_string(currentMenuName) == "MeetingHub(Clone)")
	{
		LOG_INFO("Reset ControllerManager Input to fix Innersloth movement bug");
		ControllerManager_ResetAll(__this, NULL);
	}
}