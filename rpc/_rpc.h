#pragma once
#include "il2cpp-appdata.h"

using namespace app;

class RPCInterface {
public:
	virtual ~RPCInterface() {}
	virtual void Process() = 0;
};

class RpcCloseDoorsOfType : public RPCInterface {
	SystemTypes__Enum selectedSystem;
	bool pinDoor;
public:
	RpcCloseDoorsOfType(SystemTypes__Enum selectedSystem, bool pinDoor);
	virtual void Process() override;
};

class RpcSnapTo : public RPCInterface {
	Vector2 targetVector;
public:
	RpcSnapTo(Vector2 targetVector);
	virtual void Process() override;
};

class RpcRepairSystem : public RPCInterface {
	SystemTypes__Enum selectedSystem;
	int32_t amount;
public:
	RpcRepairSystem(SystemTypes__Enum selectedSystem, int32_t amount);
	virtual void Process() override;
};

class RpcCompleteTask : public RPCInterface {
	uint32_t taskId;
public:
	RpcCompleteTask(uint32_t taskId);
	virtual void Process() override;
};

class RpcMurderPlayer : public RPCInterface {
	PlayerControl* selectedPlayer;
	PlayerControl* murderer;
public:
	RpcMurderPlayer(PlayerControl* murdering_player, PlayerControl* selected_player);
	virtual void Process() override;
};

class RpcReportPlayer : public RPCInterface {
	PlayerControl* reportingPlayer;
	GameData_PlayerInfo* selectedPlayer;
public:
	RpcReportPlayer(PlayerControl* reporting_player, GameData_PlayerInfo* selected_player);
	virtual void Process() override;
};
