#include "stdafx.h"
#include "Block.h"



Block::Block()
{
	//wybieranie losowego kszta�tu dla bloku
	shapeNumber = randomShapeNumber();
	//przpeisanie tablicy ze wsp�rz�dymi kszta�tu na tablic� na ktorej b�dziemy operowa�
	setShape(shapeNumber, shapeTable);
	// moze rozpoczac si� porusza�
	isMovable = 1;
	// rotacja = 0 
	rotationPos = 0;
}


Block::~Block()
{
}

int Block::randomShapeNumber()
{
	int random = (rand() % 7);
	return random;
}

void Block::setShape(int shapeNumber, int table[][4][2])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			shapeCoords[i][j] = table[shapeNumber][i][j];
}