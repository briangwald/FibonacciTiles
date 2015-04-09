#include "Square.h"
#include "Game.h"

#include <SDL.h>
#include <iostream>
#include <math.h>

Square::Square(int topLeftX, int topLeftY, int value) :
topLeftX(topLeftX),
topLeftY(topLeftY),
value(value)
{
}

void Square::Draw(SDL_Surface* screenSurface, SDL_Surface* spriteSheet)
{
	SDL_Rect source;

	//Use the appropriate "square" from the sprite image for each Fib value
	switch (value)
	{
	case 1:
		source = { 0, 0, 50, 50 };
		break;

	case 2:
		source = { 50, 0, 50, 50 };
		break;

	case 3:
		source = { 100, 0, 50, 50 };
		break;

	case 5:
		source = { 150, 0, 50, 50 };
		break;

	case 8:
		source = { 200, 0, 50, 50 };
		break;

	case 13:
		source = { 250, 0, 50, 50 };
		break;

	case 21:
		source = { 300, 0, 50, 50 };
		break;

	case 34:
		source = { 350, 0, 50, 50 };
		break;

	case 55:
		source = { 0, 50, 50, 50 };
		break;

	case 89:
		source = { 50, 50, 50, 50 };
		break;

	case 144:
		source = { 100, 50, 50, 50 };
		break;

	case 233:
		source = { 150, 50, 50, 50 };
		break;

	case 377:
		source = { 200, 50, 50, 50 };
		break;

	case 610:
		source = { 250, 50, 50, 50 };
		break;

	case 987:
		source = { 300, 50, 50, 50 };
		break;

	case 1597:
		source = { 300, 50, 50, 50 };
		break;
	}
	SDL_Rect destination = { topLeftX, topLeftY, 50, 50 };

	SDL_BlitSurface(spriteSheet, &source, screenSurface, &destination);
}
