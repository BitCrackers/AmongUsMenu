#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

#include <memory>

float dVent_CanUse(Vent* __this, GameData_PlayerInfo* pc, bool* canUse, bool* couldUse, MethodInfo* method) {
	if (State.UnlockVents) {
		auto ventTransform = app::Component_get_transform((Component_1*)__this, NULL);
		auto ventVector = app::Transform_get_position(ventTransform, NULL);

		auto playerPosition = app::PlayerControl_GetTruePosition(pc->fields._object, NULL);

		float ventDistance = app::Vector2_Distance(playerPosition, { ventVector.x, ventVector.y }, NULL);
		if (pc->fields.IsDead) {
			*canUse = false;
			*couldUse = false;
		}
		else {
			*canUse = (ventDistance < app::Vent_get_UsableDistance(__this, NULL));
			*couldUse = true;
		}
		return ventDistance;
	}

	return app::Vent_CanUse(__this, pc, canUse, couldUse, method);
};

void dVent_EnterVent(Vent* __this, PlayerControl* pc, MethodInfo * method) {

	auto ventVector = app::Transform_get_position(app::Component_get_transform((Component_1*)__this, NULL), NULL);
	app::Vector2 ventVector2D = {ventVector.x, ventVector.y};
	State.rawEvents.push_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_ENTER));
	State.liveReplayEvents.push_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_ENTER));

	Vent_EnterVent(__this, pc, method);
}

void dVent_ExitVent(Vent* __this, PlayerControl* pc, MethodInfo * method) {

	auto ventVector = app::Transform_get_position(app::Component_get_transform((Component_1*)__this, NULL), NULL);
	app::Vector2 ventVector2D = {ventVector.x, ventVector.y};
	State.rawEvents.push_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_EXIT));
	State.liveReplayEvents.push_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_EXIT));

	Vent_ExitVent(__this, pc, method);
}