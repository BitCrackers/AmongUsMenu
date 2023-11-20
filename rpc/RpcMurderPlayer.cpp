#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerControl* Player, PlayerControl* target)
{
	this->Player = Player;
	this->target = target;
}

void RpcMurderPlayer::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_RpcMurderPlayer(Player, target, true, NULL);
}

//damn im too lazy to add new files

RpcShapeshift::RpcShapeshift(PlayerControl* Player, const PlayerSelection& target, bool animate)
{
	this->Player = Player;
	this->target = target;
	this->animate = animate;
}

void RpcShapeshift::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_RpcShapeshift(Player, target.get_PlayerControl().value_or(nullptr), animate,  NULL);
}

CmdCheckShapeshift::CmdCheckShapeshift(PlayerControl* Player, const PlayerSelection& target, bool animate)
{
	this->Player = Player;
	this->target = target;
	this->animate = animate;
}

void CmdCheckShapeshift::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;

	PlayerControl_CmdCheckShapeshift(Player, target.get_PlayerControl().value_or(nullptr), animate, NULL);
}

RpcSendChat::RpcSendChat(PlayerControl* Player, std::string_view msg)
{
	this->Player = Player;
	this->msg = msg;
}

void RpcSendChat::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_RpcSendChat(Player, convert_to_string(msg), NULL);
}

RpcVotePlayer::RpcVotePlayer(PlayerControl* Player, PlayerControl* target, bool skip)
{
	this->Player = Player;
	this->target = target;
	this->skip = skip;
}

void RpcVotePlayer::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	if (skip)
		MeetingHud_CmdCastVote(MeetingHud__TypeInfo->static_fields->Instance, Player->fields.PlayerId, 253, NULL);
	else
		MeetingHud_CmdCastVote(MeetingHud__TypeInfo->static_fields->Instance, Player->fields.PlayerId, target->fields.PlayerId, NULL);
}

RpcVoteKick::RpcVoteKick(PlayerControl* target)
{
	this->target = target;
}

void RpcVoteKick::Process()
{
	if (!PlayerSelection(target).has_value())
		return;
	
	VoteBanSystem_CmdAddVote(VoteBanSystem__TypeInfo->static_fields->Instance, target->fields._.OwnerId, NULL);
}

RpcClearVote::RpcClearVote(PlayerControl* Player)
{
	this->Player = Player;
}

void RpcClearVote::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	MeetingHud_RpcClearVote(MeetingHud__TypeInfo->static_fields->Instance, Player->fields._.OwnerId, NULL);
}

RpcEndMeeting::RpcEndMeeting(){

}

void RpcEndMeeting::Process()
{
	MeetingHud_RpcClose(MeetingHud__TypeInfo->static_fields->Instance, NULL);
}

EndMeeting::EndMeeting() {

}

void EndMeeting::Process()
{
	MeetingHud_Close(MeetingHud__TypeInfo->static_fields->Instance, NULL);
}

DestroyMap::DestroyMap() {

}

void DestroyMap::Process()
{
	ShipStatus_OnDestroy(ShipStatus__TypeInfo->static_fields->Instance, NULL);
}

RpcRevive::RpcRevive(PlayerControl* Player)
{
	this->Player = Player;
}

void RpcRevive::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_Revive(Player, NULL);
}

RpcVent::RpcVent(PlayerControl* Player, int32_t ventId, bool exit)
{
	this->Player = Player;
	this->ventId = ventId;
	this->exit = exit;
}

void RpcVent::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	if (exit)
		PlayerPhysics_RpcExitVent(Player->fields.MyPhysics, ventId, NULL);
	else
		PlayerPhysics_RpcEnterVent(Player->fields.MyPhysics, ventId, NULL);
}

RpcBootFromVent::RpcBootFromVent(int32_t ventId)
{
	this->ventId = ventId;
}

void RpcBootFromVent::Process()
{	
	VentilationSystem_Update(VentilationSystem_Operation__Enum::BootImpostors, ventId, NULL);
}

RpcSetLevel::RpcSetLevel(PlayerControl* Player, int level)
{
	this->Player = Player;
	this->level = level;
}

void RpcSetLevel::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_RpcSetLevel(Player, level, NULL);
}

RpcEndGame::RpcEndGame(GameOverReason__Enum reason)
{
	this->reason = reason;
}

void RpcEndGame::Process()
{
	GameManager_RpcEndGame(GameManager__TypeInfo->static_fields->_Instance_k__BackingField, reason, false, NULL);
}

RpcProtectPlayer::RpcProtectPlayer(PlayerControl* Player, PlayerSelection target, uint8_t color)
{
	this->Player = Player;
	this->target = target;
	this->color = color;
}

void RpcProtectPlayer::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_RpcProtectPlayer(Player, target.get_PlayerControl().value_or(nullptr), color, NULL);
}

CmdCheckProtect::CmdCheckProtect(PlayerControl* Player, PlayerSelection target)
{
	this->Player = Player;
	this->target = target;
}

void CmdCheckProtect::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;
	
	PlayerControl_CmdCheckProtect(Player, target.get_PlayerControl().value_or(nullptr), NULL);
}