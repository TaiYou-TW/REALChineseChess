#include "Game.h"
#include <fstream>

using namespace std;

// default constructor
// clear all record
// player = RED
// controller's coord = (0, 0)
Game::Game()
{
    history.clear();
    report.clear();
    player = PLAYER_RED;
    controller.x = 0;
    controller.y = 0;
}

// continue previous game
// TODO: old record
// player = last character in file
// controller's coord = (0, 0)
Game::Game(const string &fileName)
{
    // load history / report / player / board
    loadFile(fileName);
    // set controller's coord
    controller.x = 0;
    controller.y = 0;
}

void Game::saveFile(const string &fileName) const {}

void Game::loadFile(const string &fileName)
{
    // history.push_back(<something>);
    // report.push_back(<something>);

    // load file and set chess
    ifstream save;
    save.open(fileName);
    if (save.is_open())
    {  // uid start at 0
        for (uint16_t row = 0, uid = 0; row < 10; row++)
        {
            for (uint16_t col = 0; col < 9; col++, uid++)
            {
                // set data
                Coord currLoc;
                currLoc.x = col;
                currLoc.y = row;
                int32_t kind;
                save >> kind;
                // create chess
                board.setChess(uid, kind, currLoc);
            }
        }
        // set player
        save >> player;
    }
}

const bool Game::isCheckmate() 
{ 
	return false; 
}
ChessBoard& Game::getboard()
{
	return board;
}
const bool Game::isCheck() 
{ 
	Coord general_coord;
	//check player_red is been check
	if (player == PLAYER_RED)
	{
		for (int i = 3, flag = 0; i <= 5; i++)
		{
			for (int j = 7; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				Chess &general = board.getChess(temp);
				if (general.getKind() == 1)
				{
					general_coord.x = i;
					general_coord.y = j;
					flag = 1;
					break;
				}
				if (flag == 1)
				{
					break;
				}
			}
		}
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				if (board.isMovable(general_coord, temp,PLAYER_BLACK) == true)
				{
					return 1;
				}
			}
		}
	}
	//check player_black is been check
	else if(player==PLAYER_BLACK)
	{
		for (int i = 3,flag=0; i <= 5; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				Chess &general = board.getChess(temp);
				if (general.getKind() == 1)
				{
					general_coord.x = i;
					general_coord.y = j;
					flag = 1;
					break;
				}
				if (flag == 1)
				{
					break;
				}
			}
		}
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				if (board.isMovable(general_coord, temp, PLAYER_RED) == true)
				{
					return 1;
				}
			}
		}
	}
	return false;
}
vector<Coord> Game::promptCapture(const Coord curr)
{
	vector<Coord> Capture;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() != -1 && board.isMovable(temp, curr, player) == true && board.getChess(curr).getKind() != -1)
			{
				Capture.push_back(temp);
			}
		}
	}
	return Capture;
}
vector<Coord> Game::promptMovement(const Coord curr) 
{
	vector<Coord> Movement;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() == -1 && board.isMovable(temp, curr, player) == true && board.getChess(curr).getKind() != -1)
			{
				Movement.push_back(temp);
			}
		}
	}
	return Movement;
}

