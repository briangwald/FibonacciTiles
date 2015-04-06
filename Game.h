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
	static Game* Instance()
	{
		if (instance == NULL)
		{
			instance = new Game();
		}
		return instance;
	}

	//Initialize singleton instance
	void Init();

	//cleanup
	void Shutdown();

	//SDL functions
	void DrawBackground();
	void ClearScreen();
	void DisplayText(string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB);

	void Win();
	void Lose();

	bool CanMove();

	void Move(Direction dir);

	void DrawGrid();
	void ClearGrid();

	void AddRandomSquare();

	//SDL Getters
	SDL_Surface* GetScreenSurface() { return screenSurface; }
	SDL_Window* GetWindow() { return window; }

	int GetTimer() { return timer; }
	void SetTimer(int newTimer) 
	{ 
		timer = newTimer; 
	}

	stack<GameState*>* GetGameStates() { return &gameStates; }

private:

	static Game* instance;

	int score;

	SDL_Surface* screenSurface;
	SDL_Window* window;

	int timer;

	SDL_Surface* spriteSheet;

	stack<GameState*> gameStates;

	vector<vector<Square*> > grid;

};

typedef Game TheGame;

#endif
