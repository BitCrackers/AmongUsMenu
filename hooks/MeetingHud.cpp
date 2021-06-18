#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"

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
		auto playerNameTMP = playerVoteArea->fields.NameText;


		if (playerData && localData) {
			Color32 faceColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->Black, NULL);
			if (State.RevealImpostors || localData->fields.IsImpostor) {
				Color32 c = app::Color32_op_Implicit(playerData->fields.IsImpostor
					? Palette__TypeInfo->static_fields->ImpostorRed
					: Palette__TypeInfo->static_fields->White, NULL);


				app::TextMeshPro_SetFaceColor(playerNameTMP, c, NULL);
				app::TextMeshPro_SetOutlineColor(playerNameTMP, faceColor, NULL);
			}
			else {
				Color32 c = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White, NULL);
				app::TextMeshPro_SetFaceColor(playerNameTMP, c, NULL);
				app::TextMeshPro_SetOutlineColor(playerNameTMP, faceColor, NULL);
			}
		}
		//This is to not show the "Force skip all" that a host does at the end of a meeting
		bool isDiscussionState = (__this->fields.discussionTimer < (*Game::pGameOptionsData)->fields.DiscussionTime);
		bool isVotingState = !isDiscussionState &&
							((__this->fields.discussionTimer - (*Game::pGameOptionsData)->fields.DiscussionTime) < (*Game::pGameOptionsData)->fields.VotingTime); //Voting phase

		if (playerVoteArea && playerData)
		{
			bool didVote = (playerVoteArea->fields.VotedFor != 0xFF);
			// We are goign to check to see if they voted, then we are going to check to see who they voted for, finally we are going to check to see if we already recorded a vote for them
			// votedFor will either contain the id of the person they voted for, -1 if they skipped, or -2 if they didn't vote. We don't want to record people who didn't vote
			if (isVotingState && didVote && playerVoteArea->fields.VotedFor != -2 && !State.voteMonitor[playerData->fields.PlayerId]) {
				State.events[playerVoteArea->fields.TargetPlayerId][EVENT_VOTE].push_back(new CastVoteEvent(*GetEventPlayer(playerData), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
				State.consoleEvents.push_back(new CastVoteEvent(*GetEventPlayer(playerData), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
				State.voteMonitor[playerData->fields.PlayerId] = true;
				STREAM_DEBUG("Id " << +playerData->fields.PlayerId << " voted for " << +playerVoteArea->fields.VotedFor);
			}
			else if (!didVote && State.voteMonitor[playerData->fields.PlayerId])
			{
				State.voteMonitor[playerData->fields.PlayerId] = false; //Likely disconnected player
			}
		}
	}
	
	MeetingHud_Update(__this, method);
}