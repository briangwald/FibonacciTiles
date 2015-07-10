#ifndef PAUSESTATE_H
#define PAUSETATE_H

#include "GameState.h"
#include <SDL.h>

//The "Pause Menu" state that runs when the user presses "Esc" through
//which they may resume the game or restart it
class PauseState : public GameState
{
public:

	void handleInput();

	void runState();

private:

	SDL_Event event;

};

#endif