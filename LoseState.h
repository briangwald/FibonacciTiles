#ifndef LOSESTATE_H
#define LOSESTATE_H

#include "GameState.h"
#include <SDL.h>

//The "Game Over" State, which runs when no further moves can be made
class LoseState : public GameState
{
public:

	void handleInput();

	void runState();

private:
	
	//Input event
	SDL_Event event;

};

#endif