#pragma once
/**************************
* TODO: H&L size read from
* .map file and then insert
* to them but default map
* is built in to the code.
**************************/
#define H_BOARD_SIZE 20
#define L_BOARD_SIZE 40
#define WALL '#'
#define DOT 249
#define PACMAN '@'
#define PACMAN_PLACE_X 4
#define PACMAN_PLACE_Y 5
#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75
#define GHOST 254

#include <stdio.h>
#include <string>
#include <Windows.h>
#include <time.h> // for random may not being in use
#include <stdlib.h> // ^ as well
#include "ghost.h"

char open_ = '{';
char close_ = '<';

class Board
{
public:
	Board();  /* TODO gets parameter of level, Board be built accordingly 
			     By default he will build the regular level. else will call
				 a new function that will get level as well and will return
				 char** map accordingly.. */
	~Board(); // Release memory of the board.
	void printBoard(); // print each char according to color code.
	void finish();  // clear the broad from all the points
	bool move(char dir);  // move char according to the direction..
	void ghost1();  /*	will be remove for new ghost acting,		*/
	void ghost2();	/*			the ghost now moves randomly to the same spot*/
	char** _board;  // try to make it  private
	bool isalive(); // getter
	int getScore(); // ^ as well
	void gotoxy(size_t x, size_t y);
private:
	bool alive;
	Ghost g1;    // will be generated differently
	Ghost g2;   //  -- Ghost[] list that initialize in the Board constructor
	Ghost g3;  //   ---- so the handling of ghost will be more efficient
	Ghost g4; //    ------ and need to add option to eat ghost killer
	int _x;  //     position of Panama
	int _y;
	int score;  // the total points eaten multilayer by 10 
			   //  -- TODO: option to eat bonus fruit for extra points (100 for fruit will be fare) 
	bool open;//   Conditional variable for pacman mouth condition (open - '{' / '}' or close '<' / '>')
};

Board::Board()
{
	char** a = new char* [H_BOARD_SIZE];
	for (int k = 0; k < H_BOARD_SIZE; k++)
	{
		a[k] = new char[L_BOARD_SIZE];
	}
	this->_board = a;
	for (int i = 0; i < H_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_BOARD_SIZE; j++)
		{
			if (j == 0 || i == 0 || i == L_BOARD_SIZE - 1 || j == L_BOARD_SIZE - 1 || i == H_BOARD_SIZE - 1)
			{
				this->_board[i][j] = WALL;
			}
			else
			{
				this->_board[i][j] = char(DOT);
			}
			if ((i == 10 && j > 11 && j < 29) || j == 11 && i < 11 && i > 6 ||
				i == 6 && j >= 11 && j < 29 && j != 20 && j != 19 && j != 18 && j != 21 && j != 22 && j != 17 ||
				j == 29 && i < 11 && i >= 6 || i == 13 && j >= 11 && j <= 29)
			{
				this->_board[i][j] = WALL;
			}
			else if (i == 8 && (j == 15 || j == 24 || j == 18 || j == 21))
			{
				this->_board[i][j] = char(GHOST);
			}
		}
	}
	this->g1.setX(8);
	this->g1.setY(15);
	this->g2.setX(8);
	this->g2.setY(24);
	this->g3.setX(8);
	this->g3.setY(18);
	this->g4.setX(8);
	this->g4.setY(21);
	this->_x = PACMAN_PLACE_X;
	this->_y = PACMAN_PLACE_Y;
	this->_board[PACMAN_PLACE_X][PACMAN_PLACE_Y] = PACMAN;
	this->score = 0;
	this->alive = true;
	this->open = false;
}

Board::~Board()
{
	delete[] this->_board;
}

inline void Board::printBoard()
{
	std::string ps = "";
	std::string temp = "";
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 71);

	if (this->score == 0)
	{
		ps = "--------------- Score: " + std::to_string(this->score) + " ---------------";
	}
	else if (this->score >= 10 && this->score < 100)
	{
		ps = "--------------- Score: " + std::to_string(this->score) + " --------------";
	}
	else if (this->score >= 100 && this->score < 1000)
	{
		ps = "--------------- Score: " + std::to_string(this->score) + " -------------";
	}
	else
	{
		ps = "--------------- Score: " + std::to_string(this->score) + " ------------";
	}
	puts(ps.c_str());
	for (int i = 0; i < H_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_BOARD_SIZE; j++)
		{
			if (this->_board[i][j] == PACMAN)
			{
				SetConsoleTextAttribute(h, 6);
			}
			else if (this->_board[i][j] == WALL)
			{
				SetConsoleTextAttribute(h, 68);
			}
			else if (this->_board[i][j] == char(GHOST))
			{
				SetConsoleTextAttribute(h, 1);
			}
			if (this->_board[i][j] == PACMAN)
			{
				(this->open) ? (_putchar_nolock(open_)) : (_putchar_nolock(close_));
				this->open = !this->open;
			}
			else
			{
				_putchar_nolock(this->_board[i][j]);
			}
			SetConsoleTextAttribute(h, 15);
		}
		puts("");
	}
}

