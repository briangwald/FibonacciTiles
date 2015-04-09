#ifndef GAMESTATE_H
#define GAMESTATE_H

//Interface for the game states
class GameState
{
public:

	virtual void HandleInput() = 0;

	virtual void RunState() = 0;
};

#endif