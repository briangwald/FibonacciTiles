#ifndef GAME_H
#define GAME_H

#include <string>
#include <stack>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "GameState.h"
#include "Square.h"

#define FRAME_RATE (60)

//Corresponds to the Arrow Keys pressed during the game
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

using namespace std;

class PlayState;
class ExitState;
class WinState;
class LoseState;
class MenuState;
class Square;

class Game
{
public:
	Game();
	~Game();

	//Ensure singleton instance
	static Game* getInstance()
	{
		if (instance == NULL)
		{
			instance = new Game();
		}
		return instance;
	}

	//Initialize SDL utilities, window, sprites, and game state stack
	void init();

	//Ends SDL utilities
	void shutdown();

	//SDL functions
	void clearScreen();
	void displayText(string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB);

	//Returns true if a valid move can be made
	bool canMove();

	//Moves grid's squares in the given direction
	void move(Direction dir);

	//Draws each individual square in Grid
	void drawGrid();

	void clearGrid();

	//Sets the value of a random Square on the grid to either a 1 or a 2, effectively
	//adding a new Square to the grid.
	void addRandomSquare();

	SDL_Surface* getScreenSurface() { return screenSurface; }
	SDL_Window* getWindow() { return window; }

	int getTimer() { return timer; }
	void setTimer(int newTimer) 
	{ 
		timer = newTimer; 
	}

	//TODO: Instead of an accessor, provide methods that operate on
	//the GameStates stack directly
	stack<GameState*>* getGameStates() { return &gameStates; }

private:

	//Singleton instance
	static Game* instance;

	//TODO: Implement scoring
	int score;
	
	//Surface on which graphics are to be displayed
	SDL_Surface* screenSurface;

	//Game window
	SDL_Window* window;

	//Timer used for framerate
	int timer;

	//Sprite image for each Square value
	SDL_Surface* spriteSheet;

	//Top of the stack is the current game state to be run
	stack<GameState*> gameStates;

	//2D vector holding each Square
	vector<vector<Square*> > grid;

};

typedef Game TheGame;

#endif
