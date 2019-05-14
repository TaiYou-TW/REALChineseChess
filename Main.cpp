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
#define BlackColor 8
#define RedColor 12
#define BoardColor 240
#define BoardNumColor 253
#define HintColor 3

#define UpArrowKey 38
#define LeftArrowKey 37
#define RightArrowKey 39
#define DownArrowKey 40
#define EnterKey 13

#define MainMenuTextInitX 63
#define MainMenuTextInitY 12
#define BoardInitX 32
#define BoardInitY 2
#define WindowBottomY 29

#define BoardRow 10
#define BoardCol 9

using namespace std;
namespace fs = std::experimental::filesystem;

const string savePath = "./save";
const string mainMenuText[3] = {"¶}·s¹Cְ¸", "ֵ×¨ת¦sְֹ", "ֲק¶}¹Cְ¸"};
//const string BoardText[8] = {"¢°¢±¢²¢³¢´¢µ¢¶¢·¢¸", "¨®°¨¶H₪h±N₪h¶H°¨¨®", "¯¥", "¨ע", "§L", "¬¶", "¨®״X¬Û¥K«׃¥K¬Û״X¨®", "₪E₪K₪C₪»₪­¥|₪T₪G₪@" };
const string Board[] = {
    "שÝשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששß",
    "שר שÝשששששש¡@¾װ¡@×p¡@ֵד¡@¥Ü¡@שששששששß¡@¡@¢°¡@¢±¡@¢²¡@¢³¡@¢´¡@¢µ¡@¢¶¡@¢·¡@¢¸¡@¡@שÝשששששששששששששששששששששששששששששששששששששששששששששששששששששששß שר",
    "שר שר                        שר¡@¡@שÝשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששß    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x ¢@¢x¡‏ ¢x   ¢x   ¢x    שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר    ½ü¨ל¡@    ₪ט¡@₪U´ׁ     שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x ¡‏¢x¢@ ¢x   ¢x   ¢x    שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x    שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x    שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר     ·¡×e            ÷~¬ֹ       שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x    שר    שאשששששששששששששששששששששששששששששששששששששששששששששששששששששששג שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x   ¢x    שר    שר  Esc ¿ן³ז  < ®¬´ׁ  > ֱÙ­ל שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x ¢@¢x¡‏ ¢x   ¢x   ¢x    שר    שר      Enter   ¿ן¨ת´ׁ₪l     שר שר",
    "שר שר                        שר¡@¡@שר ¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w שר    שר                           שר שר",
    "שר שר                        שר¡@¡@שר   ¢x   ¢x   ¢x ¡‏¢x¢@ ¢x   ¢x   ¢x    שר    שר       ₪ט¦Vֱה±±¨מ´ו¼׀      שר שר",
    "שר שר                        שר¡@¡@שדשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששו    שר                           שר שר",
    "שר שדשששששששששששששששששששששששששששששששששששששששששששששששששו¡@¡@₪E¡@₪K¡@₪C¡@₪»¡@₪­¡@¥|¡@₪T¡@₪G¡@₪@    שדשששששששששששששששששששששששששששששששששששששששששששששששששששששששו שר",
    "שדשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששו"};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
bool running = true;
bool gameRunning = true;
bool holdChess = false;
int mainMenuPosition = 0;
Coord cursor;

void init()
{
    SetConsoleTextAttribute(hConsole, InitColor);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // system("chcp 65001");
    system("CHCP 950"); // BIG-5
}

void GoToXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;

    if (!SetConsoleCursorPosition(hConsole, coord))
    {
        cout << "²¾°Ê´ו¼׀error";
    }
}

