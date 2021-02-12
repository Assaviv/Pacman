#pragma once
#include <time.h>
#include <stdlib.h>
#include <random>

#define KILL 0

class Ghost
{
public:
	Ghost();
	~Ghost();
	void Move(char** b);
	void setX(int);
	void setY(int);
	void gotoxy(short, short);
	void printBoardChar(char);
private:
	int _x;
	int _y;
};

Ghost::Ghost()
{
	this->_x = 0;
	this->_y = 0;
}

Ghost::~Ghost()
{
}

inline void Ghost::Move(char** b) // CHECK IF PACMAN THEN KILL
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 3);
	int r = 0, count = 0;
	char temp = ' ';
	bool again = true;
	while (again)
	{
		if (count == 100)
			again = false;
		r = distrib(gen);
		switch (r)
		{
		case 1: // down
			if (b[this->_x + 1][this->_y] == char(DOT) || b[this->_x + 1][this->_y] == ' ')
			{
				temp = b[this->_x + 1][this->_y];
				b[this->_x + 1][this->_y] = b[this->_x][this->_y];
				b[this->_x][this->_y] = (char)temp;
				gotoxy(this->_y, this->_x);
				printBoardChar(temp);
				gotoxy(this->_y, this->_x + 1);
				printBoardChar(char(GHOST));
				this->_x += 1;
				again = false;
			}
			if (b[this->_x + 1][this->_y] == PACMAN)
			{
				b[this->_x + 1][this->_y] = (char)178;
				this->_x += 1;
				throw(KILL);
			}
			break;
		case 2: // up
			if (b[this->_x - 1][this->_y] == char(DOT) || b[this->_x - 1][this->_y] == ' ')
			{
				temp = b[this->_x - 1][this->_y];
				b[this->_x - 1][this->_y] = b[this->_x][this->_y];
				b[this->_x][this->_y] = temp;
				gotoxy(this->_y, this->_x);
				printBoardChar(temp);
				gotoxy(this->_y, this->_x - 1);
				printBoardChar(char(GHOST));
				this->_x -= 1;
				again = false;
			}
			if (b[this->_x - 1][this->_y] == PACMAN)
			{
				b[this->_x - 1][this->_y] = (char)178;
				this->_x -= 1;
				throw(KILL);
			}
			break;
		case 0: // right
			if (b[this->_x][this->_y + 1] == char(DOT) || b[this->_x][this->_y + 1] == ' ')
			{
				temp = b[this->_x][this->_y + 1];
				b[this->_x][this->_y + 1] = b[this->_x][this->_y];
				b[this->_x][this->_y] = temp;
				gotoxy(this->_y, this->_x);
				printBoardChar(temp);
				gotoxy(this->_y + 1, this->_x);
				printBoardChar(char(GHOST));
				this->_y += 1;
				again = false;
			}
			if (b[this->_x][this->_y + 1] == PACMAN)
			{
				b[this->_x][this->_y + 1] = (char)178;
				this->_y += 1;
				throw(KILL);
			}
			break;
		case 3:
			if (b[this->_x][this->_y - 1] == char(DOT) || b[this->_x][this->_y - 1] == ' ')
			{
				temp = b[this->_x][this->_y - 1];
				b[this->_x][this->_y - 1] = b[this->_x][this->_y];
				b[this->_x][this->_y] = temp;
				gotoxy(this->_y, this->_x);
				printBoardChar(temp);
				gotoxy(this->_y - 1, this->_x );
				printBoardChar(char(GHOST));
				this->_y -= 1;
				again = false;
			}
			if (b[this->_x][this->_y - 1] == PACMAN)
			{
				b[this->_x][this->_y - 1] = (char)178;
				this->_y -= 1;
				throw(KILL);
			}
			break;
		}
		count++;
	}
}

inline void Ghost::setX(int x)
{
	this->_x = x;
}

inline void Ghost::setY(int y)
{
	this->_y = y;
}


inline void Ghost::gotoxy(short x, short y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, ++y };
	SetConsoleCursorPosition(h, pos);
}

inline void Ghost::printBoardChar(char c)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (c)
	{
	case PACMAN:
		SetConsoleTextAttribute(h, 6);
		break;
	case WALL:
		SetConsoleTextAttribute(h, 68);
		break;
	case char(GHOST):
		SetConsoleTextAttribute(h, 1);
		break;
	}
	_putchar_nolock(c);
	SetConsoleTextAttribute(h, 15);
}