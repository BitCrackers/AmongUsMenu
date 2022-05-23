#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include <chrono>

static app::Type* voteSpreaderType;

void dMeetingHud_Awake(MeetingHud* __this, MethodInfo* method) {
	State.voteMonitor.clear();
	State.InMeeting = true;

	if (!voteSpreaderType) {
		voteSpreaderType = app::Type_GetType(convert_to_string(translate_type_name("VoteSpreader, Assembly-CSharp")), nullptr);
	}

	MeetingHud_Awake(__this, method);
}

void dMeetingHud_Close(MeetingHud* __this, MethodInfo* method) {
	State.InMeeting = false;

	if (State.Replay_ClearAfterMeeting)
	{
		Replay::Reset();
	}

	MeetingHud_Close(__this, method);
}

static void Transform_RemoveAllVotes(app::Transform* transform) {
	auto voteSpreader = (VoteSpreader*)app::Component_GetComponent((app::Component_1*)transform, voteSpreaderType, nullptr);
	if (!voteSpreader) return;
	auto votes = il2cpp::List(voteSpreader->fields.Votes);
	if (votes.size() == 0) return;
	for (auto spriteRenderer : votes) {
		app::Object_DestroyImmediate((app::Object_1*)spriteRenderer, nullptr);
	}
	votes.clear();
}

void dMeetingHud_PopulateResults(MeetingHud* __this, void* states, MethodInfo* method) {
	// remove all votes before populating results
	do {
		for (auto votedForArea : il2cpp::Array(__this->fields.playerStates)) {
			if (!votedForArea) {
				// oops: game bug
				continue;
			}
			auto transform = app::Component_get_transform((app::Component_1*)votedForArea, nullptr);
			Transform_RemoveAllVotes(transform);
		}
		if (__this->fields.SkippedVoting) {
			auto transform = app::GameObject_get_transform(__this->fields.SkippedVoting, nullptr);
			Transform_RemoveAllVotes(transform);
		}
	} while (false);

	MeetingHud_PopulateResults(__this, states, method);
}

void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method) {
	il2cpp::Array playerStates(__this->fields.playerStates);
	for (auto playerVoteArea : playerStates) {
		if (!playerVoteArea) {
			// oops: game bug
			continue;
		}
		auto playerData = GetPlayerDataById(playerVoteArea->fields.TargetPlayerId);
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		auto playerNameTMP = playerVoteArea->fields.NameText;
		app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);

		if (playerData && localData && outfit) {
			Color32 faceColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->Black, NULL);
			Color32 roleColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White, NULL);
			std::string playerName = convert_from_string(outfit->fields._playerName);
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

		if (playerData)
		{
			bool didVote = (playerVoteArea->fields.VotedFor != 0xFF);
			// We are goign to check to see if they voted, then we are going to check to see who they voted for, finally we are going to check to see if we already recorded a vote for them
			// votedFor will either contain the id of the person they voted for, -1 if they skipped, or -2 if they didn't vote. We don't want to record people who didn't vote
			if (isVotingState && didVote && playerVoteArea->fields.VotedFor != -2 && State.voteMonitor.find(playerData->fields.PlayerId) == State.voteMonitor.end())
			{
				std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
				State.rawEvents.push_back(std::make_unique<CastVoteEvent>(GetEventPlayer(playerData).value(), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
				State.liveReplayEvents.push_back(std::make_unique<CastVoteEvent>(GetEventPlayer(playerData).value(), GetEventPlayer(GetPlayerDataById(playerVoteArea->fields.VotedFor))));
				State.voteMonitor[playerData->fields.PlayerId] = playerVoteArea->fields.VotedFor;
				STREAM_DEBUG("Id " << +playerData->fields.PlayerId << " voted for " << +playerVoteArea->fields.VotedFor);

				// avoid duplicate votes
				if (__this->fields.state < app::MeetingHud_VoteStates__Enum::Results) {
					//auto isAnonymousVotes = (*Game::pGameOptionsData)->fields.AnonymousVotes;
					//(*Game::pGameOptionsData)->fields.AnonymousVotes = false;
					if (playerVoteArea->fields.VotedFor != 253) {
						for (auto votedForArea : playerStates) {
							if (votedForArea->fields.TargetPlayerId == playerVoteArea->fields.VotedFor) {
								auto transform = app::Component_get_transform((app::Component_1*)votedForArea, nullptr);
								MeetingHud_BloopAVoteIcon(__this, playerData, 0, transform, nullptr);
								break;
							}
						}
					}
					else if (__this->fields.SkippedVoting) {
						auto transform = app::GameObject_get_transform(__this->fields.SkippedVoting, nullptr);
						MeetingHud_BloopAVoteIcon(__this, playerData, 0, transform, nullptr);
					}
					//(*Game::pGameOptionsData)->fields.AnonymousVotes = isAnonymousVotes;
				}
			}
			else if (!didVote && State.voteMonitor.find(playerData->fields.PlayerId) != State.voteMonitor.end())
			{
				auto it = State.voteMonitor.find(playerData->fields.PlayerId);
				auto votedFor = it->second;
				State.voteMonitor.erase(it); //Likely disconnected player

				// Remove all votes for disconnected player 
				for (auto votedForArea : playerStates) {
					if (votedForArea->fields.TargetPlayerId == votedFor) {
						auto transform = app::Component_get_transform((app::Component_1*)votedForArea, nullptr);
						Transform_RemoveAllVotes(transform);
						break;
					}
				}
			}
		}
	}

	do {
		bool isVotingState = __this->fields.state == app::MeetingHud_VoteStates__Enum::NotVoted
			|| __this->fields.state == app::MeetingHud_VoteStates__Enum::Voted;
		if (!isVotingState) {
			break;
		}

		for (auto votedForArea : playerStates) {
			if (!votedForArea) {
				// oops: game bug
				continue;
			}
			auto transform = app::Component_get_transform((app::Component_1*)votedForArea, nullptr);
			auto voteSpreader = (VoteSpreader*)app::Component_GetComponent((app::Component_1*)transform, voteSpreaderType, nullptr);
			if (!voteSpreader) continue;
			for (auto spriteRenderer : il2cpp::List(voteSpreader->fields.Votes)) {
				auto gameObject = app::Component_get_gameObject((app::Component_1*)spriteRenderer, nullptr);
				app::GameObject_SetActive(gameObject, State.RevealVotes, nullptr);
			}
		}

		if (__this->fields.SkippedVoting) {
			bool showSkipped = false;
			for (const auto& pair : State.voteMonitor) {
				if (pair.second == 253) {
					showSkipped = State.RevealVotes;
					break;
				}
			}
			app::GameObject_SetActive(__this->fields.SkippedVoting, showSkipped, nullptr);
		}
	} while (false);
	MeetingHud_Update(__this, method);
}