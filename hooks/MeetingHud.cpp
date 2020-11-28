#include "_hooks.hpp"

using namespace app;

void dMeetingHud_Awake(MeetingHud* __this, MethodInfo* method) {
	for (auto playerData : GetAllPlayerData())
		State.voteMonitor[playerData->fields.PlayerId] = false;

	MeetingHud_Awake(__this, method);
}

void dMeetingHud_Close(MeetingHud* __this, MethodInfo* method) {
	State.voteMonitor.clear();

	MeetingHud_Close(__this, method);
}

void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method) {
	PlayerVoteArea__Array* playerStates = __this->fields.playerStates;
	for (size_t i = 0; i < playerStates->max_length; i++) {
		PlayerVoteArea* playerVoteArea = playerStates->vector[i];
		auto playerData = GetPlayerDataById(playerVoteArea->fields._TargetPlayerId_k__BackingField);
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		if (playerData && localData) {
			if (State.RevealImpostors || localData->fields.IsImpostor)
				playerVoteArea->fields.NameText->fields.Color = playerData->fields.IsImpostor
				? Palette__TypeInfo->static_fields->ImpostorRed
				: Palette__TypeInfo->static_fields->White;
			else
				playerVoteArea->fields.NameText->fields.Color = Palette__TypeInfo->static_fields->White;
		}

		if (__this->fields.state == MeetingHud_VoteStates__Enum_NotVoted || __this->fields.state == MeetingHud_VoteStates__Enum_Voted) {
			if (!playerData->fields.IsDead) {
				if (playerVoteArea->fields.didVote && !State.voteMonitor[playerData->fields.PlayerId]) {
					State.events.push_back(new CastVoteEvent(*GetEventPlayer(playerData), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.votedFor))));
					State.voteMonitor[playerData->fields.PlayerId] = true;
				}
			}
		}
	}
	MeetingHud_Update(__this, method);
}