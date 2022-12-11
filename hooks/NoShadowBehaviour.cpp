#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"

void dNoShadowBehaviour_SetMaskFunction(NoShadowBehaviour* __this, int32_t func, MethodInfo* method) {
	if ((State.Wallhack || State.FreeCam || State.EnableZoom) && !State.OcclusionCulling) {
		NoShadowBehaviour_SetMaskFunction(__this, 8, NULL);
		return;
	}
	NoShadowBehaviour_SetMaskFunction(__this, func, NULL);
}
	