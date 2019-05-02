#include <iostream>
#include <windows.h>

#include "Board.h"

#define CmdWidth 1200
#define CmdHeight 700
#define MenuLineColor 9
#define MenuChoosenColor 240

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
int menuPosition = 0;

void initCmdWindow(int width = CmdWidth, int height = CmdHeight) { // set cmd window's width and height
	HWND console = GetConsoleWindow();
	RECT r;
	
	GetWindowRect(console, &r);

	MoveWindow(console, 100, 100, width, height, TRUE);
}

void drawMainMenu(int index = 0) {
	system("CLS");
	int space = 25;
	for (int i = 0; i < 15; i++)
		cout << "\n";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	for (int i = 0; i < space; i++)
		cout << "　";
	cout << "┌－－－－－－┐\n";
	for (int i = 0; i < space; i++)
		cout << "　";
	cout << "｜　";
	if (index == 0)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "開新遊戲";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << " │\n";
	for (int i = 0; i < space; i++)
		cout << "　";
	cout << "├－－－－－－┤\n";
	for (int i = 0; i < space; i++)
		cout << "　";
	
	cout << "｜　";
	if (index == 1)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "讀取存檔";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << " ｜\n";
	for (int i = 0; i < space; i++)
		cout << "　"; 
	cout << "├－－－－－－┤\n";
	for (int i = 0; i < space; i++)
		cout << "　"; 


	cout << "｜　";
	if (index == 2)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "離開遊戲";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << " ｜\n";

	for (int i = 0; i < space; i++)
		cout << "　"; 
	cout << "└－－－－－－┘\n";
	for (int i = 0; i < 15; i++)
		cout << "\n";
}

void moveMenu(int keydown) {
	if (keydown == 38 || keydown == 40) {
		if (keydown == 38) {
			menuPosition--;
		}
		if (keydown == 40) {
			menuPosition++;
		}
		if (menuPosition > 2)
			menuPosition = 0;
		if (menuPosition < 0)
			menuPosition = 2;
		drawMainMenu(menuPosition);
	}
}

DWORD getKey() { // get user keydown
	INPUT_RECORD irInput;
	DWORD InputsRead = 0;
	ReadConsoleInput(hInput, &irInput, 1, &InputsRead);
	if (irInput.Event.KeyEvent.bKeyDown)
		return irInput.Event.KeyEvent.wVirtualKeyCode;
	else
		return 0;
}

int main() {
	initCmdWindow();
	drawMainMenu();

	while (running) {
		int keydown = getKey();
		if (keydown != 0) {
			moveMenu(keydown);
		}
	}
	return 0;
}