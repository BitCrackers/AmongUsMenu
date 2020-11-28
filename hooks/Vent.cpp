#include "_hooks.hpp"

using namespace app;

float dVent_CanUse(Vent* __this, GameData_PlayerInfo* pc, bool* canUse, bool* couldUse, MethodInfo* method) {
	if (State.UnlockVents) {
		auto ventTransform = app::Component_get_transform((Component*)__this, NULL);
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
	auto ventVector = app::Transform_get_position(app::Component_get_transform((Component*)__this, NULL), NULL);
	State.events.push_back(new VentEvent(GetEventPlayer(pc), { ventVector.x, ventVector.y }, VENT_ENTER));
	Vent_EnterVent(__this, pc, method);
}

void dVent_ExitVent(Vent* __this, PlayerControl* pc, MethodInfo * method) {
	auto ventVector = app::Transform_get_position(app::Component_get_transform((Component*)__this, NULL), NULL);
	State.events.push_back(new VentEvent(GetEventPlayer(pc), { ventVector.x, ventVector.y }, VENT_EXIT));
	Vent_ExitVent(__this, pc, method);
}