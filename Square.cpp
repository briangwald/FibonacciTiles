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

	//TODO
	switch (value)
	{
	case 1:
		//TODO
		source = { 0, 0, 50, 50 };
		break;

	case 2:
		//TODO
		source = { 50, 0, 50, 50 };
		break;

	case 3:
		//TODO
		source = { 100, 0, 50, 50 };
		break;

	case 5:
		//TODO
		source = { 150, 0, 50, 50 };
		break;

	case 8:
		//TODO
		source = { 200, 0, 50, 50 };
		break;

	case 13:
		//TODO
		source = { 250, 0, 50, 50 };
		break;

	case 21:
		//TODO
		source = { 300, 0, 50, 50 };
		break;

	case 34:
		//TODO
		source = { 350, 0, 50, 50 };
		break;

	case 55:
		//TODO
		source = { 0, 50, 50, 50 };
		break;

	case 89:
		//TODO
		source = { 50, 50, 50, 50 };
		break;

	case 144:
		//TODO
		source = { 100, 50, 50, 50 };
		break;

	case 233:
		//TODO
		source = { 150, 50, 50, 50 };
		break;

	case 377:
		//TODO
		source = { 200, 50, 50, 50 };
		break;

	case 610:
		//TODO
		source = { 250, 50, 50, 50 };
		break;

	case 987:
		//TODO
		source = { 300, 50, 50, 50 };
		break;

	case 1597:
		//TODO
		source = { 300, 50, 50, 50 };
		break;
	}
	SDL_Rect destination = { topLeftX, topLeftY, 50, 50 };

	SDL_BlitSurface(spriteSheet, &source, screenSurface, &destination);
}
