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
	RpcRepairSystem(SystemTypes__Enum selectedSystem, SystemTypes__Enum amount);
	RpcRepairSystem(SystemTypes__Enum selectedSystem, uint32_t amount);
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
	RpcReportPlayer(const PlayerSelection& target);
	virtual void Process() override;
};

class CmdCheckMurder : public RPCInterface {
	PlayerSelection target;
public:
	CmdCheckMurder(const PlayerSelection& target);
	virtual void Process() override;
};

class RpcMurderPlayer : public RPCInterface {
	PlayerSelection target;
public:
	RpcMurderPlayer(const PlayerSelection& target);
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
	RpcSetName(std::string_view name);
	virtual void Process() override;
};

class RpcSetNamePlate : public RPCInterface {
	String* NamePlateId;
public:
	RpcSetNamePlate(String* namePlateId);
	virtual void Process() override;
};

class RpcUsePlatform : public RPCInterface {
public:
	RpcUsePlatform();
	virtual void Process() override;
};

class RpcSetPet : public RPCInterface {
	String* PetId;
public:
	RpcSetPet(String* petId);
	virtual void Process() override;
};

class RpcSetSkin : public RPCInterface {
	String* SkinId;
public:
	RpcSetSkin(String* skinId);
	virtual void Process() override;
};

class RpcSetHat : public RPCInterface {
	String* HatId;
public:
	RpcSetHat(String* hatId);
	virtual void Process() override;
};

class RpcSetVisor : public RPCInterface {
	String* VisorId;
public:
	RpcSetVisor(String* visorId);
	virtual void Process() override;
};

class RpcSetRole : public RPCInterface {
	PlayerControl* Player;
	RoleTypes__Enum Role;
public:
	RpcSetRole(PlayerControl* player, RoleTypes__Enum role);
	virtual void Process() override;
};

class RpcChatMessage : public RPCInterface {
	std::string SenderName;
	std::string Message;
	uint32_t ColorId;
	std::chrono::system_clock::time_point Timestamp;
public:
	RpcChatMessage(std::string sendername, std::string message, uint32_t colorId, std::chrono::system_clock::time_point timestamp);
	virtual void Process() override;
	virtual void PrintUser();
	virtual void PrintMessage();
};