#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

WalkEvent::WalkEvent(EVENT_PLAYER source, Vector2 position) : EventInterface(source, EVENT_WALK) {
	this->position = position;
}

void WalkEvent::Output() {
	return;
}

void WalkEvent::ColoredEventOutput() {
	return;
}