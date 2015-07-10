#include "LoseState.h"
#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void LoseState::handleInput()
{
	if (SDL_PollEvent(&event))
	{
		stack<GameState*>* gameStates = TheGame::getInstance()->getGameStates();

		if (event.type == SDL_QUIT)
		{
			while (!gameStates->empty())
			{
				gameStates->pop();
			}
			return;
		}
		if (event.type == SDL_KEYDOWN)
		{
			//Pressing Esc or Y will bring up the Exit menu/state
			if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_y)
			{
				gameStates->pop();
				return;
			}
			//Pressing N will return you to the main menu/state
			if (event.key.keysym.sym == SDLK_n)
			{
				gameStates->pop();

				ExitState* exit = new ExitState;
				gameStates->push(exit);

				MenuState* menu = new MenuState;
				gameStates->push(menu);
				return;
			}
		}
	}
}

void LoseState::runState()
{
	if (SDL_GetTicks() - TheGame::getInstance()->getTimer() >= FRAME_RATE)
	{

		TheGame::getInstance()->clearScreen();

		TheGame::getInstance()->displayText("Game Over!", 100, 120, 12, 255, 255, 255, 0, 0, 0);
		TheGame::getInstance()->displayText("Quit Game (Y or N)?", 100, 140, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::getInstance()->getWindow());

		TheGame::getInstance()->setTimer(SDL_GetTicks());

		handleInput();
	}
}