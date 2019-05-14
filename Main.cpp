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

#define MainMenuTextInitX 55
#define MainMenuTextInitY 12
#define BoardInitX 32
#define BoardInitY 2
#define WindowBottomY 29

#define BoardRow 10
#define BoardCol 9

using namespace std;
namespace fs = std::experimental::filesystem;

const string savePath = "./save";
const string mainMenuText[3] = {"╢}╖s╣C└╕", "┼ки·жs└╔", "┬ў╢}╣C└╕"};
//const string BoardText[8] = {"в░в▒в▓в│в┤в╡в╢в╖в╕", "ио░и╢Hдh▒Nдh╢H░иио", "пе", "иЄ", "зL", "м╢", "ио╪Xм█еKл╙еKм█╪Xио", "дEдKдCд╗дне|дTдGд@" };
const string Board[] = {
    "∙▌вдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙▀",
    "∙° ∙▌вдвдвдб@╛╘б@кpб@┼уб@е▄б@вдвдвд∙▀б@б@в░б@в▒б@в▓б@в│б@в┤б@в╡б@в╢б@в╖б@в╕б@б@∙▌вдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙▀ ∙°",
    "∙° ∙°                        ∙°б@б@∙▌вдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙▀    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx в@вxб■ вx   вx   вx    ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°    ╜№иьб@    дшб@дU┤╤     ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx б■вxв@ вx   вx   вx    ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx   вx   вx   вx   вx    ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx   вx   вx   вx   вx    ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвrвwвwвwвrвwвwвwвrвwвwвwвrвwвwвwвrвwвwвwвrвwвwвwвrвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°     ╖бкe            ║~м╔       ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвsвwвwвwвsвwвwвwвsвwвwвwвsвwвwвwвsвwвwвwвsвwвwвwвsвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx   вx   вx   вx   вx    ∙°    ∙рвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙т ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx   вx   вx   вx   вx    ∙°    ∙°  Esc ┐я│ц  < ом┤╤  > ┴┘нь ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx в@вxб■ вx   вx   вx    ∙°    ∙°      Enter   ┐яи·┤╤дl     ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙° вwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвwвqвwвwвw ∙°    ∙°                           ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙°   вx   вx   вx б■вxв@ вx   вx   вx    ∙°    ∙°       дшжV┴ф▒▒ию┤х╝╨      ∙° ∙°",
    "∙° ∙°                        ∙°б@б@∙увдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙х    ∙°                           ∙° ∙°",
    "∙° ∙увдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙хб@б@дEб@дKб@дCб@д╗б@днб@е|б@дTб@дGб@д@    ∙увдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙х ∙°",
    "∙увдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвдвд∙х"};

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
    system("CHCP 950"); // BIG-5
}

void GoToXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;

    if (!SetConsoleCursorPosition(hConsole, coord))
    {
        cout << "▓╛░╩┤х╝╨error";
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
    cout << "е╪лeжs└╔бG\n";
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
    int space = 26;
    int blank_row = 11;

    system("CLS");
    SetConsoleTextAttribute(hConsole, MainMenuLineColor);

    for (int i = 0; i < blank_row; i++)
        cout << "\n";

    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вzвwвwвwвwвwвwвwвwвwвwвwвwв{\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вxб@" << mainMenuText[0] << "б@вx\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вuвwвwвwвwвwвwвwвwвwвwвwвwвt\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вxб@" << mainMenuText[1] << "б@вx\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вuвwвwвwвwвwвwвwвwвwвwвwвwвt\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "вxб@" << mainMenuText[2] << "б@вx\n";
    for (int i = 0; i < space; i++)
        cout << "б@";

    cout << "в|вwвwвwвwвwвwвwвwвwвwвwвwв}\n";
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

void startNewGame()
{
    GoToXY(MainMenuTextInitX, MainMenuTextInitY);
    cout << "Game StartбI\n";
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

        if (keydown != 0)
        {
            if (keydown >= LeftArrowKey && keydown <= DownArrowKey)
                moveCursor(keydown);
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
            cout << "╜╨┐щдJ╜s╕╣(┐щдJ 0 ┬ў╢}) : ";
            cin >> cmd;
            if (cmd[0] == '0' && cmd.length() == 1)
            {
                return;
            }
        }

        system("cls");
        cout << "╕№дJ \"" << filename[atoi(cmd.c_str()) - 1] << "\" дд ...... \n";
        delay(3000);
        cout << "иSж│дUд@иBг{";
        delay(1000);
        Game save(filename[atoi(cmd.c_str()) - 1]);
    }
    else
    {
        cout << "╡Lжs└╔бI";
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