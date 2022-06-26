#pragma once
#include <optional>
#include <chrono>
#include <format>
#include "il2cpp-helpers.h"
#include "game.h"

using namespace app;

#define ALL_EVENTS \
	ADD_EVENT (KILL, "Kill"), \
	ADD_EVENT (VENT, "Vent"), \
	ADD_EVENT (TASK, "Task"), \
	ADD_EVENT (REPORT, "Report"), \
	ADD_EVENT (MEETING, "Meeting"), \
	ADD_EVENT (VOTE, "Vote"), \
	ADD_EVENT (CHEAT, "Cheat"), \
	ADD_EVENT (DISCONNECT, "Disconnect"), \
	ADD_EVENT (SHAPESHIFT, "Shapeshift"), \
	ADD_EVENT (PROTECTPLAYER, "Protect"), \
	ADD_EVENT (WALK, "Walk")

enum class EVENT_TYPES {
#define ADD_EVENT(name, desc) EVENT_ ## name
	ALL_EVENTS,
#undef ADD_EVENT
	EVENT_TYPES_SIZE
};

enum class VENT_ACTIONS {
	VENT_ENTER,
	VENT_EXIT
};

enum class CHEAT_ACTIONS {
	CHEAT_TELEPORT,
	CHEAT_KILL_IMPOSTOR
};

const std::vector<const char*> CHEAT_ACTION_NAMES = { "Teleporting", "Killed impostor" };

struct EVENT_PLAYER {
	Game::PlayerId playerId;
	Game::ColorId colorId;
	std::string playerName;
	bool isDead;
	bool isAngel;
	bool isProtected;

	EVENT_PLAYER() {
		playerId = Game::NoPlayerId;
		colorId = Game::NoColorId;
		playerName = "";
		isDead = false;
		isAngel = false;
		isProtected = false;
	}

	EVENT_PLAYER(GameData_PlayerInfo* playerInfo) {
		playerId = playerInfo->fields.PlayerId;

		GameData_PlayerOutfit* outfit = app::GameData_PlayerInfo_get_DefaultOutfit(playerInfo, nullptr);
		if (outfit != nullptr)
		{
			colorId = outfit->fields.ColorId;
			playerName = convert_from_string(app::GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
		}
		else
		{
			colorId = Game::NoColorId;
			playerName = "ERROR";
		}

		isDead = playerInfo->fields.IsDead;
		isAngel = (playerInfo->fields.Role) ? playerInfo->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel : false;
		
		if (auto object = GameData_PlayerInfo_get_Object(playerInfo, nullptr))
			isProtected = object->fields.protectedByGuardian;
		else
			isProtected = false;
	}
};

class EventInterface {
protected:
	EVENT_TYPES eventType;
	EVENT_PLAYER source;
	std::chrono::system_clock::time_point timestamp;
public:
	EventInterface(const EVENT_PLAYER& source, EVENT_TYPES eventType) {
		this->source = source;
		this->eventType = eventType;
		this->timestamp = std::chrono::system_clock::now();
	}
	virtual ~EventInterface() {}
	virtual void Output() = 0;
	virtual void ColoredEventOutput() = 0;
	EVENT_TYPES getType() const { return this->eventType; }
	const EVENT_PLAYER& getSource() const { return this->source; }
	const std::chrono::system_clock::time_point& GetTimeStamp() const { return this->timestamp; }
};

class KillEvent : public EventInterface {
private:
	EVENT_PLAYER target;
	Vector2 position;
	Vector2 targetPosition;
	SystemTypes__Enum systemType;
public:
	KillEvent(const EVENT_PLAYER& source, const EVENT_PLAYER& target, const Vector2& position, const Vector2& targetPosition);
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
	VentEvent(const EVENT_PLAYER& source, const Vector2& position, VENT_ACTIONS action);
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
	TaskCompletedEvent(const EVENT_PLAYER& source, const std::optional<TaskTypes__Enum>& taskType, const Vector2& position);
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
	ReportDeadBodyEvent(const EVENT_PLAYER& source, const std::optional<EVENT_PLAYER>& target, const Vector2& position, const std::optional<Vector2>& targetPosition);
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
	CastVoteEvent(const EVENT_PLAYER& source, const std::optional<EVENT_PLAYER>& target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	std::optional<EVENT_PLAYER> GetTarget() { return this->target; }
};

class CheatDetectedEvent : public EventInterface {
private:
	CHEAT_ACTIONS action;
public:
	CheatDetectedEvent(const EVENT_PLAYER& source, CHEAT_ACTIONS action);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	CHEAT_ACTIONS GetCheatAction() { return this->action; }
};

class DisconnectEvent : public EventInterface {
public:
	DisconnectEvent(const EVENT_PLAYER& source);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
};

class ShapeShiftEvent : public EventInterface {
private:
	EVENT_PLAYER target;
public:
	ShapeShiftEvent(const EVENT_PLAYER& source, const EVENT_PLAYER& target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	EVENT_PLAYER GetTarget() { return this->target; }
};

class ProtectPlayerEvent : public EventInterface {
private:
	EVENT_PLAYER target;
public:
	ProtectPlayerEvent(const EVENT_PLAYER& source, const EVENT_PLAYER& target);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	EVENT_PLAYER GetTarget() { return this->target; }
};

class WalkEvent : public EventInterface {
private:
	Vector2 position;
public:
	WalkEvent(const EVENT_PLAYER& source, const Vector2& position);
	virtual void Output() override;
	virtual void ColoredEventOutput() override;
	Vector2 GetPosition() { return this->position; }
};