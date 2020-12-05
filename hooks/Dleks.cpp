#include "_hooks.hpp"

using namespace app;

bool dConstants_ShouldFlipSkeld(MethodInfo* method) {
	if (State.FlipSkeld) {
		return true;
	}
	return Constants_ShouldFlipSkeld(method);
}