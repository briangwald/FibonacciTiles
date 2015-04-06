#include "PauseState.h"
#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void PauseState::HandleInput()
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
			if (event.key.keysym.sym == SDLK_r)
			{
				gameStates->pop();
				TheGame::Instance()->ClearGrid();
				TheGame::Instance()->AddRandomSquare();
				TheGame::Instance()->AddRandomSquare();

				return;
			}
			if (event.key.keysym.sym == SDLK_m)
			{
				gameStates->pop();
				gameStates->pop();

				TheGame::Instance()->ClearGrid();

				ExitState* exit = new ExitState;
				gameStates->push(exit);

				MenuState* menu = new MenuState;
				gameStates->push(menu);
				return;
			}
		}
	}
}

void PauseState::RunState()
{
	if (SDL_GetTicks() - TheGame::Instance()->GetTimer() >= FRAME_RATE)
	{

		TheGame::Instance()->ClearScreen();

		TheGame::Instance()->DisplayText("Restart? (R)", 100, 120, 12, 255, 255, 255, 0, 0, 0);
		TheGame::Instance()->DisplayText("Main Menu? (M)", 100, 140, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::Instance()->GetWindow());

		TheGame::Instance()->SetTimer(SDL_GetTicks());

		HandleInput();
	}
}