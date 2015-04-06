#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <SDL.h>

class MenuState : public GameState
{
public:

	void HandleInput();

	void RunState();

private:

	SDL_Event event;

};
#endif