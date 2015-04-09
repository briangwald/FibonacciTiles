#include "ExitState.h"
#include "MenuState.h"
#include "Game.h"

void ExitState::HandleInput()
{
	if (SDL_PollEvent(&event))
	{
		stack<GameState*>* gameStates = TheGame::Instance()->GetGameStates();

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