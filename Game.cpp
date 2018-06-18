#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	srand(time(NULL));
	score = 0;
	isGameEnded = 0;
	timeInterval = 600;
	// dodanie pierwszego bloku
	addingNewBlock();
	showBoard(*board);
	while (!isGameEnded)
	{
		while (!isPaused)
		{
			update();
		}
		while (isPaused)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				isPaused = 0;
			}
		}
	}
}


Game::~Game()
{
}

void Game::addingBlockToBoard(Block &block, int xPos, int yPos)
{
	for (int i = 0; i<4; i++)
	{
		block.shapeCoords[i][0] = xPos + block.shapeCoords[i][0];
		block.shapeCoords[i][1] = yPos + block.shapeCoords[i][1];
		//sprawdzenie, czy miejsce w ktorym chcemy dodac nowy blok jest zajete,jesli tak, konczymy grê
		if (board->boardBody[block.shapeCoords[i][0]][block.shapeCoords[i][1]] == 1)
		{
			endGame();
			return;
		}
		board->boardBody[block.shapeCoords[i][0]][block.shapeCoords[i][1]] = 1;
	}
}

void Game::addingNewBlock()
{
	timeInterval = 400;
	Block* anotherPiece = new Block();
	currentBlock = anotherPiece;
	addingBlockToBoard(*currentBlock, 6, 0);
	return;
}

void Game::checkLines(void)
{
	int temp = 0;
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			//jeœli ca³y wiersz jest zajety usuwamy go 
			if (board->boardBody[i][j] == 1)
				temp++;
		}
		if (temp == 15)
		{
			removedLineNum = j;
			removingLine(removedLineNum);
		}
		temp = 0;
	}
}

void Game::tryMove(Block &block)
{

	for (int i = 3; i>=0; i--)
	{
		board->boardBody[(block.shapeCoords[i][0])][block.shapeCoords[i][1]] = 0;
		block.shapeCoords[i][1] = 1 + block.shapeCoords[i][1];
		board->boardBody[(block.shapeCoords[i][0])][block.shapeCoords[i][1]] = 1;
	}
	for (int rectNumb = 0; rectNumb<4; ++rectNumb)
	{
		if (checkingForCollisions(*currentBlock, rectNumb))
		{
			addingNewBlock();
			break;
		}
	}
}

bool Game::checkingForCollisions(Block &block, int rectNumb)
{
	// jesli dan klocek ma pod sob¹ zajête pole, a nie jest to klocek z jego ksztaltu to zachodzi kolizja
	if (board->boardBody[block.shapeCoords[rectNumb][0]][block.shapeCoords[rectNumb][1] + 1] == 1)
	{
		if (block.shapeCoords[rectNumb][1] + 1 != block.shapeCoords[rectNumb + 1][1])
			return true;
	}
	//jeœli klocek dotyka podlogi, to równie¿ zachodzi kolizja
	if (block.shapeCoords[rectNumb][1] == 19)
		return true;
	else
		return false;
}
void Game::removingLine(int removedLineNum)
{
	score += 10;
	for (int i = 0; i < 15; i++)
	{
		board->boardBody[i][removedLineNum] = 0;
		for (int j = removedLineNum-1; j > 0 ; j--)
		{
			if (board->boardBody[i][j] == 1)
			{
					board->boardBody[i][j] = 0;
					board->boardBody[i][j+1] = 1;
			}
		}
	}
}

void Game::showBoard(Board &board)
{
	for (int j = 0; j <20; j++)
	{
		cout << "|";
		for (int i = 0; i < 15; i++)
		{
			if (board.boardBody[i][j] == 1)
				cout << " *";
			else
				cout << "  ";
		}
		cout << "|";
		cout << endl;
	}
	cout << " ";
	for (int i = 0; i < 15; i++)
	{
		cout << "\\/";
	}
	cout << endl;
}


