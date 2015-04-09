#include "Game.h"
#include "ExitState.h"
#include "MenuState.h"
#include <iostream>
#include <ctime>



Game::Game()
{
	score = 0;

	screenSurface = NULL;
	window = NULL;

    //Allocate size for GRID_ROWS x CELLS_PER_ROW 2d vector
	grid.resize(GRID_ROWS);

	for (int i = 0; i < GRID_ROWS; i++)
	{
		grid[i].resize(CELLS_PER_ROW);
	}

	//Set x,y coordinates of the "Squares"
	int x = 70;
	int y = 70;

	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW; cell++)
		{
			grid[row][cell] = new Square(x, y, 0);
			//Squares are 50x50 pixels with 20 pixels of padding
			x += 70;
		}
		x = 70;
		y += 70;
	}
}


Game::~Game()
{
	//Deallocate memory allocated for each Square object
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW; cell++)
		{
			delete(grid[row][cell]);
		}
	}
}

//Initialize SDL functionality, window, assets, and game state vector
void Game::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("Fibonacci", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
	}

	spriteSheet = SDL_LoadBMP("Assets/Fibonacci.bmp");
	if (spriteSheet == NULL)
	{
		cout << "Failed to load bitmap" << endl;
	}

	screenSurface = SDL_GetWindowSurface(window);

	ExitState* exit = new ExitState;
	gameStates.push(exit);

	MenuState* menu = new MenuState;
	gameStates.push(menu);

	TTF_Init();
}

//Quits SDL Utilities
void Game::Shutdown()
{
	TTF_Quit();

	SDL_DestroyWindow(window);

	SDL_Quit();

}

//Clears the window to black
void Game::ClearScreen()
{
	SDL_FillRect(screenSurface, 0, 0);
}

void Game::DisplayText(string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB)
{
	TTF_Font* font = TTF_OpenFont("Assets/arial.ttf", size);

	SDL_Color foreground = { fR, fG, fB };
	SDL_Color background = { bR, bG, bB };

	SDL_Surface* tempSurface = TTF_RenderText_Shaded(font, text.c_str(), foreground, background);

	SDL_Rect destination = { x, y, 0, 0 };

	SDL_BlitSurface(tempSurface, NULL, screenSurface, &destination);

	SDL_FreeSurface(tempSurface);

	TTF_CloseFont(font);
}

//Helper function for isFibonacci to test for perfect squares
bool isPerfectSquare(int num)
{
	int temp = sqrt(num);
	return temp*temp == num;
}

//Tests a number to see if it's a valid Fibonacci number. 
bool isFibonacci(int num)
{
	return (isPerfectSquare(5 * (num*num) + 4) || isPerfectSquare(5 * (num*num) - 4));
}

//Test for possible valid moves
bool Game::CanMove()
{
	//Check for horizontal moves. Return early if a possible move is found
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW - 1; cell++)
		{
			int cellVal = grid[row][cell]->GetValue();
			int adjCellVal = grid[row][cell + 1]->GetValue();
			if (isFibonacci(cellVal + adjCellVal))
			{
				return true;
			}
		}
	}
	//Check for vertical moves. Return early if a possible move is found
	for (int col = 0; col < GRID_COLS; col++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW - 1; cell++)
		{
			int cellVal = grid[cell][col]->GetValue();
			int adjCellVal = grid[cell + 1][col]->GetValue();

			if (isFibonacci(cellVal + adjCellVal))
			{
				return true;
			}
		}
	}
	return false;
}