void Game::controll() {}
void Game::writeReport()
{
	int kind = board.getChess(controller).getKind();
	Coord pre = board.getChess(controller).getPrevCoord(), curr = controller;
	// define string
	const static string duplicateofChinese[4] = { "前後", "前中後", "前二三後",
												 "前二三四後" };
	const static string kindofChinese = "將士象車馬包卒帥仕相車傌炮兵";
	const static string numberChinese[2] = { "１２３４５６７８９", "九八七六五四三二一" };
	const static string verbofChinese = "平進退";
	string text;
	// Set the first word
	text = kindofChinese[(kind - 1) * 2] + kindofChinese[(kind - 1) * 2 + 1];
	// check the how many same kind of chess on the same x INDEX [0](how many) [1]this
	// chess index [2] the bool of
	short duplicate[3] = { 0, 0, 0 };
	// check duplicate and set second word
	for (int i = 0; i <= 9; i++)
	{
		Coord checkCoord;
		checkCoord.x = pre.x;
		checkCoord.y = i;
		const Chess &checkChess = board.getChess(checkCoord);
		if (checkChess.getKind() == kind)
		{
			duplicate[0] += 1;
		}
		else if (pre.x == checkCoord.x && pre.y == checkCoord.y)
		{
			duplicate[0] += 1;
			duplicate[1] = duplicate[0];
		}
		if (duplicate[0] > 1 && i == 9)
		{
			duplicate[2] = 1;
			if (player == 1)
			{
				text += duplicateofChinese[duplicate[0] - 2][(duplicate[1] - 1) * 2] +
					duplicateofChinese[duplicate[0] - 2][(duplicate[1] - 1) * 2 + 1];
			}
			else
			{
				text += duplicateofChinese[duplicate[0] - 2]
					[(duplicate[0] - duplicate[1]) * 2] +
					duplicateofChinese[duplicate[0] - 2]
					[(duplicate[0] - duplicate[1]) * 2 + 1];
			}
		}
		else if (i == 9)
		{
			text += numberChinese[player][(pre.x - 1) * 2] +
				numberChinese[player][(pre.x - 1) * 2 + 1];
		}
	}
	if (player == 1)
	{
		text = "紅：" + text;
		if (pre.x == curr.x)
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[2] + verbofChinese[3] +
					numberChinese[1][(pre.y - curr.y - 1) * 2] +
					numberChinese[1][(pre.y - curr.y - 1) * 2 + 1];
			}
			else
			{
				text += verbofChinese[4] + verbofChinese[5] +
					numberChinese[1][(curr.y - pre.y - 1) * 2] +
					numberChinese[1][(curr.y - pre.y - 1) * 2 + 1];
			}
		}
		else if (pre.y == curr.y)
		{
			text += verbofChinese[0] + verbofChinese[1] +
				numberChinese[1][(curr.x - 1) * 2] +
				numberChinese[1][(curr.x - 1) * 2 + 1];
		}
		else
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[2] + verbofChinese[3] +
					numberChinese[1][(curr.x - 1) * 2] +
					numberChinese[1][(curr.x - 1) * 2 + 1];
			}
			else
			{
				text += verbofChinese[4] + verbofChinese[5] +
					numberChinese[1][(curr.x - 1) * 2] +
					numberChinese[1][(curr.x - 1) * 2 + 1];
			}
		}
	}
	else
	{
		text = "黑：" + text;
		if (pre.x == curr.x)
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[4] + verbofChinese[5] +
					numberChinese[0][(pre.y - curr.y - 1) * 2] +
					numberChinese[0][(pre.y - curr.y - 1) * 2 + 1];
			}
			else
			{
				text += verbofChinese[2] + verbofChinese[3] +
					numberChinese[0][(curr.y - pre.y - 1) * 2] +
					numberChinese[0][(curr.y - pre.y - 1) * 2 + 1];
			}
		}
		else if (pre.y == curr.y)
		{
			text += verbofChinese[0] + verbofChinese[1] +
				numberChinese[0][(curr.x - 1) * 2] +
				numberChinese[0][(curr.x - 1) * 2 + 1];
		}
		else
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[4] + verbofChinese[5] +
					numberChinese[0][(curr.x - 1) * 2] +
					numberChinese[0][(curr.x - 1) * 2 + 1];
			}
			else
			{
				text += verbofChinese[2] + verbofChinese[3] +
					numberChinese[0][(curr.x - 1) * 2] +
					numberChinese[0][(curr.x - 1) * 2 + 1];
			}
		}
	}
	//write report
	if (board.getTurn() > report.size())
	{
		report.push_back(text);
	}
	else
	{
		report[board.getTurn()-1]=text;
	}
}
const uint16_t Game::playerNow() const { return player; }