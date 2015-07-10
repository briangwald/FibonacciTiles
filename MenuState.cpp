#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"

void MenuState::handleInput()
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
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				gameStates->pop();
				break;

			case SDLK_q:
				gameStates->pop();
				break;

			case SDLK_g:
				gameStates->pop();

				TheGame::getInstance()->addRandomSquare();
				TheGame::getInstance()->addRandomSquare();

				PlayState* play = new PlayState;
				gameStates->push(play);
				break;
			}
			return;
		}
	}
}

void MenuState::runState()
{
	if (SDL_GetTicks() - TheGame::getInstance()->getTimer() >= FRAME_RATE)
	{
		handleInput();

		TheGame::getInstance()->clearScreen();

		TheGame::getInstance()->displayText("Start (G)ame", 175, 150, 12, 255, 255, 255, 0, 0, 0);
		TheGame::getInstance()->displayText("(Q)uit Game", 175, 200, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::getInstance()->getWindow());

		TheGame::getInstance()->setTimer(SDL_GetTicks());
	}
}