void delay(int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

DWORD getKey()
{ // get user keydown
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
    cout << "¥״«e¦sְֹ¡G\n";
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
{ // set cmd window's width and height
    HWND console = GetConsoleWindow();
    RECT r;

    GetWindowRect(console, &r);

    MoveWindow(console, 100, 100, width, height, TRUE);
}

void colorBoard(ChessBoard obj)
{ // color Board
    int start_x = 43;
    int end_x = 74;
    int start_y = BoardInitY;
    int end_y = BoardInitY + BoardRow;
    SetConsoleTextAttribute(hConsole, BoardNumColor);
    GoToXY(BoardInitX, BoardInitY - 1);
    cout << Board[1][start_x - 2] << Board[1][start_x - 1];
    for (int i = start_x; i <= end_x; i += 2)
    {
        for (int j = i; j < i + 2; j++)
            cout << Board[1][j];
    }
    GoToXY(BoardInitX, BoardInitY);
    for (int i = start_x - 8; i <= end_x + 28; i += 2)
    {
        for (int j = i; j < i + 2; j++)
            cout << Board[2][j];
    }
    Coord coo;
    for (int i = start_y + 1, row = 0; i <= end_y; i++, row++)
    {
        GoToXY(BoardInitX, i);
        row = 0;
        for (int j = start_x, col = 0; j <= end_x; j++, col++)
        {
            coo.x = row;
            coo.y = col;
            if (obj.getChess(coo).getKind() == -1)
            {
                SetConsoleTextAttribute(hConsole, BoardColor);
            }
            else if (obj.getChess(coo).getKind() >= 1 && obj.getChess(coo).getKind() <= 7) // black
            {
                SetConsoleTextAttribute(hConsole, BlackColor);
            }
            else if (obj.getChess(coo).getKind() >= 8 && obj.getChess(coo).getKind() <= 14) // red
            {
                SetConsoleTextAttribute(hConsole, RedColor);
            }
            for (int k = j; k < j + 2; k++)
                cout << Board[i][k];
        }
    }
    /*for (int i = start_x, col = 0; i <= end_x; i += 2, col++)
	{
		for (int j = start_y, row = 0; j <= end_y; j++, row++) {
			coo.x = row;
			coo.y = col;
			if (obj.getChess(coo).getKind() == -1) 
			{
				SetConsoleTextAttribute(hConsole, BoardColor);
			}
			else if (obj.getChess(coo).getKind() >= 1 && obj.getChess(coo).getKind() <= 7) // black
			{
				SetConsoleTextAttribute(hConsole, BlackColor);
			}
			else if (obj.getChess(coo).getKind() >= 8 && obj.getChess(coo).getKind() <= 14) // red
			{
				SetConsoleTextAttribute(hConsole, RedColor);
			}
			for (int k = i; k < i + 2; k++)
				cout << Board[j][j];
		}
	}*/

    GoToXY(BoardInitX, BoardInitY);
}

void colorMainMenuCursor()
{ // color menu's cursor
    SetConsoleTextAttribute(hConsole, MainMenuLineColor);
    for (int i = MainMenuTextInitY, j = 0; i <= MainMenuTextInitY + 4; i += 2, j++)
    {
        GoToXY(MainMenuTextInitX, i);
        cout << mainMenuText[j];
    }

    SetConsoleTextAttribute(hConsole, MainMenuChoosenColor);
    GoToXY(MainMenuTextInitX, MainMenuTextInitY + mainMenuPosition * 2);
    cout << mainMenuText[mainMenuPosition];
    GoToXY(0, WindowBottomY);
}

void drawMainMenu()
{
    int index = mainMenuPosition;
    int space = 30;
    int blank_row = 11;

    system("CLS");
    SetConsoleTextAttribute(hConsole, MainMenuLineColor);

    for (int i = 0; i < blank_row; i++)
        cout << "\n";

    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢z¢w¢w¢w¢w¢w¢{\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢x " << mainMenuText[0] << " ¢x\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢u¢w¢w¢w¢w¢w¢t\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢x " << mainMenuText[1] << " ¢x\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢u¢w¢w¢w¢w¢w¢t\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢x " << mainMenuText[2] << " ¢x\n";
    for (int i = 0; i < space; i++)
        cout << "¡@";

    cout << "¢|¢w¢w¢w¢w¢w¢}\n";
    for (int i = 0; i < blank_row; i++)
        cout << "\n";
    colorMainMenuCursor();
}

void moveMainMenu(int keydown)
{ // move menu's cursor
    if (keydown == UpArrowKey)
    {
        mainMenuPosition--;
    }
    if (keydown == DownArrowKey)
    {
        mainMenuPosition++;
    }
    if (mainMenuPosition > 2)
        mainMenuPosition = 0;
    if (mainMenuPosition < 0)
        mainMenuPosition = 2;
    colorMainMenuCursor();
}

void printGameFormat()
{
    /*ifstream in;
    in.open("./Format/init.ya");
    string line;
    while (getline(in, line))
    {
        cout << line << "\n";
    }*/
    for (int i = 0; i < 23; i++)
        cout << Board[i] << "\n";
}

void moveCursor(int keydown)
{
    // int max_x = BoardCol * 2 + BoardInitX;
    // int max_y = BoardRow * 2 + BoardInitY;
    if (keydown == UpArrowKey)
    {
        // cursor.y--;
        Game::controll(0, -1);
    }
    else if (keydown == DownArrowKey)
    {
        // cursor.y++;
        Game::controll(0, 1);
    }
    else if (keydown == LeftArrowKey)
    {
        // cursor.x--;
        Game::controll(-1, 0);
    }
    else if (keydown == RightArrowKey)
    {
        // cursor.x++;
        Game::controll(1, 0);
    }
    if (cursor.x < BoardInitX)
        // cursor.x = max_x - 1;
        Game::controll(max_x - 1);
    if (cursor.x >= max_x)
        // cursor.x = BoardInitX;
        Game::controll(BoardInitX);
    if (cursor.y < BoardInitY)
        // cursor.y = max_y - 1;
        Game::controll(max_y - 1);
    if (cursor.y >= max_y)
        // cursor.y = BoardInitY;
        Game::controll(BoardInitY);
    GoToXY(cursor.x + BoardInitX - 1, cursor.y + BoardInitY - 1);
}

// main gaming process
void startNewGame()
{
    GoToXY(MainMenuTextInitX, MainMenuTextInitY);
    cout << "Game Start¡I\n";
    Game newGame;
    ChessBoard &board = newGame.getboard();
    delay(1000);
    system("cls");

    cursor.x = 0;
    cursor.y = 0;

    printGameFormat();
    colorBoard(board);

    while (gameRunning)
    {
        int keydown = getKey();
        Coord select;
        if (keydown != 0)
        {
            // move the cursor by arrow key
            if (keydown >= LeftArrowKey && keydown <= DownArrowKey)
                moveCursor(keydown);
            // has no chess -> select
            // TODO: complete the select method
            else if (keydown == EnterKey && !holdChess)
            {
                // select a location
                // select.x = cursor.x;
                // select.y = cursor.y;
                holdChess = true;
            }
            // has chess -> move
            else if (keydown == EnterKey && holdChess)
            {
                // move the chess
                Chess &c = board.getChess(select);
             //   board.moveChess(c, /*another coord*/);
                holdChess = false;
                // store board's old status
                newGame.writeHistory(board.getArea());
            }
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
            cout << "½׀¿י₪J½s¸¹(¿י₪J 0 ֲק¶}) : ";
            cin >> cmd;
            if (cmd[0] == '0' && cmd.length() == 1)
            {
                return;
            }
        }

        system("cls");
        cout << "¸ü₪J \"" << filename[atoi(cmd.c_str()) - 1] << "\" ₪₪ ...... \n";
        delay(3000);
        cout << "¨S¦³₪U₪@¨B£{";
        delay(1000);
        Game save(filename[atoi(cmd.c_str()) - 1]);
    }
    else
    {
        cout << "µL¦sְֹ¡I";
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

void testColor()
{
    for (int i = 1; i <= 255; i++)
    {
        SetConsoleTextAttribute(hConsole, i);
        cout << i << " : weqweqweqwe\n";
    }
}
int main()
{
    init();
    initCmdWindow();
    drawMainMenu();
    //testColor();
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