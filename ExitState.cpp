#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void ExitState::handleInput()
{
	if (SDL_PollEvent(&event))
	{
		stack<GameState*>* gameStates = TheGame::getInstance()->getGameStates();

		//Pressing X on the window will exit the game entirely
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
			switch (event.key.keysym.sym)
			{
			//Pressing Esc will exit the game
			case SDLK_ESCAPE:
				gameStates->pop();
				break;
			//Pressing Y will exit game
			case SDLK_y:
				gameStates->pop();
				break;
			//Pressing N will bring you back to the menu
			case SDLK_n:
				MenuState* menu = new MenuState;
				gameStates->push(menu);
				break;
			}
		}
	}
}

void ExitState::runState()
{
	if (SDL_GetTicks() - TheGame::getInstance()->getTimer() >= FRAME_RATE)
	{
		handleInput();

		TheGame::getInstance()->clearScreen();

		TheGame::getInstance()->displayText("Quit Game (Y or N)?", 150, 150, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::getInstance()->getWindow());

		TheGame::getInstance()->setTimer(SDL_GetTicks());
	}
}