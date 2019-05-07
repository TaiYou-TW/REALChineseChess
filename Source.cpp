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

void showDir(int &counter, vector<string> &filename) {
	for (auto& p : fs::directory_iterator(path)) {
		fs::path px = p.path();
		if (px.extension() == ".txt") {
			cout << counter++ << " : " << px.filename() << "\n";
			filename.push_back(px.filename().string());
		}
	}
}

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
	for (int i = 0; i < 15; i++)
		cout << "\n";
}

void moveMenu(int keydown) {
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

void mainMenuAction() {
	if (menuPosition == 0) {
		
	}
	else if (menuPosition == 1) {
		int counter = 0;
		vector<string> filename;
		int cmd = -1;

		SetConsoleTextAttribute(hConsole, InitColor);
		system("cls");
		
		cout << "¥Ø«e¦sÀÉ¡G\n";

		showDir(counter, filename);
		
		while (!(cmd >= 0 && cmd <= counter)) {
			cout << "½Ð¿é¤J½s¸¹ : ";
			cin >> cmd;
		}

		system("cls");
		cout << "¸ü¤J \"" << filename[cmd] << "\" ¤¤ ...... \n";
		delay(3000);
		//Game load(filename[cmd]);
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
	cout << "ùÝùùùùùùùùùùùùùß\nùø¡@¶Ù¡@ùø\nùàùùùùùùùùùùùùùâ\nùø¡@¢ç¡@ùø\nùãùùùùùùùùùùùùùå\n";
	//drawMainMenu();
	
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