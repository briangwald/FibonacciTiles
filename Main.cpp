#include "Game.h"
#include "GameState.h"

int main(int argc, char** argv)
{
	TheGame::Instance()->Init();

	//Game loop
	while (!TheGame::Instance()->GetGameStates()->empty())
	{

		TheGame::Instance()->GetGameStates()->top()->RunState();
	}

	TheGame::Instance()->Shutdown();

	return 0;
}