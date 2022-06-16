#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"
#include "logger.h"

void HandleRpc(uint8_t callId, MessageReader* reader) {
	switch (callId) {
	case (uint8_t)42069:
		int32_t playerid = MessageReader_ReadInt32(reader, NULL);
		if (!std::count(State.aumUsers.begin(), State.aumUsers.end(), playerid)) {
			State.aumUsers.push_back(playerid);
			STREAM_DEBUG("RPC Received for another AUM User from " << ToString((Game::PlayerId)playerid));
		}
		break;
	}
}