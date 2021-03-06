#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include <SDL.h>

//The "Gameplay" state where the actual game runs
class PlayState : public GameState
{
public:

	void handleInput();

	void runState();

private:

	SDL_Event event;
};
#endif