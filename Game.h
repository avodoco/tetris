#pragma once
#include "board.h"
#include "block.h"
#include "Windows.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Game
{
public:
	Game();
	~Game();
	void addingBlockToBoard(Block &block, int xPos, int yPos);
	void addingNewBlock(void);
	void checkLines(void);
	void tryMove(Block &block);
	bool checkingForCollisions(Block &block, int rectNumb);
	void removingLine(int removedLineNum);
	void showBoard(Board &board);
	void ifKeyPressed(Board &board);
	void showScore(void);
	void update(void);
	void endGame(void);
	friend class Block;
	friend class Board;
private:
	int score;
	int timeInterval;
	int removedLineNum;
	int isPaused;
	int isGameEnded;
	Board * board = new Board();
	Block *currentBlock;
	int currentX, currentY;
};

