#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dKeyboardJoystick_Update(KeyboardJoystick* __this, MethodInfo* method) {
    if (!State.FreeCam && !State.playerToFollow.has_value()) {
        app::KeyboardJoystick_Update(__this, method);
    }
}