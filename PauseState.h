#ifndef PAUSESTATE_H
#define PAUSETATE_H

#include "GameState.h"
#include <SDL.h>

class PauseState : public GameState
{
public:

	void HandleInput();

	void RunState();

private:

	SDL_Event event;

};

#endif