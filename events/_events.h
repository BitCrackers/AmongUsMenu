#pragma once
#include <optional>
#include <chrono>
//#include "utility.h"

using namespace app;

#define EVENT_TYPES_SIZE 11

enum EVENT_TYPES {
	EVENT_KILL = 0,
	EVENT_VENT = 1,
	EVENT_TASK = 2,
	EVENT_REPORT = 3,
	EVENT_MEETING = 4,
	EVENT_VOTE = 5,
	EVENT_CHEAT = 6,
	EVENT_DISCONNECT = 7,
	EVENT_SHAPESHIFT = 8,
	EVENT_PROTECTPLAYER = 9,
	EVENT_WALK = 10
};

enum VENT_ACTION {
	VENT_ENTER = 0x0,
	VENT_EXIT = 0x1
};

enum CHEAT_ACTION {
	CHEAT_TELEPORT = 0x0,
	CHEAT_KILL_IMPOSTOR = 0x1
};

const std::vector<const char*> CHEAT_ACTION_NAMES = { "Teleporting", "Killed impostor" };

struct EVENT_PLAYER {
	uint8_t playerId;
	uint8_t colorId;
	std::string playerName;

	EVENT_PLAYER() {
		playerId = 0;
		colorId = 0;
		playerName = "";
	}

	EVENT_PLAYER(GameData_PlayerInfo* playerInfo) {
		playerId = playerInfo->fields.PlayerId;

		// rolling GetPlayerOutfit into this func to avoid circular dependencies
		GameData_PlayerOutfit* outfit = 0;
		auto arr = playerInfo->fields.Outfits->fields.entries;
		for (int i = 0; i < playerInfo->fields.Outfits->fields.count; i++)
		{
			auto kvp = arr->vector[i];
			if (kvp.key == PlayerOutfitType__Enum::Default)
			{
				outfit = kvp.value;
				break;
			}
		}

		if (outfit != 0)
		{
			colorId = outfit->fields.ColorId;
			playerName = convert_from_string(outfit->fields._playerName);
		}
		else
		{
			colorId = 0;
			playerName = "ERROR";
		}
	}
};

class EventInterface {
protected:
	EVENT_TYPES eventType;
	EVENT_PLAYER source;
	std::chrono::system_clock::time_point timestamp;
public:
	EventInterface(EVENT_PLAYER source, EVENT_TYPES eventType) {
		this->source = source;
		this->eventType = eventType;
		this->timestamp = std::chrono::system_clock::now();
	}
	virtual ~EventInterface() {}
	virtual void Output() = 0;
	virtual void ColoredEventOutput() = 0;
	EVENT_TYPES getType() { return this->eventType; }
	EVENT_PLAYER getSource() { return this->source; }
};

class KillEvent : public EventInterface {
private:
	EVENT_PLAYER target;
	Vector2 position;
	SystemTypes__Enum systemType;
public:
	KillEvent(EVENT_PLAYER source, EVENT_PLAYER target, Vector2 position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class VentEvent : public EventInterface {
private:
	Vector2 position;
	SystemTypes__Enum systemType;
	VENT_ACTION action;
public:
	VentEvent(EVENT_PLAYER source, Vector2 position, VENT_ACTION action);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class TaskCompletedEvent : public EventInterface {
private:
	std::optional<TaskTypes__Enum> taskType;
	Vector2 position;
	SystemTypes__Enum systemType;
public:
	TaskCompletedEvent(EVENT_PLAYER source, std::optional<TaskTypes__Enum> taskType, Vector2 position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class ReportDeadBodyEvent : public EventInterface {
private:
	std::optional<EVENT_PLAYER> target;
	Vector2 position;
	SystemTypes__Enum systemType;
public:
	ReportDeadBodyEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target, Vector2 position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class CastVoteEvent : public EventInterface {
private:
	std::optional<EVENT_PLAYER> target;
public:
	CastVoteEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class CheatDetectedEvent : public EventInterface {
private:
	CHEAT_ACTION action;
public:
	CheatDetectedEvent(EVENT_PLAYER source, CHEAT_ACTION action);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class DisconnectEvent : public EventInterface {
public:
	DisconnectEvent(EVENT_PLAYER source);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class ShapeShiftEvent : public EventInterface {
private:
	EVENT_PLAYER target;
public:
	ShapeShiftEvent(EVENT_PLAYER source, EVENT_PLAYER target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class ProtectPlayerEvent : public EventInterface {
private:
	EVENT_PLAYER target;
public:
	ProtectPlayerEvent(EVENT_PLAYER source, EVENT_PLAYER target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class WalkEvent : public EventInterface {
private:
	Vector2 position;
public:
	WalkEvent(EVENT_PLAYER source, Vector2 position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	virtual Vector2 GetPosition();
};