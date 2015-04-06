#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <SDL.h>

class PlayState : public GameState
{
public:

	void HandleInput();

	void RunState();

private:

	SDL_Event event;
};
#endif