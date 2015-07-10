#include "Game.h"
#include "GameState.h"

int main(int argc, char** argv)
{
	TheGame::getInstance()->init();

	//Game loop
	while (!TheGame::getInstance()->getGameStates()->empty())
	{

		TheGame::getInstance()->getGameStates()->top()->runState();
	}

	TheGame::getInstance()->shutdown();

	return 0;
}