#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void ExitState::HandleInput()
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
			case SDLK_ESCAPE:
				gameStates->pop();
				break;

			case SDLK_y:
				gameStates->pop();
				break;

			case SDLK_n:
				MenuState* menu = new MenuState;
				gameStates->push(menu);
				break;
			}
		}
	}
}

void ExitState::RunState()
{
	if (SDL_GetTicks() - TheGame::Instance()->GetTimer() >= FRAME_RATE)
	{
		HandleInput();

		TheGame::Instance()->ClearScreen();

		TheGame::Instance()->DisplayText("Quit Game (Y or N)?", 150, 150, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::Instance()->GetWindow());

		TheGame::Instance()->SetTimer(SDL_GetTicks());
	}
}