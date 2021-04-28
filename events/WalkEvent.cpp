#include "pch-il2cpp.h"
#include "_events.h"

WalkEvent::WalkEvent(EVENT_PLAYER source, Vector2 position) : EventInterface(source, EVENT_WALK, ImColor(1.0f, 1.0f, 0.0f, 1.0f)) {
	this->position = position;
}

void WalkEvent::Output() {
	// not needed
}

void WalkEvent::ColoredEventOutput() {
	// not needed
}