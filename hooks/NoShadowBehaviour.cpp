#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dNoShadowBehaviour_LateUpdate(NoShadowBehaviour* __this, MethodInfo* method) {
	if ((State.Wallhack || State.FreeCam || State.EnableZoom) && !State.OcclusionCulling) {
		NoShadowBehaviour_SetMaskFunction(__this, 8, NULL);
	}
	else {
		NoShadowBehaviour_LateUpdate(__this, method);
	}
	return;
}