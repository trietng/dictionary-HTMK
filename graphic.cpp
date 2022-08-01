#include "graphic.hpp"

// graphics: 
void menuDrawChooseDictionary(short opt) {
	short opt_ = opt;
	const char* ch1 = "EMOTIONAL";
	LPSTR lpstr1 = const_cast<LPSTR>(ch1);
	setColorBGTextXY(50, 8, 15, ((opt_ == 1) ? 2 : 0), lpstr1);
	const char* ch2 = "ENG-ENG";
	LPSTR lpstr2 = const_cast<LPSTR>(ch2);
	setColorBGTextXY(50, 9, 15, ((opt_ == 2) ? 3 : 0), lpstr2);
	const char* ch3 = "SLANG";
	LPSTR lpstr3 = const_cast<LPSTR>(ch3);
	setColorBGTextXY(50, 10, 15, ((opt_ == 3) ? 4 : 0), lpstr3);
	const char* ch4 = "VIE-ENG";
	LPSTR lpstr4 = const_cast<LPSTR>(ch4);
	setColorBGTextXY(50, 11, 15, ((opt_ == 4) ? 5 : 0), lpstr4);
	SetBGColor(16);
}

// graphics:
void menuDrawEnterDictionary(short opt) {
	short opt_ = opt;
	SetColor(4);
	gotoxy(47, 7);
	string str;

	cout << "Please choose one of them:";
	const char* ch1 = "1. Search for a keyword.";
	LPSTR lpstr1 = const_cast<LPSTR>(ch1);
	setColorBGTextXY(50, 8, 15, ((opt_ == 1) ? 2 : 0), lpstr1);

	const char* ch2 = "2. Search for a definition.";
	LPSTR lpstr2 = const_cast<LPSTR>(ch2);
	setColorBGTextXY(50, 9, 15, ((opt_ == 2) ? 3 : 0), lpstr2);

	const char* ch3 = "3. View history of search words.";
	LPSTR lpstr3 = const_cast<LPSTR>(ch3);
	setColorBGTextXY(50, 10, 15, ((opt_ == 3) ? 4 : 0), lpstr3);

	const char* ch4 = "4. Add new word and its definition.";
	LPSTR lpstr4 = const_cast<LPSTR>(ch4);
	setColorBGTextXY(50, 11, 15, ((opt_ == 4) ? 5 : 0), lpstr4);

	const char* ch5 = "5. Edit definition.";
	LPSTR lpstr5 = const_cast<LPSTR>(ch5);
	setColorBGTextXY(50, 12, 15, ((opt_ == 5) ? 6 : 0), lpstr5);

	const char* ch6 = "6. Remove a word.";
	LPSTR lpstr6 = const_cast<LPSTR>(ch6);
	setColorBGTextXY(50, 13, 15, ((opt_ == 6) ? 7 : 0), lpstr6);

	const char* ch7 = "7. Reset the dictionary.";
	LPSTR lpstr7 = const_cast<LPSTR>(ch7);
	setColorBGTextXY(50, 14, 15, ((opt_ == 7) ? 8 : 0), lpstr7);

	const char* ch8 = "8. View a random word.";
	LPSTR lpstr8 = const_cast<LPSTR>(ch8);
	setColorBGTextXY(50, 15, 15, ((opt_ == 8) ? 9 : 0), lpstr8);

	const char* ch9 = "9. View the favourite list.";
	LPSTR lpstr9 = const_cast<LPSTR>(ch9);
	setColorBGTextXY(50, 16, 15, ((opt_ == 9) ? 10 : 0), lpstr9);

	const char* ch10 = "10. Guess definition game.";
	LPSTR lpstr10 = const_cast<LPSTR>(ch10);
	setColorBGTextXY(50, 17, 15, ((opt_ == 10) ? 11 : 0), lpstr10);

	const char* ch11 = "11. Guess word game.";
	LPSTR lpstr11 = const_cast<LPSTR>(ch11);
	setColorBGTextXY(50, 18, 15, ((opt_ == 11) ? 12 : 0), lpstr11);

	const char* ch12 = "12. Choose another dictionary.";
	LPSTR lpstr12 = const_cast<LPSTR>(ch12);
	setColorBGTextXY(50, 19, 15, ((opt_ == 12) ? 13 : 0), lpstr12);

	const char* ch13 = "0. EXIT";
	LPSTR lpstr13 = const_cast<LPSTR>(ch13);
	setColorBGTextXY(50, 20, 15, ((opt_ == 13) ? 14 : 0), lpstr13);

	SetBGColor(16);
}

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

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}


void menu()
{
	ShowConsoleCursor(0);
	//----- setting ----
	int x = 50; int y = 5;
	int w = 20;
	int h = 2;
	int t_color = 11;
	int b_color = 1;
	int b_color_sang = 75;
	string nd = "hello";
	int sl = 4;
	n_box(x, y, w, h, t_color, b_color, nd, sl);

	//-------------
	int xp = x; int yp = y;//tọa độ thanh sáng
	int xcu = xp; int ycu = yp;
	bool kt = true;
	char keyBoard = {};
	do {
		//------ in ----
		if (kt == true)
		{
			//----- back space ----
			gotoxy(xcu, ycu);
			thanh_sang(xcu, ycu, w, h, b_color, nd);//rs thanh sang cu
			xcu = xp; ycu = yp;
			//-------------
			thanh_sang(xp, yp, w, h, b_color_sang, nd);
			kt = false;
		}
		//----- dieu khien ---- //----- di chuyen ----
		if (_kbhit())
		{
			keyBoard = _getch();
			if (keyBoard == -32)
			{
				kt = true;// đã bấm
				keyBoard = _getch();
				if (keyBoard == 72)
				{
					if (yp != y)yp -= 2;
					else
					{
						yp = y + h * (sl - 1);
					}
				}
				else if (keyBoard == 80)
				{
					if (yp != y + h * (sl - 1))yp += 2;
					else
					{
						yp = y;
					}
				}
			}
		} 
		//---- speed ----
	} while (keyBoard != '\r');

}
void thanh_sang(int x, int y, int w, int h, int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoxy(ix, iy); cout << " ";
		}
	}
	SetColor(7);
	gotoxy(x + 1, y + 1);
	cout << nd;
}

void box(int x, int y, int w, int h, int t_color, int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoxy(ix, iy); cout << " ";
		}
	}
	SetColor(7);
	gotoxy(x + 1, y + 1);
	cout << nd;
	//============= ve vien =============
	textcolor(1);
	SetColor(t_color);//update
	if (h <= 1 || w <= 1)return;
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoxy(ix, y);
		cout << char(196);
		gotoxy(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoxy(x, iy);
		cout << char(179);
		gotoxy(x + w, iy);
		cout << char(179);
	}
	gotoxy(x, y); cout << char(218);
	gotoxy(x + w, y); cout << char(191);
	gotoxy(x, y + h); cout << char(192);
	gotoxy(x + w, y + h); cout << char(217);

}
void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd, int sl)
{
	for (int i = 0; i < sl; i++)
	{
		box(x, y + (i * 2), w, h, t_color, b_color, nd);//i = 0 => x,y, i = 1: x,y+2
		if (i != 0)
		{
			gotoxy(x, y + (i * 2)); cout << char(195);
			gotoxy(x + w, y + (i * 2)); cout << char(180);
		}
	}
}