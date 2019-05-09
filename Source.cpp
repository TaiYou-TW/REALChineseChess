#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <experimental/filesystem>
#include <windows.h>

#include "Game.h"

#define CmdWidth 1200
#define CmdHeight 700
#define MenuLineColor 9
#define MenuChoosenColor 240
#define InitColor 7
#define UpArrowKey 38
#define DownArrowKey 40
#define EnterKey 13

using namespace std;
namespace fs = std::experimental::filesystem;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
string path = "./save";
int menuPosition = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
}

void delay(int time) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void storeSavedFilename(int &counter, vector<string> &filename) {
	for (auto& p : fs::directory_iterator(path)) {
		fs::path px = p.path();
		if (px.extension() == ".txt") {
			filename.push_back(px.filename().string());
			counter++;
		}
	}
}

void initCmdWindow(int width = CmdWidth, int height = CmdHeight) { // set cmd window's width and height
	HWND console = GetConsoleWindow();
	RECT r;
	
	GetWindowRect(console, &r);

	MoveWindow(console, 100, 100, width, height, TRUE);
}

void drawMainMenu() {
	int index = menuPosition;
	system("CLS");
	int space = 32;
	int blank_row = 15;
	for (int i = 0; i < blank_row; i++)
		cout << "\n";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	for (int i = 0; i < space; i++)
		cout << "¡@";
	cout << "¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{\n";
	for (int i = 0; i < space; i++)
		cout << "¡@";
	cout << "¢x¡@";
	if (index == 0)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "¶}·s¹CÀ¸";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << "¡@¢x\n";
	for (int i = 0; i < space; i++)
		cout << "¡@";
	cout << "¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t\n";
	for (int i = 0; i < space; i++)
		cout << "¡@";
	
	cout << "¢x¡@";
	if (index == 1)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "Åª¨ú¦sÀÉ";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << "¡@¢x\n";
	for (int i = 0; i < space; i++)
		cout << "¡@"; 
	cout << "¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t\n";
	for (int i = 0; i < space; i++)
		cout << "¡@"; 


	cout << "¢x¡@";
	if (index == 2)
		SetConsoleTextAttribute(hConsole, MenuChoosenColor);
	cout << "Â÷¶}¹CÀ¸";
	SetConsoleTextAttribute(hConsole, MenuLineColor);
	cout << "¡@¢x\n";

	for (int i = 0; i < space; i++)
		cout << "¡@"; 
	cout << "¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}\n";
	for (int i = 0; i < blank_row; i++)
		cout << "\n";
}

void moveMenu(int keydown) {
	if (keydown == UpArrowKey) {
		menuPosition--;
	}
	if (keydown == DownArrowKey) {
		menuPosition++;
	}
	if (menuPosition > 2)
		menuPosition = 0;
	if (menuPosition < 0)
		menuPosition = 2;
	drawMainMenu();
}

void mainMenuAction() {
	SetConsoleTextAttribute(hConsole, InitColor);
	if (menuPosition == 0) {
		system("cls");

		cout << "Game Start¡I\n"; 
		delay(3000);
		drawMainMenu();
	}
	else if (menuPosition == 1) {
		int counter = 0;
		vector<string> filename;
		int cmd = -1;

		system("cls");
		
		storeSavedFilename(counter, filename);
		
		if (counter > 0) {
			cout << "¥Ø«e¦sÀÉ¡G\n";
			int i = 1;
			for (vector<string>::iterator it = filename.begin(); it != filename.end(); ++it, i++)
				cout << i << " : " << *it  << "\n";

			while (!(cmd > 0 && cmd <= counter)) {
				cout << "½Ð¿é¤J½s¸¹(¿é¤J 0 Â÷¶}) : ";
				cin >> cmd;
				if (cmd == 0) {
					drawMainMenu();
					return;
				}
			}

			system("cls");
			cout << "¸ü¤J \"" << filename[cmd-1] << "\" ¤¤ ...... \n";
			delay(3000);
			//Game load(filename[cmd]);
		}
		else {
			cout << "µL¦sÀÉ¡I";
			delay(3000);
			drawMainMenu();
		}
	}
	else if (menuPosition == 2) {
		exit(0);
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
	init();
	initCmdWindow();
	//cout << "ùÝùùùùùùùùùùùùùß\nùø¡@¶Ù¡@ùø\nùàùùùùùùùùùùùùùâ\nùø¡@¢ç¡@ùø\nùãùùùùùùùùùùùùùå\n";
	drawMainMenu();
	
	while (running) {
		int keydown = getKey();

		if (keydown != 0) {
			if (keydown == UpArrowKey || keydown == DownArrowKey) {
				moveMenu(keydown);
			}
			else if (keydown == EnterKey) {
				mainMenuAction();
			}
		}
	}
	return 0;
}