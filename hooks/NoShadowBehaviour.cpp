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

void dLightSource_Update(LightSource* __this, MethodInfo* method) {
	if (State.FreeCam || State.Wallhack || State.EnableZoom) {
		Mesh_Clear(__this->fields.myMesh, NULL);
		Mesh_Clear(__this->fields.occluderMesh, NULL);
		CommandBuffer_Clear(__this->fields.cb, NULL);
		RenderTexture_Release(__this->fields.shadowTexture, NULL);
		Material_set_color(__this->fields.shadowCasterMaterial, Color_get_clear(NULL), NULL);
		return;
	}
	LightSource_Update(__this, method);
}