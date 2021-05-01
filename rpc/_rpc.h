#pragma once
#include "utility.h"

void HandleRpc(uint8_t callId, MessageReader* reader);

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

class RpcPlayAnimation : public RPCInterface {
	uint8_t animId;
public:
	RpcPlayAnimation(uint8_t taskId);
	virtual void Process() override;
};

class RpcSetScanner : public RPCInterface {
	bool playAnimation;
public:
	RpcSetScanner(bool playAnimation);
	virtual void Process() override;
};

class RpcReportPlayer : public RPCInterface {
	PlayerSelection reportedPlayer;
public:
	RpcReportPlayer(PlayerSelection target);
	virtual void Process() override;
};

class RpcMurderPlayer : public RPCInterface {
	PlayerSelection target;
public:
	RpcMurderPlayer(PlayerSelection target);
	virtual void Process() override;
};

class RpcSetColor : public RPCInterface {
	uint8_t bodyColor;
	bool forceColor; //Uses RpcSetColor, only can use as host
public:
	RpcSetColor(uint8_t colorId, bool force=false);
	virtual void Process() override;
};

class RpcSetName : public RPCInterface {
	std::string name;
public:
	RpcSetName(std::string name);
	virtual void Process() override;
};

class RpcUsePlatform : public RPCInterface {
public:
	RpcUsePlatform();
	virtual void Process() override;
};

class RpcSetPet : public RPCInterface {
	uint32_t PetId;
public:
	RpcSetPet(uint32_t petId);
	virtual void Process() override;
};

class RpcSetSkin : public RPCInterface {
	uint32_t SkinId;
public:
	RpcSetSkin(uint32_t skinId);
	virtual void Process() override;
};

class RpcSetHat : public RPCInterface {
	uint32_t HatId;
public:
	RpcSetHat(uint32_t hatId);
	virtual void Process() override;
};