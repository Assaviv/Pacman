#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "Board.h"
#include <conio.h>
#include "resource.h"
#include <chrono>

/*********************************************
* ~TODO: file system with .map files
*		 ~Warm holes (according to protocol)
*		 ~~Fruit to collect more points
*		 ~~~Settings and more customization
*		 ~~~~Kill ghosts option
*		 ~~~~~Kill works bad
*		 ~~~~~~Try catch.. throw smth when killed so the catch will handle the death
*********************************************/
/////////////////////////////////////////////
/* .map files will be in levels dir and will be read according to this protocol: 
*		line: command
*		1:	  rows
*		2:    cols
*		3 -> rows*cols + 2:    map
*		map: 
*		@ - pacman
*		# - wall
*		g - ghost
*		0:9 - fruit,  different colors
*		w - warm hole (only one is allowed)
*       . / space - points
*/
#define UP 72   /// try to get key without ASCII
#define DOWN 80
#define RIGHT 77
#define LEFT 75

int WINNING_SCORE = 2500;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void banner(); // make banner more change able, include settings and levels

int main()
{
	/* Variables: */
	auto ans = IDYES;
	bool exit = true, win = false, out = false;
	int score = false;
	Board* b = new Board();
	char mov = ' ', lastKey = 'a';
	/* Console defaults */
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 24;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL + 300; // bold
	std::wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(h, FALSE, &cfi);
	SetConsoleTitleA("Pacman");
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
	/* Game start menu */
	system("mode 40,14");
	printf("\x1b[d");
	banner(); // maybe will need to return value and built Board* b here.
	/* Game start level */
	system("mode 40,22");
	b->printBoard(false);
	// !_kbhit() for thread like
	mov = _getch();
	while (exit && b->isalive())
	{
		auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		while (!_kbhit())
		{		
			b->printBoard();
			dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			if (dur.count() > 150 && b->isalive())
			{
				b->ghost2();
				b->ghost2();
				b->ghost1();
				b->ghost1();
				if (mov == 'a' ||  mov == 'd' || mov == 's' || mov == 'w'
					|| mov == RIGHT || mov == LEFT || mov == DOWN || mov == UP)
				{
					lastKey = mov;
				}
				exit = b->move(lastKey);
				score = b->getScore();
				if (score >= WINNING_SCORE || !b->isalive())
				{
					goto done;
					out = true;
					break;
				}
				start = std::chrono::high_resolution_clock::now();
			}
			end = std::chrono::high_resolution_clock::now();
		}
		if (!out)
		{
			b->ghost1();
			b->ghost1();
			b->ghost2();
			b->ghost2();
			mov = _getch();
			if (mov == 'a' || mov == 'd' || mov == 's' || mov == 'w'
				|| mov == RIGHT || mov == LEFT || mov == DOWN || mov == UP)
			{
				lastKey = mov;
			}
			exit = b->move(lastKey);
			score = b->getScore();
			Sleep(150);
		}
		done:
		if (score >= WINNING_SCORE)
		{
			win = true;
			exit = false;
		}
	}
	/* End of the game */
	(win) ? (PlaySoundW(TEXT("music/tada.wav"), NULL, SND_FILENAME | SND_ASYNC)) : (PlaySoundW(TEXT("music/death.wav"), NULL, SND_FILENAME | SND_ASYNC));
	b->finish();
	system("mode 40,25");
	b->printBoard(false);
	// TODO: replace all () ? () : ();
	(win) ? (std::cout << "----------------------------------------\n" << "-----------YOU-----------WIN!-----------\n\a" << "----------------------------------------\n") :
		(std::cout << "----------------------------------------\n" << "-----------YOU-----------LOST-----------\n\a" << "----------------------------------------\n");
	(win) ? (ans = MessageBox(NULL, L"You succeed collecting all the points!\nDo you wanna play again?", L"Congratulation!", MB_YESNO)):
		(ans = MessageBox(NULL, L"You were killed by a ghost👻\nDo you wanna play again?", L"Oh No!", MB_YESNO));
	lpCursor.bVisible = true;
	lpCursor.dwSize = 10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
	if (ans == IDYES)  // maybe gets it up a bit..
		main();
	return 0;
}

void banner()
{
	PlaySoundW(TEXT("music/intro.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	char ans = ' ';
	int place = 0;
	do
	{

		switch (ans)
		{
		case UP:
			if (place == 0)
				break;
			else
				place--;
			break;
		case DOWN:
			if (place == 2)
				break;
			else
				place++;
			break;
		default:
			break;
		}
		std::cout << "                                        \n";
		std::cout << "                                        \n";
		std::cout << "           Choose  difficulty           \n";
		std::cout << "                                        \n";
		switch (place)
		{
		case 0:
			SetConsoleTextAttribute(h, 159);
			std::cout << "                  Easy           ,--.   \n";
			SetConsoleTextAttribute(h, 15);
			std::cout << "                                |oo  |  \n";
			std::cout << "                 Medium         |~~  |  \n";
			std::cout << "                                |/\\/\\|  \n";
			std::cout << "                  Hard                  \n";
			std::cout << "                                        \n";
			break;
		case 1:
			std::cout << "   ,--.           Easy                  \n";
			std::cout << "  |  oo|                                \n";
			SetConsoleTextAttribute(h, 159);
			std::cout << "  |  ~~|         Medium                 \n";
			SetConsoleTextAttribute(h, 15);
			std::cout << "  |/\\/\\|                                \n";
			std::cout << "                  Hard                  \n";
			std::cout << "                                        \n";
			break;
		case 2:
			std::cout << "                  Easy                  \n";
			std::cout << "                                        \n";
			std::cout << "                 Medium         .--.    \n";
			std::cout << "                               / _.-'   \n";
			SetConsoleTextAttribute(h, 159);
			std::cout << "                  Hard         \\  '-.   \n";
			SetConsoleTextAttribute(h, 15);
			std::cout << "                                '--'    \n";
			break;
		}
		std::cout << "             [s]: To select             \n";
		std::cout << "                                        \n";
		ans = _getch();
		printf("\x1b[d");
	} while (ans != 's' && ans != 'S');
	switch (place)
	{
	case 0:
		WINNING_SCORE = 1000;
		break;
	case 1:
		WINNING_SCORE = 2500;
		break;
	case 2:
		WINNING_SCORE = 5000;
		break;
	}
	PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
