#ifndef SQUARE_H
#define SQUARE_H

#include <SDL.h>

#define GRID_ROWS (4)
#define GRID_COLS (4)
#define CELLS_PER_ROW (4)
#define CELLS_PER_COL (4)

//The objects that are stored within Game's 2d vector, grid.
class Square
{
public:

	Square(int topLeftX, int topLeftY, int value);

	void Draw(SDL_Surface* screenSurface, SDL_Surface* spriteSheet);

	int GetValue() { return value; }
	void SetValue(int val) { value = val; }

private:

	//X position on the screen
	int topLeftX;

	//Y position on the screen
	int topLeftY;

	//Fibonacci number represented by the Square
	int value;


};
#endif