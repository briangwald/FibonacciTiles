#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"

void MenuState::HandleInput()
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

			case SDLK_q:
				gameStates->pop();
				break;

			case SDLK_g:
				gameStates->pop();

				TheGame::Instance()->AddRandomSquare();
				TheGame::Instance()->AddRandomSquare();

				PlayState* play = new PlayState;
				gameStates->push(play);
				break;
			}
			return;
		}
	}
}

void MenuState::RunState()
{
	if (SDL_GetTicks() - TheGame::Instance()->GetTimer() >= FRAME_RATE)
	{
		HandleInput();

		TheGame::Instance()->ClearScreen();

		TheGame::Instance()->DisplayText("Start (G)ame", 175, 150, 12, 255, 255, 255, 0, 0, 0);
		TheGame::Instance()->DisplayText("(Q)uit Game", 175, 200, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateWindowSurface(TheGame::Instance()->GetWindow());

		TheGame::Instance()->SetTimer(SDL_GetTicks());
	}
}