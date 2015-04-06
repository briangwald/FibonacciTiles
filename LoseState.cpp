#include "LoseState.h"
#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void LoseState::HandleInput()
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
			if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_y)
			{
				gameStates->pop();
				return;
			}
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

void LoseState::RunState()
{
	if (SDL_GetTicks() - TheGame::Instance()->GetTimer() >= FRAME_RATE)
	{

		TheGame::Instance()->ClearScreen();

		TheGame::Instance()->DisplayText("Game Over!", 100, 120, 12, 255, 255, 255, 0, 0, 0);
		TheGame::Instance()->DisplayText("Quit Game (Y or N)?", 100, 140, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::Instance()->GetWindow());

		TheGame::Instance()->SetTimer(SDL_GetTicks());

		HandleInput();
	}
}