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

using namespace std;
namespace fs = std::experimental::filesystem;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
string path = "./save";
int menuPosition = 0;

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
		cout << "　";
	cout << "╔════════════╗\n";
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
		
		cout << "目前存檔：\n";

		showDir(counter, filename);
		
		while (!(cmd >= 0 && cmd <= counter)) {
			cout << "請輸入編號 : ";
			cin >> cmd;
		}

		system("cls");
		cout << "載入 \"" << filename[cmd] << "\" 中 ...... " << endl;
		delay(3000);
		//Game load(filename[cmd]);
	}
	else if (menuPosition == 2) {
		exit(0);
	}
}

void showColor() {
	for (int i = 1; i < 255; i++) {
		SetConsoleTextAttribute(hConsole, i);
		cout << "test" << endl;
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
	//showColor();
	drawMainMenu();
	while (running) {
		int keydown = getKey();
		if (keydown != 0) {
			if (keydown == 38 || keydown == 40)
				moveMenu(keydown);
			if (keydown == 13) {
				mainMenuAction();
			}
		}
	}
	return 0;
}