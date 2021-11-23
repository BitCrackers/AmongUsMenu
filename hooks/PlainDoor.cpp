#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include <iostream>

void dDoorBreakerGame_Start(DoorBreakerGame* __this, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Doors, __this->fields.MyDoor->fields.Id | 64));
        PlainDoor_SetDoorway(__this->fields.MyDoor, true, NULL);
        Minigame_Close((Minigame*)__this, NULL);
        return;
    }
    DoorBreakerGame_Start(__this, method);
}

void dDoorCardSwipeGame_Begin(DoorCardSwipeGame* __this, PlayerTask* playerTask, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        __this->fields.State = DoorCardSwipeGame_TaskStages__Enum::Inserted;
        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Doors, __this->fields.MyDoor->fields.Id | 64));
        PlainDoor_SetDoorway(__this->fields.MyDoor, true, NULL);
        Minigame_Close((Minigame*)__this, NULL);
        return;
    }
    DoorCardSwipeGame_Begin(__this, playerTask, method);
}