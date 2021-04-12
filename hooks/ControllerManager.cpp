#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"
#include "utility.h"

void dControllerManager_CloseOverlayMenu(ControllerManager* __this, String* menuName, MethodInfo* method)
{
	auto currentMenuName = __this->fields.CurrentUiState->fields.MenuName;
	/*
	std::vector<ControllerUiElementsState*> uiStack = GetElementsFromList<List_1_ControllerUiElementsState_*, ControllerUiElementsState*>(__this->fields.CurrentUiStateStack);
	STREAM_DEBUG("Ui Stack Count: " << uiStack.size());
	for (ControllerUiElementsState* uiElement : uiStack)
	{
		STREAM_DEBUG("Ui Stack " << convert_from_string(uiElement->fields.MenuName));
	}
	*/
	if (convert_from_string(menuName) == "MeetingHub(Clone)" && convert_from_string(currentMenuName) == "PlayerButton(Clone)")
	{
		LOG_INFO("Close PlayerButton before MeetingHub to fix Innersloth movement bug");
		ControllerManager_CloseOverlayMenu(__this, currentMenuName, method);
	}
	ControllerManager_CloseOverlayMenu(__this, menuName, method);
}