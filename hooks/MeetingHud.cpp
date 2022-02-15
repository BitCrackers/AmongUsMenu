#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include <chrono>

void dMeetingHud_Awake(MeetingHud* __this, MethodInfo* method) {
	State.voteMonitor.reset();
	State.InMeeting = true;
	State.RoundEnd = std::chrono::system_clock::now();

	MeetingHud_Awake(__this, method);
}

void dMeetingHud_Close(MeetingHud* __this, MethodInfo* method) {
	State.InMeeting = false;
	State.RoundStart = std::chrono::system_clock::now();

	if (State.Replay_ClearAfterMeeting)
	{
		Replay::Reset(true);
	}

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
			Color32 roleColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White, NULL);
			std::string playerName = convert_from_string(GetPlayerOutfit(playerData)->fields._playerName);
			if (State.RevealRoles)
			{
				std::string roleName = GetRoleName(playerData->fields.Role, State.AbbreviatedRoleNames);
				playerName += "\n<size=50%>(" + roleName + ")";
				roleColor = app::Color32_op_Implicit(GetRoleColor(playerData->fields.Role), NULL);
			}
			else if (PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
			{
				roleColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->ImpostorRed, NULL);
			}

			String* playerNameStr = convert_to_string(playerName);
			app::TMP_Text_set_text((app::TMP_Text*)playerNameTMP, playerNameStr, NULL);
			app::TextMeshPro_SetFaceColor(playerNameTMP, roleColor, NULL);
			app::TextMeshPro_SetOutlineColor(playerNameTMP, faceColor, NULL);
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
			if (isVotingState && didVote && playerVoteArea->fields.VotedFor != -2 && !State.voteMonitor[playerData->fields.PlayerId])
			{
				State.rawEvents.push_back(std::make_unique<CastVoteEvent>(GetEventPlayer(playerData).value(), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
				State.liveReplayEvents.push_back(std::make_unique<CastVoteEvent>(GetEventPlayer(playerData).value(), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
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