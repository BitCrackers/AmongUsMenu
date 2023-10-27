#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include <iostream>

using namespace std::string_view_literals;

static bool OpenDoor(OpenableDoor* door) {
    if ("PlainDoor"sv == door->klass->name) {
        app::PlainDoor_SetDoorway(reinterpret_cast<PlainDoor*>(door), true, {});
    }
    else if ("MushroomWallDoor"sv == door->klass->name) {
        app::MushroomWallDoor_SetDoorway(reinterpret_cast<MushroomWallDoor*>(door), true, {});
    }
    else {
        return false;
    }
    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Doors, door->fields.Id | 64));
    return true;
}

void dMushroomDoorSabotageMinigame_Begin(MushroomDoorSabotageMinigame* __this, PlayerTask* task, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        if (OpenDoor(__this->fields.myDoor)) {
            Minigame_Close((Minigame*)__this, {});
            return;
        }
    }
    app::MushroomDoorSabotageMinigame_Begin(__this, task, method);
}

void dDoorBreakerGame_Start(DoorBreakerGame* __this, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        if (OpenDoor(__this->fields.MyDoor)) {
            Minigame_Close((Minigame*)__this, {});
            return;
        }
    }
    DoorBreakerGame_Start(__this, method);
}

void dDoorCardSwipeGame_Begin(DoorCardSwipeGame* __this, PlayerTask* playerTask, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        __this->fields.State = DoorCardSwipeGame_TaskStages__Enum::Inserted;
        if (OpenDoor(__this->fields.MyDoor)) {
            Minigame_Close((Minigame*)__this, {});
            return;
        }
    }
    DoorCardSwipeGame_Begin(__this, playerTask, method);
}