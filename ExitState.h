#ifndef EXITSTATE_H
#define EXITSTATE_H

#include "GameState.h"
#include <SDL.h>

class ExitState : public GameState
{
public:

	void HandleInput();

	void RunState();

private:

	SDL_Event event;

};
#endif