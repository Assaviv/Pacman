#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "Board.h"
#include <conio.h>
#include <cwchar>
#include <thread>

#define UP 72
#define DOWN 80

int WINNING_SCORE = 2500;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void banner();

int main()
{
	auto ans = IDYES;
	bool exit = true, win = false;
	int score = false;
	Board* b = new Board();
	char mov = ' ';
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
	system("mode 40,14");
	printf("\x1b[d");
	banner();
	system("mode 40,22");
	while (exit && b->isalive())
	{
		b->printBoard();
		b->ghost1();
		b->ghost1();
		b->ghost2();
		b->ghost2();
		mov = _getch();
		exit = b->move(mov);
		score = b->getScore();
		if (score >= WINNING_SCORE)
		{
			win = true;
			exit = false;
		}
		printf("\x1b[d");
		//Sleep(100);
	}
	(win) ? (PlaySoundW(TEXT("music/tada.wav"), NULL, SND_FILENAME | SND_ASYNC)) : (PlaySoundW(TEXT("music/death.wav"), NULL, SND_FILENAME | SND_ASYNC));
	b->finish();
	system("mode 40,25");
	b->printBoard();
	// TODO: replace all () ? () : ();
	(win) ? (std::cout << "----------------------------------------\n" << "-----------YOU-----------WIN!-----------\n\a" << "----------------------------------------\n") :
		(std::cout << "----------------------------------------\n" << "-----------YOU-----------LOST-----------\n\a" << "----------------------------------------\n");
	(win) ? (ans = MessageBox(NULL, L"You succeed collecting all the points!\nDo you wanna play again?", L"Congratulation!", MB_YESNO)) : (ans = MessageBox(NULL, L"You were killed by a ghost👻\nDo you wanna play again?", L"Oh No!", MB_YESNO));
	lpCursor.bVisible = true;
	lpCursor.dwSize = 10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
	if (ans == IDYES)
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
			{
				//blip();
				place--;
			}
			break;
		case DOWN:
			if (place == 2)
				break;
			else
			{
				//blip();
				place++;
			}
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
