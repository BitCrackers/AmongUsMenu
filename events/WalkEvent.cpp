#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

WalkEvent::WalkEvent(EVENT_PLAYER source, Vector2 position) : EventInterface(source, EVENT_TYPES::EVENT_WALK) {
	this->position = position;
}

void WalkEvent::Output() {
	// not needed
}

void WalkEvent::ColoredEventOutput() {
	// not needed
}