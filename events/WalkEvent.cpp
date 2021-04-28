#include "pch-il2cpp.h"
#include "_events.h"

WalkEvent::WalkEvent(EVENT_PLAYER source) : EventInterface(source, EVENT_WALK, ImColor(1.0f, 1.0f, 0.0f, 1.0f)) {
}

void WalkEvent::Output() {
	// not needed
}

void WalkEvent::ColoredEventOutput() {
	// not needed
}