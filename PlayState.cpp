#include "PlayState.h"
#include "LoseState.h"
#include "PauseState.h"
#include "Game.h"
#include <SDL.h>
#include <string>

void PlayState::HandleInput()
{
	if (SDL_PollEvent(&event))
	{
		stack<GameState*>* gameStates = TheGame::Instance()->GetGameStates();

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
				

				case SDLK_UP:
					TheGame::Instance()->Move(UP);
					break;

				case SDLK_DOWN:
					TheGame::Instance()->Move(DOWN);
					break;

				case SDLK_LEFT:
					TheGame::Instance()->Move(LEFT);
					break;

				case SDLK_RIGHT:
					TheGame::Instance()->Move(RIGHT);
					break;

				case SDLK_ESCAPE:
					PauseState* pause = new PauseState;
					gameStates->push(pause);
					break;
			}
		}
	}
}

void PlayState::RunState()
{
	if (SDL_GetTicks() - TheGame::Instance()->GetTimer() >= FRAME_RATE)
	{
		HandleInput();

		TheGame::Instance()->ClearScreen();

		TheGame::Instance()->DrawGrid();

		SDL_UpdateWindowSurface(TheGame::Instance()->GetWindow());


		//If no further moves can be made, game over
		if (!TheGame::Instance()->CanMove())
		{
			TheGame::Instance()->ClearGrid();

			TheGame::Instance()->GetGameStates()->pop();

			LoseState* lose = new LoseState;
			TheGame::Instance()->GetGameStates()->push(lose);
		}

		TheGame::Instance()->SetTimer(SDL_GetTicks());
	}
	

}