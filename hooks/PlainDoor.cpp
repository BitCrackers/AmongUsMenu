#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include <iostream>

void dDoorBreakerGame_Start(DoorBreakerGame* __this, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        static Il2CppClass* klassPlainDoor = get_class("Assembly-CSharp, PlainDoor");
        if (il2cpp_class_is_assignable_from(klassPlainDoor, __this->fields.MyDoor->klass)) {
            State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Doors, __this->fields.MyDoor->fields.Id | 64));
            PlainDoor_SetDoorway((PlainDoor*)__this->fields.MyDoor, true, NULL);
            Minigame_Close((Minigame*)__this, NULL);
            return;
        }
    }
    DoorBreakerGame_Start(__this, method);
}

void dDoorCardSwipeGame_Begin(DoorCardSwipeGame* __this, PlayerTask* playerTask, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        static Il2CppClass* klassPlainDoor = get_class("Assembly-CSharp, PlainDoor");
        if (il2cpp_class_is_assignable_from(klassPlainDoor, __this->fields.MyDoor->klass)) {
            __this->fields.State = DoorCardSwipeGame_TaskStages__Enum::Inserted;
            State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Doors, __this->fields.MyDoor->fields.Id | 64));
            PlainDoor_SetDoorway((PlainDoor*)__this->fields.MyDoor, true, NULL);
            Minigame_Close((Minigame*)__this, NULL);
            return;
        }
    }
    DoorCardSwipeGame_Begin(__this, playerTask, method);
}

void dMushroomDoorSabotageMinigame_Begin(MushroomDoorSabotageMinigame* __this, PlayerTask* task, MethodInfo* method) {
    if (State.AutoOpenDoors) {
        __this->fields.mushroomWhackCount = 6; //six mushrooms are to be whacked
        State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Doors, __this->fields.myDoor->fields.Id | 64));
        MushroomDoorSabotageMinigame_SetDoor(__this, (OpenableDoor*)__this->fields.myDoor->fields.Open, NULL);
        Minigame_Close((Minigame*)__this, NULL);
        return;
    }
    MushroomDoorSabotageMinigame_Begin(__this, task, method);
}