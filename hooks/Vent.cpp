#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include <memory>

float dVent_CanUse(Vent* __this, GameData_PlayerInfo* pc, bool* canUse, bool* couldUse, MethodInfo* method) {
	if (State.UnlockVents) {
		auto object = GameData_PlayerInfo_get_Object(pc, nullptr);
		if (!object) {
			LOG_ERROR(ToString(pc) + " _object is null");
			return app::Vent_CanUse(__this, pc, canUse, couldUse, method);
		}

		auto ventTransform = app::Component_get_transform((Component_1*)__this, NULL);
		auto ventVector = app::Transform_get_position(ventTransform, NULL);

		auto playerPosition = app::PlayerControl_GetTruePosition(object, NULL);

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
	synchronized(Replay::replayEventMutex) {
		State.liveReplayEvents.emplace_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_ACTIONS::VENT_ENTER));
	}
	Vent_EnterVent(__this, pc, method);
}

void dVent_ExitVent(Vent* __this, PlayerControl* pc, MethodInfo * method) {
	auto ventVector = app::Transform_get_position(app::Component_get_transform((Component_1*)__this, NULL), NULL);
	app::Vector2 ventVector2D = {ventVector.x, ventVector.y};
	synchronized(Replay::replayEventMutex) {
		State.liveReplayEvents.emplace_back(std::make_unique<VentEvent>(GetEventPlayerControl(pc).value(), ventVector2D, VENT_ACTIONS::VENT_EXIT));
	}
	Vent_ExitVent(__this, pc, method);
}