#include "stdafx.h"
#include "Board.h"


// stworzenie planszy do gry, wypełnionej samymi zerami 
Board::Board()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			boardBody[j][i] = 0;
		}
	}
}

Board::~Board()
{
}