void Game::Move(Direction dir)
{
	bool successfullyMoved = false;

	switch (dir)
	{
	case UP:

		for (int col = 0; col < GRID_COLS; col++)
		{
			for (int cell = 0; cell < CELLS_PER_COL - 1; cell++)
			{
				int combinedVals = 0;

				//If current cell is 0, we need to check the next two nonzero numbers
				if (grid[cell][col]->GetValue() == 0)
				{
					int compCell = cell + 1;

					//Find the first nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_COL - 1) compCell++;
						else break;
					}

					//Store the number and set its location to 0
					combinedVals += grid[compCell][col]->GetValue();
					grid[compCell][col]->SetValue(0);

					//Find the next nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_COL - 1) compCell++;
						else break;
					}

					//Check if the two numbers combine to form a fibonacci number.
					//If they do, store the result and set this number's former location to
					//zero
					if (isFibonacci(combinedVals + grid[compCell][col]->GetValue()))
					{
						combinedVals += grid[compCell][col]->GetValue();
						grid[compCell][col]->SetValue(0);
					}

					//Store either that number or the first nonzero number we found, 
					//if the two did not add up to a fibnonaaci numer
					grid[cell][col]->SetValue(combinedVals);

					successfullyMoved = true;

				}
				//If current cell is nonzero, we only need to check for the next
				//nonzero number
				else
				{
					int compCell = cell + 1;

					//Find the next nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_COL - 1) compCell++;
						else break;
					}

					combinedVals += grid[compCell][col]->GetValue();

					//If both add up to a fibonacci number, set the current cell
					//to this number and the other to 0. If they do not, do nothing
					if (isFibonacci(combinedVals + grid[cell][col]->GetValue()))
					{
						combinedVals += grid[cell][col]->GetValue();
						grid[compCell][col]->SetValue(0);
						grid[cell][col]->SetValue(combinedVals);

						successfullyMoved = true;
					}
				}
			}
		}
		break;

	case DOWN:

		for (int col = 0; col < GRID_COLS; col++)
		{
			for (int cell = CELLS_PER_COL - 1; cell > 0; cell--)
			{
				int combinedVals = 0;

				//If current cell is 0, we need to check the next two nonzero numbers
				if (grid[cell][col]->GetValue() == 0)
				{
					int compCell = cell - 1;

					//Find the first nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					//Store the number and set its location to 0
					combinedVals += grid[compCell][col]->GetValue();
					grid[compCell][col]->SetValue(0);

					//Find the next nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					//Check if the two numbers combine to form a fibonacci number.
					//If they do, store the result and set this number's former location to
					//zero
					if (isFibonacci(combinedVals + grid[compCell][col]->GetValue()))
					{
						combinedVals += grid[compCell][col]->GetValue();
						grid[compCell][col]->SetValue(0);
					}

					//Store either that number or the first nonzero number we found, 
					//if the two did not add up to a fibnonaaci numer
					grid[cell][col]->SetValue(combinedVals);

					successfullyMoved = true;

				}
				//If current cell is nonzero, we only need to check for the next
				//nonzero number
				else
				{
					int compCell = cell - 1;

					//Find the next nonzero number down the column
					while (grid[compCell][col]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					combinedVals += grid[compCell][col]->GetValue();

					//If both add up to a fibonacci number, set the current cell
					//to this number and the other to 0. If they do not, do nothing
					if (isFibonacci(combinedVals + grid[cell][col]->GetValue()))
					{
						combinedVals += grid[cell][col]->GetValue();
						grid[compCell][col]->SetValue(0);
						grid[cell][col]->SetValue(combinedVals);

						successfullyMoved = true;
					}
				}
			}
		}
		break;

	case LEFT:

		for (int row = 0; row < GRID_ROWS; row++)
		{
			for (int cell = 0; cell < CELLS_PER_ROW - 1; cell++)
			{

				int combinedVals = 0;

				//If current cell is 0, we need to check the next two nonzero numbers
				if (grid[row][cell]->GetValue() == 0)
				{
					int compCell = cell + 1;

					//Find the first nonzero number down the row
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_ROW - 1) compCell++;
						else break;
					}

					//Store the number and set its location to 0
					combinedVals += grid[row][compCell]->GetValue();
					grid[row][compCell]->SetValue(0);

					//Find the next nonzero number down the row
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_ROW - 1) compCell++;
						else break;
					}

					//Check if the two numbers combine to form a fibonacci number.
					//If they do, store the result and set this number's former location to
					//zero
					if (isFibonacci(combinedVals + grid[row][compCell]->GetValue()))
					{
						combinedVals += grid[row][compCell]->GetValue();
						grid[row][compCell]->SetValue(0);
					}

					grid[row][cell]->SetValue(combinedVals);

					successfullyMoved = true;

				}

				//If current cell is nonzero, we only need to check for the next
				//nonzero number
				else
				{
					int compCell = cell + 1;

					//Find the next nonzero number down the row
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell < CELLS_PER_ROW - 1) compCell++;
						else break;
					}

					combinedVals += grid[row][compCell]->GetValue();

					//If both add up to a fibonacci number, set the current cell
					//to this number and the other to 0. If they do not, do nothing
					if (isFibonacci(combinedVals + grid[row][cell]->GetValue()))
					{
						combinedVals += grid[row][cell]->GetValue();
						grid[row][compCell]->SetValue(0);
						grid[row][cell]->SetValue(combinedVals);

						successfullyMoved = true;
					}
				}
			}
		}
		break;

	case RIGHT:

		cout << "After RIGHT shift:" << endl;

		for (int row = 0; row < GRID_ROWS; row++)
		{
			for (int cell = CELLS_PER_ROW - 1; cell > 0; cell--)
			{
				int combinedVals = 0;

				//If current cell is 0, we need to check the next two nonzero numbers
				if (grid[row][cell]->GetValue() == 0)
				{
					int compCell = cell - 1;

					//Find the first nonzero number down the column
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					//Store the number and set its location to 0
					combinedVals += grid[row][compCell]->GetValue();
					grid[row][compCell]->SetValue(0);

					//Find the next nonzero number down the column
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					//Check if the two numbers combine to form a fibonacci number.
					//If they do, store the result and set this number's former location to
					//zero
					if (isFibonacci(combinedVals + grid[row][compCell]->GetValue()))
					{
						combinedVals += grid[row][compCell]->GetValue();
						grid[row][compCell]->SetValue(0);
					}

					grid[row][cell]->SetValue(combinedVals);

					successfullyMoved = true;

				}

				//If current cell is nonzero, we only need to check for the next
				//nonzero number
				else
				{
					int compCell = cell - 1;

					//Find the next nonzero number down the row
					while (grid[row][compCell]->GetValue() == 0)
					{
						if (compCell > 0) compCell--;
						else break;
					}

					combinedVals += grid[row][compCell]->GetValue();

					//If both add up to a fibonacci number, set the current cell
					//to this number and the other to 0. If they do not, do nothing
					if (isFibonacci(combinedVals + grid[row][cell]->GetValue()))
					{
						combinedVals += grid[row][cell]->GetValue();
						grid[row][compCell]->SetValue(0);
						grid[row][cell]->SetValue(combinedVals);

						successfullyMoved = true;
					}
				}
			}
		}
		break;
	}

	//Only add an additional square to the grid once a valid move is made
	if (successfullyMoved)
	{
		AddRandomSquare();
	}
}

//Adds either a 1 or a 2 to a random grid cell after each move
void Game::AddRandomSquare()
{
	srand(time(0));

	int randVal = (rand() % 2) + 1;
	
	int randRow;
	int randCell;
	
	//Pick out a random cell until you find an empty one
	do
	{
		randRow = rand() % GRID_ROWS;
		randCell = rand() % CELLS_PER_ROW;
	} 
	while (grid[randRow][randCell]->GetValue() != 0);

	grid[randRow][randCell]->SetValue(randVal);
	
}

//Draw each square on the grid
void Game::DrawGrid()
{
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW; cell++)
		{
			grid[row][cell]->Draw(screenSurface, spriteSheet);
		}
	}
}

//Remove all squares from the grid by setting each val to 0
void Game::ClearGrid()
{
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int cell = 0; cell < CELLS_PER_ROW; cell++)
		{
			grid[row][cell]->SetValue(0);
		}
	}
}

Game* Game::instance = NULL;
