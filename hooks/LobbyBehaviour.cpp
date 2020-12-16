#include "_hooks.hpp"

using namespace app;

void dLobbyBehaviour_Start(LobbyBehaviour* __this, MethodInfo* method)
{
	State.LobbyTimer = 20;
	LobbyBehaviour_Start(__this, method);
}