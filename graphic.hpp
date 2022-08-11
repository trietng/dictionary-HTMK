#pragma once
#pragma warning(disable : 4996)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <utility>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <ctime>
#include <Windows.h>
#include <chrono>
#include <tchar.h>
#include <thread>
#include <vector>

using namespace std;
string headline();
//use arrow keys for moving
const int KEY_UP = 72;
const int KEY_DOWN = 80;

//Color text (choose from 1 to 16 colors)
void SetColor(WORD color);

//Color background (choose from 1 to 16 colors)
void SetBGColor(WORD color);

//Move the cursor to select(x: column,  y: row)
void gotoxy(short x, short y);

//Get the text data of the console and return the current text data
WORD textAttr();

//Reset the attribute of the console
void resetTextAttr();

//Color the text and its own background based on the position
void setColorBGTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, ...);


//true/false to show/hide the cursor
void ShowConsoleCursor(bool showFlag);

void moveChoice(int row, int y, int& opt);

void menuDrawEnterDictionary(short opt);

void menuDrawChooseDictionary(short opt);

void thanh_sang(int x, int y, int w, int h, int b_color, vector<string> nd, int fix);

void box(int x, int y, int w, int h, int t_color, int b_color, vector<string> nd, int fix);

void n_box(int x, int y, int w, int h, int t_color, int b_color, vector<string> nd, int sl, int fix);

int draw4options(vector<string> nd);

void textcolor(int x);