void Game::ifKeyPressed(Board &board)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (currentBlock->shapeCoords[0][0] != 0 && board.boardBody[currentBlock->shapeCoords[0][0]-1][currentBlock->shapeCoords[0][1]] != 1)
		{
			for (int i = 0; i < 4; i++)
			{
				//przesuniecie w lewo
				board.boardBody[currentBlock->shapeCoords[i][0]][currentBlock->shapeCoords[i][1]] = 0;
				currentBlock->shapeCoords[i][0]--;
				board.boardBody[currentBlock->shapeCoords[i][0]][currentBlock->shapeCoords[i][1]] = 1;
			}
		}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (currentBlock->shapeCoords[3][0] != 14 && board.boardBody[currentBlock->shapeCoords[3][0] + 1][currentBlock->shapeCoords[0][1]] != 1)
		{
			for (int i = 3; i >= 0; i--)
			{
				//przesuniecie w prawo
				board.boardBody[currentBlock->shapeCoords[i][0]][currentBlock->shapeCoords[i][1]] = 0;
				currentBlock->shapeCoords[i][0]++;
				board.boardBody[currentBlock->shapeCoords[i][0]][currentBlock->shapeCoords[i][1]] = 1;
			}
		}

	}
	if (GetAsyncKeyState(VK_UP))
	{
		int x, y;
		//zwiekszanie licznika rotacji
		currentBlock->rotationPos++;
		//zerowanie obecnie zajmowanego miejsca i znalezienie punktu po³o¿enia calego ksztaltu
		for (int i = 0; i < 4; i++)
		{
			board.boardBody[currentBlock->shapeCoords[i][0]][currentBlock->shapeCoords[i][1]] = 0;
			if (i == 0)
			{
				x = currentBlock->shapeCoords[i][0];
				y = currentBlock->shapeCoords[i][1];
			}
		}
		// zwracanie kszta³tu odpowiednigo dla obecnej rotacji i sprawdzanie czy nie bedzie wychodzi³ poza tablice
		if (currentBlock->rotationPos == 1)
		{
			currentBlock->setShape(currentBlock->shapeNumber, currentBlock->rotation1);
			while (currentBlock->shapeCoords[3][0] + x > 14)
			{
				x--;
			}
			addingBlockToBoard(*currentBlock, x, y);
		}
		if (currentBlock->rotationPos == 2)
		{
			currentBlock->setShape(currentBlock->shapeNumber, currentBlock->rotation2);
			while (currentBlock->shapeCoords[3][0] + x > 14)
			{
				x--;
			}
			addingBlockToBoard(*currentBlock, x, y);
		}
		if (currentBlock->rotationPos == 3)
		{
			currentBlock->setShape(currentBlock->shapeNumber, currentBlock->rotation3);
			while (currentBlock->shapeCoords[3][0] + x > 14)
			{
				x--;
			}
			addingBlockToBoard(*currentBlock, x, y);
		}
		if (currentBlock->rotationPos == 4)
		{
			currentBlock->setShape(currentBlock->shapeNumber, currentBlock->shapeTable);
			while (currentBlock->shapeCoords[3][0] + x > 14)
			{
				x--;
			}
			addingBlockToBoard(*currentBlock, x, y);
			currentBlock->rotationPos = 0;
		}


	}
	//przyspieszanie spadajacego obiektu
	if (GetAsyncKeyState(VK_DOWN))
	{
		timeInterval = 200;
	}
	//zatrzymanie gry
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (isPaused == 0)
			isPaused = 1;
		else
			isPaused = 0;
	}
}

void Game::showScore(void)
{
	cout << "SCORE = " << score << endl;
	return;
}


void Game::update()
{
	// czyszczenie ekranu
	system("cls");
	showScore();
	checkLines();
	ifKeyPressed(*board);
	tryMove(*currentBlock);
	showBoard(*board);
	// oczekiwanie na ponowne wywow³anie funkcji, po czasie t= timeInterval
	Sleep(timeInterval);
}

void Game::endGame(void)
{
	isGameEnded = 1;
	isPaused = 1;
	system("cls");
	cout << " ####     ##    #    #  ######       ####   #    #  ######  #####  " << endl;
	cout << "#    #   #  #   ##  ##  #           #    #  #    #  #       #    # " << endl;
	cout << "#       #    #  # ## #  #####       #    #  #    #  #####   #    # " << endl;
	cout << "#  ###  ######  #    #  #           #    #  #    #  #       #####  " << endl;
	cout << "#    #  #    #  #    #  #           #    #   #  #   #       #   #  " << endl;
	cout << " ####   #    #  #    #  ######       ####     ##    ######  #    # " << endl;
}
