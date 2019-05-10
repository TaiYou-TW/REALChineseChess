#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <experimental/filesystem>
#include <windows.h>

#include "Game.h"

#define CmdWidth 1200
#define CmdHeight 650
#define MainMenuLineColor 9
#define MainMenuChoosenColor 240
#define InitColor 7
#define UpArrowKey 38
#define DownArrowKey 40
#define EnterKey 13
#define MainMenuTextPositionX 67
#define MainMenuTextPositionY 16
#define WindowBottomY 37

using namespace std;
namespace fs = std::experimental::filesystem;

const string path = "./save";
const string mainMenuText[3] = { "開新遊戲", "讀取存檔", "離開遊戲" };

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
int mainMenuPosition = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
}

void GoToXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;

	if (!SetConsoleCursorPosition(hConsole, coord))
	{
		cout << "移動游標err";
	}
}

void delay(int time) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void storeSavedFilename(int &counter, vector<string> &filename) {
	for (auto& p : fs::directory_iterator(path)) {
		fs::path px = p.path();
		if (px.extension() == ".txt") {
			cout << px << endl;
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

void colorMainMenuCursor() { // color menu's cursor
	SetConsoleTextAttribute(hConsole, MainMenuLineColor);
	for (int i = MainMenuTextPositionY, j = 0; i <= MainMenuTextPositionY + 4; i += 2, j++) {
		GoToXY(MainMenuTextPositionX, i);
		cout << mainMenuText[j];
	}

	SetConsoleTextAttribute(hConsole, MainMenuChoosenColor);
	GoToXY(MainMenuTextPositionX, MainMenuTextPositionY + mainMenuPosition * 2);
	cout << mainMenuText[mainMenuPosition];
	GoToXY(0, WindowBottomY);
}

void drawMainMenu() {
	int index = mainMenuPosition;
	int space = 32;
	int blank_row = 15;

	system("CLS");
	SetConsoleTextAttribute(hConsole, MainMenuLineColor);

	for (int i = 0; i < blank_row; i++)
		cout << "\n";

	for (int i = 0; i < space; i++)
		cout << "　";

	cout << "┌────────────┐\n";
	for (int i = 0; i < space; i++)
		cout << "　";

	cout << "│　" << mainMenuText[0] << "　│\n";
	for (int i = 0; i < space; i++)
		cout << "　";

	cout << "├────────────┤\n";
	for (int i = 0; i < space; i++)
		cout << "　";
	
	cout << "│　" << mainMenuText[1] << "　│\n";
	for (int i = 0; i < space; i++)
		cout << "　"; 

	cout << "├────────────┤\n";
	for (int i = 0; i < space; i++)
		cout << "　"; 

	cout << "│　" << mainMenuText[2] << "　│\n";
	for (int i = 0; i < space; i++)
		cout << "　"; 

	cout << "└────────────┘\n";
	for (int i = 0; i < blank_row; i++)
		cout << "\n";
	colorMainMenuCursor();
}

void moveMainMenu(int keydown) { // move menu's cursor
	if (keydown == UpArrowKey) {
		mainMenuPosition--;
	}
	if (keydown == DownArrowKey) {
		mainMenuPosition++;
	}
	if (mainMenuPosition > 2)
		mainMenuPosition = 0;
	if (mainMenuPosition < 0)
		mainMenuPosition = 2;
	colorMainMenuCursor();
}

void startNewGame() {
	GoToXY(MainMenuTextPositionX, MainMenuTextPositionY);
	cout << "Game Start！\n";
	delay(3000);
}

void loadGame() {
	int counter = 0;
	vector<string> filename;
	string cmd = "";

	storeSavedFilename(counter, filename);

	if (counter > 0) {
		cout << "目前存檔：\n";
		int i = 1;
		for (vector<string>::iterator it = filename.begin(); it != filename.end(); ++it, i++)
			cout << i << " : " << *it << "\n";

		while (atoi(cmd.c_str()) < 1 || atoi(cmd.c_str()) > counter) {
			cout << "請輸入編號(輸入 0 離開) : ";
			cin >> cmd;
			if (cmd[0] == '0' && cmd.length() == 1) {
				return;
			}
		}

		system("cls");
		cout << "載入 \"" << filename[atoi(cmd.c_str()) - 1] << "\" 中 ...... \n";
		delay(3000);
		cout << "沒有下一步ㄌ";
		delay(1000);
		Game save(filename[atoi(cmd.c_str()) - 1]);
	}
	else {
		cout << "無存檔！";
		delay(3000);
		drawMainMenu();
	}
}

void mainMenuAction() {
	SetConsoleTextAttribute(hConsole, InitColor);
	system("CLS");
	if (mainMenuPosition == 0) {
		startNewGame();
	}
	else if (mainMenuPosition == 1) {
		loadGame();
	}
	else if (mainMenuPosition == 2) {
		exit(0);
	}
	drawMainMenu();
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
	drawMainMenu();
	
	while (running) {
		int keydown = getKey();

		if (keydown != 0) {
			if (keydown == UpArrowKey || keydown == DownArrowKey) {
				moveMainMenu(keydown);
			}
			else if (keydown == EnterKey) {
				mainMenuAction();
			}
		}
	}
	return 0;
}