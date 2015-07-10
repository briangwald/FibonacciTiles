#ifndef GAMESTATE_H
#define GAMESTATE_H

//Interface for the game states
class GameState
{
public:

	virtual void handleInput() = 0;

	virtual void runState() = 0;
};

#endif