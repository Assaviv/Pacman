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
	int temp = ' ';
	bool again = true;
	while (again)
	{
		if (count == 100)
			again = false;
		r = distrib(gen);
		switch (r)
		{
		case 1:
			if (b[this->_x + 1][this->_y] == char(DOT) || b[this->_x + 1][this->_y] == ' ')
			{
				temp = b[this->_x + 1][this->_y];
				b[this->_x + 1][this->_y] = b[this->_x][this->_y];
				b[this->_x][this->_y] = (char)temp;
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
