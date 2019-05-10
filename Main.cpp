#include <windows.h>
#include <chrono>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "Game.h"

#define CmdWidth 1200
#define CmdHeight 650

#define MainMenuLineColor 9
#define MainMenuChoosenColor 240
#define InitColor 7

#define UpArrowKey 38
#define LeftArrowKey 37
#define RightArrowKey 39
#define DownArrowKey 40
#define EnterKey 13

#define MainMenuTextPositionX 55
#define MainMenuTextPositionY 16
#define WindowBottomY 37

#define BoardRow 10
#define BoardCol 9

using namespace std;
namespace fs = std::experimental::filesystem;

const string savePath = "./save";
const string mainMenuText[3] = {"開新遊戲", "讀取存檔", "離開遊戲"};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
bool gameRunning = true;
int mainMenuPosition = 0;
Coord cursor;

void init()
{
    SetConsoleTextAttribute(hConsole, InitColor);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // system("chcp 65001");
    system("CHCP 950");  // BIG-5
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

void delay(int time) { std::this_thread::sleep_for(std::chrono::milliseconds(time)); }

DWORD getKey()
{  // get user keydown
    INPUT_RECORD irInput;
    DWORD InputsRead = 0;
    ReadConsoleInput(hInput, &irInput, 1, &InputsRead);
    if (irInput.Event.KeyEvent.bKeyDown)
        return irInput.Event.KeyEvent.wVirtualKeyCode;
    else
        return 0;
}

void storeSavedFilename(int &counter, vector<string> &filename)
{
    cout << "目前存檔：\n";
    int i = 1;
    for (auto &p : fs::directory_iterator(savePath))
    {
        fs::path px = p.path();
        if (px.extension() == ".txt")
        {
            cout << i++ << " : " << px.stem() << endl;
            filename.push_back(px.string());
            counter++;
        }
    }
}

void initCmdWindow(int width = CmdWidth, int height = CmdHeight)
{  // set cmd window's width and height
    HWND console = GetConsoleWindow();
    RECT r;

    GetWindowRect(console, &r);

    MoveWindow(console, 100, 100, width, height, TRUE);
}

void colorMainMenuCursor()
{  // color menu's cursor
    SetConsoleTextAttribute(hConsole, MainMenuLineColor);
    for (int i = MainMenuTextPositionY, j = 0; i <= MainMenuTextPositionY + 4;
         i += 2, j++)
    {
        GoToXY(MainMenuTextPositionX, i);
        cout << mainMenuText[j];
    }

    SetConsoleTextAttribute(hConsole, MainMenuChoosenColor);
    GoToXY(MainMenuTextPositionX, MainMenuTextPositionY + mainMenuPosition * 2);
    cout << mainMenuText[mainMenuPosition];
    GoToXY(0, WindowBottomY);
}

void drawMainMenu()
{
    int index = mainMenuPosition;
    int space = 26;
    int blank_row = 15;

    system("CLS");
    SetConsoleTextAttribute(hConsole, MainMenuLineColor);

    for (int i = 0; i < blank_row; i++) cout << "\n";

    for (int i = 0; i < space; i++) cout << "　";

    cout << "┌────────────┐\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "│　" << mainMenuText[0] << "　│\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "├────────────┤\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "│　" << mainMenuText[1] << "　│\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "├────────────┤\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "│　" << mainMenuText[2] << "　│\n";
    for (int i = 0; i < space; i++) cout << "　";

    cout << "└────────────┘\n";
    for (int i = 0; i < blank_row; i++) cout << "\n";
    colorMainMenuCursor();
}

void moveMainMenu(int keydown)
{  // move menu's cursor
    if (keydown == UpArrowKey)
    {
        mainMenuPosition--;
    }
    if (keydown == DownArrowKey)
    {
        mainMenuPosition++;
    }
    if (mainMenuPosition > 2) mainMenuPosition = 0;
    if (mainMenuPosition < 0) mainMenuPosition = 2;
    colorMainMenuCursor();
}

void printGameFormat()
{
    ifstream in;
    in.open("./Format/main.ya");
    string line;
    while (getline(in, line))
    {
        cout << line << "\n";
    }
}

void moveCursor(int keydown)
{
    if (keydown == UpArrowKey)
    {
        cursor.y--;
    }
    else if (keydown == DownArrowKey)
    {
        cursor.y++;
    }
    else if (keydown == LeftArrowKey)
    {
        cursor.x--;
    }
    else if (keydown == RightArrowKey)
    {
        cursor.x++;
    }
    if (cursor.x < 0) cursor.x = BoardCol - 1;
    if (cursor.x >= BoardCol) cursor.x = 0;
    if (cursor.y < 0) cursor.y = BoardRow - 1;
    if (cursor.y >= BoardRow) cursor.y = 0;
    GoToXY(cursor.x, cursor.y);
}

void startNewGame()
{
    GoToXY(MainMenuTextPositionX, MainMenuTextPositionY);
    cout << "Game Start！\n";
    delay(1000);
    system("cls");

    cursor.x = 0;
    cursor.y = 0;

    printGameFormat();

    while (gameRunning)
    {
        int keydown = getKey();

        if (keydown != 0)
        {
            if (keydown >= LeftArrowKey && keydown <= DownArrowKey) moveCursor(keydown);
        }
    }
}

void loadGame()
{
    int counter = 0;
    vector<string> filename;
    string cmd = "";

    storeSavedFilename(counter, filename);

    if (counter > 0)
    {
        while (atoi(cmd.c_str()) < 1 || atoi(cmd.c_str()) > counter)
        {
            cout << "請輸入編號(輸入 0 離開) : ";
            cin >> cmd;
            if (cmd[0] == '0' && cmd.length() == 1)
            {
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
    else
    {
        cout << "無存檔！";
        delay(3000);
        drawMainMenu();
    }
}

void mainMenuAction()
{
    SetConsoleTextAttribute(hConsole, InitColor);
    system("CLS");
    if (mainMenuPosition == 0)
    {
        startNewGame();
    }
    else if (mainMenuPosition == 1)
    {
        loadGame();
    }
    else if (mainMenuPosition == 2)
    {
        exit(0);
    }
    drawMainMenu();
}

int main()
{
    init();
    initCmdWindow();
    drawMainMenu();

    while (running)
    {
        int keydown = getKey();

        if (keydown != 0)
        {
            if (keydown == UpArrowKey || keydown == DownArrowKey)
            {
                moveMainMenu(keydown);
            }
            else if (keydown == EnterKey)
            {
                mainMenuAction();
            }
        }
    }
    return 0;
}