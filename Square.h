#ifndef SQUARE_H
#define SQUARE_H

#include <SDL.h>

#define GRID_ROWS (4)
#define GRID_COLS (4)
#define CELLS_PER_ROW (4)
#define CELLS_PER_COL (4)

class Square
{
public:

	Square(int topLeftX, int topLeftY, int value);

	void Draw(SDL_Surface* screenSurface, SDL_Surface* spriteSheet);

	int GetValue() { return value; }
	void SetValue(int val) { value = val; }

private:

	int topLeftX;
	int topLeftY;

	int value;

	SDL_Surface image;
};
#endif