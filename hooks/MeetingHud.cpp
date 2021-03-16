#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"

void dMeetingHud_Awake(MeetingHud* __this, MethodInfo* method) {
	State.voteMonitor.reset();
	State.InMeeting = true;

	MeetingHud_Awake(__this, method);
}

void dMeetingHud_Close(MeetingHud* __this, MethodInfo* method) {
	State.InMeeting = false;

	MeetingHud_Close(__this, method);
}

void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method) {
	PlayerVoteArea__Array* playerStates = __this->fields.playerStates;
	for (size_t i = 0; i < playerStates->max_length; i++) {
		PlayerVoteArea* playerVoteArea = playerStates->vector[i];
		auto playerData = GetPlayerDataById(playerVoteArea->fields.TargetPlayerId);
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		if (playerData && localData) {
			if (State.RevealImpostors || localData->fields.IsImpostor)
				playerVoteArea->fields.NameText->fields.Color = playerData->fields.IsImpostor
				? Palette__TypeInfo->static_fields->ImpostorRed
				: Palette__TypeInfo->static_fields->White;
			else
				playerVoteArea->fields.NameText->fields.Color = Palette__TypeInfo->static_fields->White;
		}

		// We are goign to check to see if they voted, then we are going to check to see who they voted for, finally we are going to check to see if we already recorded a vote for them
		// votedFor will either contain the id of the person they voted for, -1 if they skipped, or -2 if they didn't vote. We don't want to record people who didn't vote
		if (playerVoteArea->fields.didVote && playerVoteArea->fields.votedFor != -2 && !State.voteMonitor[playerData->fields.PlayerId]) {
			State.events.push_back(new CastVoteEvent(*GetEventPlayer(playerData), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.votedFor))));
			State.voteMonitor[playerData->fields.PlayerId] = true;
		}
	}
	MeetingHud_Update(__this, method);
}