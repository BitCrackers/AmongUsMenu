#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

bool dConstants_ShouldFlipSkeld(MethodInfo* method) {
	bool orig_return = Constants_ShouldFlipSkeld(method);
	if (State.FlipSkeld) {
		return true;
	}
	else if (orig_return)
	{
		State.FlipSkeld = true;
	}
	return orig_return;
}