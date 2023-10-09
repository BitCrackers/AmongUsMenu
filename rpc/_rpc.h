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

class RpcForceSnapTo : public RPCInterface {
	PlayerControl* Player;
	Vector2 targetVector;
public:
	RpcForceSnapTo(PlayerControl* Player, Vector2 targetVector);
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

class RpcRevive : public RPCInterface {
	PlayerControl* Player;
public:
	RpcRevive(PlayerControl* Player);
	virtual void Process() override;
};

class RpcVent : public RPCInterface {
	PlayerControl* Player;
	int32_t ventId;
	bool exit; //Uses RpcSetColor, only can use as host
public:
	RpcVent(PlayerControl* Player, int32_t ventId, bool exit);
	virtual void Process() override;
};

class RpcSetLevel : public RPCInterface {
	PlayerControl* Player;
	int level;
public:
	RpcSetLevel(PlayerControl* Player, int level);
	virtual void Process() override;
};

class RpcEndGame : public RPCInterface {
	GameOverReason__Enum reason;
public:
	RpcEndGame(GameOverReason__Enum reason);
	virtual void Process() override;
};

class RpcProtectPlayer : public RPCInterface {
	PlayerControl* Player;
	PlayerSelection target;
	uint8_t color;
public:
	RpcProtectPlayer(PlayerControl* Player,	PlayerSelection target, uint8_t color);
	virtual void Process() override;
};

class CmdCheckProtect : public RPCInterface {
	PlayerControl* Player;
	PlayerSelection target;
public:
	CmdCheckProtect(PlayerControl* Player, PlayerSelection target);
	virtual void Process() override;
};

class RpcCompleteTask : public RPCInterface {
	uint32_t taskId;
public:
	RpcCompleteTask(uint32_t taskId);
	virtual void Process() override;
};

class RpcForceCompleteTask : public RPCInterface {
	PlayerControl* Player;
	uint32_t taskId;
public:
	RpcForceCompleteTask(PlayerControl* Player, uint32_t taskId);
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

class RpcForceScanner : public RPCInterface {
	PlayerControl* Player;
	bool playAnimation;
public:
	RpcForceScanner(PlayerControl* Player, bool playAnimation);
	virtual void Process() override;
};

class RpcReportPlayer : public RPCInterface {
	PlayerSelection reportedPlayer;
public:
	RpcReportPlayer(const PlayerSelection& target);
	virtual void Process() override;
};

class RpcForceReportPlayer : public RPCInterface {
	PlayerControl* Player;
	PlayerSelection reportedPlayer;
public:
	RpcForceReportPlayer(PlayerControl* Player, const PlayerSelection& target);
	virtual void Process() override;
};

class RpcForceMeeting : public RPCInterface {
	PlayerControl* Player;
	PlayerSelection reportedPlayer;
public:
	RpcForceMeeting(PlayerControl* Player, const PlayerSelection& target);
	virtual void Process() override;
};

class CmdCheckMurder : public RPCInterface {
	PlayerSelection target;
public:
	CmdCheckMurder(const PlayerSelection& target);
	virtual void Process() override;
};

class RpcMurderPlayer : public RPCInterface {
	PlayerControl* Player;
	PlayerControl* target;
public:
	RpcMurderPlayer(PlayerControl* Player, PlayerControl* target);
	virtual void Process() override;
};

class RpcShapeshift : public RPCInterface {
	PlayerControl* Player;
	PlayerSelection target;
	bool animate;
public:
	RpcShapeshift(PlayerControl* Player, const PlayerSelection& target, bool animate);
	virtual void Process() override;
};

class RpcSendChat : public RPCInterface {
	PlayerControl* Player;
	std::string msg;
public:
	RpcSendChat(PlayerControl* Player, std::string_view msg);
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

class RpcVotePlayer : public RPCInterface {
	PlayerControl* Player;
	PlayerControl* target;
	bool skip;
public:
	RpcVotePlayer(PlayerControl* Player, PlayerControl* target, bool skip = false);
	virtual void Process() override;
};

class RpcVoteKick : public RPCInterface {
	PlayerControl* target;
public:
	RpcVoteKick(PlayerControl* target);
	virtual void Process() override;
};

class RpcClearVote : public RPCInterface {
	PlayerControl* Player;
public:
	RpcClearVote(PlayerControl* Player);
	virtual void Process() override;
};

class RpcEndMeeting : public RPCInterface {
public:
	RpcEndMeeting();
	virtual void Process() override;
};

class EndMeeting : public RPCInterface {
public:
	EndMeeting();
	virtual void Process() override;
};

class DestroyMap : public RPCInterface {
public:
	DestroyMap();
	virtual void Process() override;
};

class RpcSetColor : public RPCInterface {
	uint8_t bodyColor;
	bool forceColor; //Uses RpcSetColor, only can use as host
public:
	RpcSetColor(uint8_t colorId, bool force=false);
	virtual void Process() override;
};

class RpcForceColor : public RPCInterface {
	PlayerControl* Player;
	uint8_t bodyColor;
	bool forceColor;
public:
	RpcForceColor(PlayerControl* player, uint8_t colorId, bool force = false);
	virtual void Process() override;
};

class RpcSetName : public RPCInterface {
	std::string name;
public:
	RpcSetName(std::string_view name);
	virtual void Process() override;
};

class RpcForceName : public RPCInterface {
	PlayerControl* Player;
	std::string name;
public:
	RpcForceName(PlayerControl* player, std::string_view name);
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

class RpcForcePet : public RPCInterface {
	PlayerControl* Player;
	String* PetId;
public:
	RpcForcePet(PlayerControl* Player, String* petId);
	virtual void Process() override;
};

class RpcSetSkin : public RPCInterface {
	String* SkinId;
public:
	RpcSetSkin(String* skinId);
	virtual void Process() override;
};

class RpcForceSkin : public RPCInterface {
	PlayerControl* Player;
	String* SkinId;
public:
	RpcForceSkin(PlayerControl* Player, String* skinId);
	virtual void Process() override;
};

class RpcSetHat : public RPCInterface {
	String* HatId;
public:
	RpcSetHat(String* hatId);
	virtual void Process() override;
};

class RpcForceHat : public RPCInterface {
	PlayerControl* Player;
	String* HatId;
public:
	RpcForceHat(PlayerControl* Player, String* hatId);
	virtual void Process() override;
};

class RpcSetVisor : public RPCInterface {
	String* VisorId;
public:
	RpcSetVisor(String* visorId);
	virtual void Process() override;
};

class RpcForceVisor : public RPCInterface {
	PlayerControl* Player;
	String* VisorId;
public:
	RpcForceVisor(PlayerControl* Player, String* visorId);
	virtual void Process() override;
};

class RpcSetNamePlate : public RPCInterface {
	String* NamePlateId;
public:
	RpcSetNamePlate(String* namePlateId);
	virtual void Process() override;
};

class RpcForceNamePlate : public RPCInterface {
	PlayerControl* Player;
	String* NamePlateId;
public:
	RpcForceNamePlate(PlayerControl* Player, String* namePlateId);
	virtual void Process() override;
};

class RpcSetRole : public RPCInterface {
	PlayerControl* Player;
	RoleTypes__Enum Role;
public:
	RpcSetRole(PlayerControl* player, RoleTypes__Enum role);
	virtual void Process() override;
};

class SetRole : public RPCInterface {
	RoleTypes__Enum Role;
public:
	SetRole(RoleTypes__Enum role);
	virtual void Process() override;
};