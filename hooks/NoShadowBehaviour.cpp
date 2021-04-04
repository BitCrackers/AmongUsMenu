#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"

void dNoShadowBehaviour_LateUpdate(NoShadowBehaviour* __this, MethodInfo* method) {
	if ((State.Wallhack || State.FreeCam || State.EnableZoom) && !State.OcclusionCulling) {
		NoShadowBehaviour_SetMaskFunction(__this, 8, NULL);
	}
	else {
		NoShadowBehaviour_LateUpdate(__this, method);
	}
	return;
}

void dShadowCollab_OnEnable(ShadowCollab* __this, MethodInfo* method) {
	ShadowCollab_OnEnable(__this, method);
	State.shadowLayer = __this;
#ifdef _DEBUG
	Log.Debug("ShadowLayer Enabled");
#endif
}