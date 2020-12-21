#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

bool dConstants_ShouldFlipSkeld(MethodInfo* method) {
	if (State.FlipSkeld) {
		return true;
	}
	return Constants_ShouldFlipSkeld(method);
}