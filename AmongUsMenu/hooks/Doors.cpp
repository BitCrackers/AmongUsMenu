#include "_hooks.hpp"

using namespace app;

void dPlainDoor_SetDoorway(PlainDoor* __this, bool open, MethodInfo* method) {
	if (open && (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), __this->fields.Room) != State.pinnedDoors.end())) {
		State.rpcQueue.push(new RpcCloseDoorsOfType(__this->fields.Room, false));
	}
	app::PlainDoor_SetDoorway(__this, open, method);
}

bool dAutoOpenDoor_DoUpdate(AutoOpenDoor* __this, float dt, MethodInfo* method) {
	if ((std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), __this->fields._.Room) != State.pinnedDoors.end()) && __this->fields.ClosedTimer < 1) {
		State.rpcQueue.push(new RpcCloseDoorsOfType(__this->fields._.Room, false));
	}
	return app::AutoOpenDoor_DoUpdate(__this, dt, method);
}