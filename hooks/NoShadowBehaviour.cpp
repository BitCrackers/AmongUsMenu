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

void dLightSource_DrawOcclusion(LightSource* __this, float effectiveRadius, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_DrawOcclusion(__this, effectiveRadius, method);
}

void dLightSource_Start(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_Start(__this, method);
}

void dLightSource_Update(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_Update(__this, method);
}

void dLightSource_ClearEdges(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_ClearEdges(__this, method);
}

void dLightSource_GenerateShadowmap(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_GenerateShadowmap(__this, method);
}

void dLightSource_UpdateOccMesh(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_UpdateOccMesh(__this, method);
}

void dLightSource_GPUShadows(LightSource* __this, Vector2 myPos, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		return;
	}
	LightSource_GPUShadows(__this, myPos, method);
}