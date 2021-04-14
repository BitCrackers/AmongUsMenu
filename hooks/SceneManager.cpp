#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"

void dSceneManager_Internal_ActiveSceneChanged(Scene previousActiveScene, Scene newActiveScene, MethodInfo* method) {
	//State.CurrentScene = convert_from_string(app::Scene_GetNameInternal(newActiveScene.m_Handle, NULL));
	app::SceneManager_Internal_ActiveSceneChanged(previousActiveScene, newActiveScene, method);
}

void dTutorialManager_Awake(TutorialManager* __this, MethodInfo* method) {
	State.Tutorial = true;
	LOG_DEBUG("Entered tutorial");
	TutorialManager_Awake(__this, method);
}

void dTutorialManager_OnDestroy(TutorialManager* __this, MethodInfo* method) {
	State.Tutorial = false;
	LOG_DEBUG("Exited tutorial");
	TutorialManager_OnDestroy(__this, method);
}