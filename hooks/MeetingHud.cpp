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
			if (State.RevealRoles || PlayerIsImpostor(localData)) {

				Color32 c = app::Color32_op_Implicit(GetRoleColor(playerData->fields.Role), NULL);

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
	}
	
	MeetingHud_Update(__this, method);
}