#pragma once
class Board
{
public:
	Board();
	~Board();
	int boardBody[15][20];
	friend class Board;
};

