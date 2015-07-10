#include "PlayState.h"
#include "LoseState.h"
#include "PauseState.h"
#include "Game.h"
#include <SDL.h>
#include <string>

void PlayState::handleInput()
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
				//Move the grid's Squares in the direction corresponding to 
				//whichever arrow key is pressed
				case SDLK_UP:
					TheGame::getInstance()->move(UP);
					break;

				case SDLK_DOWN:
					TheGame::getInstance()->move(DOWN);
					break;

				case SDLK_LEFT:
					TheGame::getInstance()->move(LEFT);
					break;

				case SDLK_RIGHT:
					TheGame::getInstance()->move(RIGHT);
					break;
				//Pressing escape brings up the Pause menu (state)
				case SDLK_ESCAPE:
					PauseState* pause = new PauseState;
					gameStates->push(pause);
					break;
			}
		}
	}
}

void PlayState::runState()
{
	if (SDL_GetTicks() - TheGame::getInstance()->getTimer() >= FRAME_RATE)
	{
		handleInput();

		TheGame::getInstance()->clearScreen();

		TheGame::getInstance()->drawGrid();

		SDL_UpdateWindowSurface(TheGame::getInstance()->getWindow());


		//If no further moves can be made, game over
		if (!TheGame::getInstance()->canMove())
		{
			TheGame::getInstance()->clearGrid();

			TheGame::getInstance()->getGameStates()->pop();

			LoseState* lose = new LoseState;
			TheGame::getInstance()->getGameStates()->push(lose);
		}

		TheGame::getInstance()->setTimer(SDL_GetTicks());
	}
	

}