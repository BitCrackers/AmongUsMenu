#pragma once
#include <optional>
#include <chrono>

using namespace app;

#define EVENT_TYPES_SIZE 11

enum EVENT_TYPES {
	EVENT_KILL,
	EVENT_VENT,
	EVENT_TASK,
	EVENT_REPORT,
	EVENT_MEETING,
	EVENT_VOTE,
	EVENT_CHEAT,
	EVENT_DISCONNECT,
	EVENT_SHAPESHIFT,
	EVENT_PROTECTPLAYER,
	EVENT_WALK
};

enum VENT_ACTIONS {
	VENT_ENTER,
	VENT_EXIT
};

enum CHEAT_ACTIONS {
	CHEAT_TELEPORT,
	CHEAT_KILL_IMPOSTOR
};

const std::vector<const char*> CHEAT_ACTION_NAMES = { "Teleporting", "Killed impostor" };

struct EVENT_PLAYER {
	uint8_t playerId;
	uint8_t colorId;
	std::string playerName;
	bool isDead;
	bool isAngel;

	EVENT_PLAYER() {
		playerId = 0;
		colorId = 0;
		playerName = "";
		isDead = false;
		isAngel = false;
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

		isDead = playerInfo->fields.IsDead;
		isAngel = (playerInfo->fields.Role) ? playerInfo->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel : false;
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
	std::chrono::system_clock::time_point GetTimeStamp() { return this->timestamp; }
};

class KillEvent : public EventInterface {
private:
	EVENT_PLAYER target;
	Vector2 position;
	Vector2 targetPosition;
	SystemTypes__Enum systemType;
public:
	KillEvent(EVENT_PLAYER source, EVENT_PLAYER target, Vector2 position, Vector2 targetPosition);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	std::optional<EVENT_PLAYER> GetTarget() { return this->target; }
	Vector2 GetPosition() { return this->position; }
	Vector2 GetTargetPosition() { return this->targetPosition; }
	SystemTypes__Enum GetSystemType() { return this->systemType; }
};

class VentEvent : public EventInterface {
private:
	Vector2 position;
	SystemTypes__Enum systemType;
	VENT_ACTIONS action;
public:
	VentEvent(EVENT_PLAYER source, Vector2 position, VENT_ACTIONS action);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	Vector2 GetPosition() { return this->position; }
	VENT_ACTIONS GetEventActionEnum() { return this->action; }
	std::string GetEventActionString()
	{
		switch (this->action)
		{
		case VENT_ACTIONS::VENT_ENTER:
			return std::string("Enter");
			break;

		case VENT_ACTIONS::VENT_EXIT:
			return std::string("Exit");
			break;

		default:
			break;
		}
	}
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
	std::optional<TaskTypes__Enum> GetTaskType() { return this->taskType; }
	Vector2 GetPosition() { return this->position; }
	SystemTypes__Enum GetSystemType() { return this->systemType; }

};

class ReportDeadBodyEvent : public EventInterface {
private:
	std::optional<EVENT_PLAYER> target;
	Vector2 position;
	std::optional<Vector2> targetPosition;
	SystemTypes__Enum systemType;
public:
	ReportDeadBodyEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target, Vector2 position, std::optional<Vector2> targetPosition);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	std::optional<EVENT_PLAYER> GetTarget() { return this->target; }
	Vector2 GetPosition() { return this->position; }
	std::optional<Vector2> GetTargetPosition() { return this->targetPosition; }
	SystemTypes__Enum GetSystemType() { return this->systemType; }
};

class CastVoteEvent : public EventInterface {
private:
	std::optional<EVENT_PLAYER> target;
public:
	CastVoteEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	std::optional<EVENT_PLAYER> GetTarget() { return this->target; }
};

class CheatDetectedEvent : public EventInterface {
private:
	CHEAT_ACTIONS action;
public:
	CheatDetectedEvent(EVENT_PLAYER source, CHEAT_ACTIONS action);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	CHEAT_ACTIONS GetCheatAction() { return this->action; }
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
	EVENT_PLAYER GetTarget() { return this->target; }
};

class ProtectPlayerEvent : public EventInterface {
private:
	EVENT_PLAYER target;
public:
	ProtectPlayerEvent(EVENT_PLAYER source, EVENT_PLAYER target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	EVENT_PLAYER GetTarget() { return this->target; }
};

class WalkEvent : public EventInterface {
private:
	Vector2 position;
public:
	WalkEvent(EVENT_PLAYER source, Vector2 position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	Vector2 GetPosition() { return this->position; }
};