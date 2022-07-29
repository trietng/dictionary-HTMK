#include "graphic.hpp"

string headline() {
	string hl;
	return hl = R"(  

    ____  _      __  _                             
   / __ \(_)____/ /_(_)___  ____  ____ ________  __
  / / / / / ___/ __/ / __ \/ __ \/ __ `/ ___/ / / /
 / /_/ / / /__/ /_/ / /_/ / / / / /_/ / /  / /_/ / 
/_____/_/\___/\__/_/\____/_/ /_/\__,_/_/   \__, /  
                                          /____/   
             
              
    )";
}
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}


void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}


WORD textAttr()
{
	HANDLE hConsoleOutput;
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
	return ConsoleInfo.wAttributes;
}


void resetTextAttr()
{
	HANDLE hConsoleOutput;
	DWORD Default_Color = textAttr();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleOutput, Default_Color);
}

void setColorBGTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, ...)
{
	gotoxy(x, y);
	SetBGColor(background);
	SetColor(color);

	// Using C++11 varargs to print more data
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);

	resetTextAttr();
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void moveChoice(int row, int y, int& opt) {
	char keyBoard = {};
	do
	{
		keyBoard = _getch();
		switch (keyBoard)
		{
		case KEY_DOWN:
			if (y + 1 != row + 7)
			{
				y++;
				opt++;
				gotoxy(7, y + 1);
			}
			else
			{
				y -= (row - 1);
				opt = 1;
				gotoxy(7, y + 1);
			}
			break;
		case KEY_UP:
			if (y - 1 != 6)
			{
				y--;
				opt--;
				gotoxy(7, y + 1);
			}
			else
			{
				y += (row - 1);
				opt = row;
				gotoxy(7, y + 1);
			}
			break;
		default:
			break;
		}
	} while (keyBoard != '\r');
}