inline void Board::finish()
{
	for (int i = 0; i < H_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_BOARD_SIZE; j++)
		{
			if (this->_board[i][j] == (char)DOT)
			{
				this->_board[i][j] = ' ';
				if (i%4 == 0 && j%4 == 0)
				{
					this->printBoard();
					printf("\x1b[d");
				}
			}
		}
	}
}

inline bool Board::move(char dir)
{
	if (dir == 'w' || dir == 'a' || dir == 's' || dir == 'd' ||
		dir == UP_ARROW || dir == DOWN_ARROW || dir == RIGHT_ARROW || dir == LEFT_ARROW)
	{
		if (dir == 'd' || dir == RIGHT_ARROW)
		{
			open_ = '{';
			close_ = '<';
			if (this->_board[this->_x][this->_y + 1] != '#')
			{
				if (this->_board[this->_x][this->_y + 1] == char(DOT))
				{
					this->score += 10;
					PlaySoundW(TEXT("music/eat2.wav"), NULL, SND_FILENAME | SND_ASYNC);

				}
				else if (this->_board[this->_x][this->_y + 1] == char(GHOST))
				{
					return false;
				}
				this->_board[this->_x][this->_y] = ' ';
				this->_board[this->_x][this->_y + 1] = PACMAN;
				this->_y += 1;
			}
		}
		else if (dir == 'w' || dir == UP_ARROW)
		{
			if (this->_board[this->_x - 1][this->_y] != '#')
			{
				if (this->_board[this->_x - 1][this->_y] == char(DOT))
				{
					this->score += 10;
					PlaySoundW(TEXT("music/eat2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (this->_board[this->_x - 1][this->_y] == char(GHOST))
				{
					return false;
				}
				this->_board[this->_x][this->_y] = ' ';
				this->_board[this->_x - 1][this->_y] = PACMAN;
				this->_x -= 1;
			}
		}
		else if (dir == 's' || dir == DOWN_ARROW)
		{
			if (this->_board[this->_x + 1][this->_y] != '#')
			{
				if (this->_board[this->_x + 1][this->_y] == char(DOT))
				{
					this->score += 10;
					PlaySoundW(TEXT("music/eat2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (this->_board[this->_x + 1][this->_y] == char(GHOST))
				{
					return false;
				}
				this->_board[this->_x][this->_y] = ' ';
				this->_board[this->_x + 1][this->_y] = PACMAN;
				this->_x += 1;
			}
		}
		else if (dir == 'a' || dir == LEFT_ARROW)
		{
			open_ = '}';
			close_ = '>';
			if (this->_board[this->_x][this->_y - 1] != '#')
			{
				if (this->_board[this->_x][this->_y - 1] == char(DOT))
				{
					this->score += 10;
					PlaySoundW(TEXT("music/eat2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (this->_board[this->_x][this->_y - 1] == char(GHOST))
				{
					return false;
				}
				this->_board[this->_x][this->_y] = ' ';
				this->_board[this->_x][this->_y - 1] = PACMAN;
				this->_y -= 1;
			}
		}
	}
	return true;
}

inline void Board::ghost1()
{
	try
	{
		this->g1.Move(this->_board);
		this->g1.Move(this->_board);
		this->g2.Move(this->_board);
		this->g2.Move(this->_board);
	}
	catch (...)
	{
		this->alive = false;
	}

}

inline void Board::ghost2()
{
	try
	{
		this->g3.Move(this->_board);
		this->g3.Move(this->_board);
		this->g4.Move(this->_board);
		this->g4.Move(this->_board);
	}
	catch (...)
	{
		this->alive = false;
	}

}

inline bool Board::isalive()
{
	return this->alive;
}

inline int Board::getScore()
{
	return this->score;
}
