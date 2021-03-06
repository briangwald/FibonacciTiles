#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <SDL.h>

//The "Main Menu" state through which the game can be started or exited
class MenuState : public GameState
{
public:

	void handleInput();

	void runState();

private:

	SDL_Event event;

};
#endif