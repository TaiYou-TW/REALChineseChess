#include "Game.h"
#include <fstream>

using namespace std;

// default constructor
// clear all record
// player = RED
// controller's coord = (0, 0)
Game::Game(){
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
Game::Game(const string& fileName)
{
    // load history / report / player / board
    loadFile(fileName);
    // set controller's coord
    controller.x = 0;
    controller.y = 0;
}

void Game::saveFile(const string& fileName) const
{

}

void Game::loadFile(const string& fileName)
{
    // history.push_back(<something>);
    // report.push_back(<something>);

    // load file and set chess
    ifstream save;
    save.open(""); // TODO: which file?
    if(save.is_open())
    {   // uid start at 0 
        for(uint16_t row = 0, uid = 0; row < 10; row++, uid++)
        {
            for(uint16_t col = 0; col < 9; col++) 
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

const bool Game::isCheckmate() const
{

}
const bool Game::isCheck() const
{

}

void Game::controll()
{

}
void Game::writeReport()
{
	int kind=board.getChessKind(controller);
	string chineseKind, text, kindofchinese = "將士象車馬包卒帥仕相車傌炮兵", numberChinese[2] = { "１２３４５６７８９","九八七六五四三二一" }, verbsChinese="平進退前二三四後";
	Coord pre=board.getPrevCoord(controller),curr=controller;

	chineseKind = kindofchinese[(board.getChessKind(controller) - 1) * 2] + kindofchinese[(board.getChessKind(controller) - 1) * 2 + 1];
	short duplicate = 0;
	
	if (player==1)
	{
		for (int i = 0; i < 9; i++)
		{

		}
		text = "紅：";
		if (pre.x == curr.x)
		{
			text += chineseKind + numberChinese[1][(pre.x - 1) * 2] + numberChinese[1][(pre.x - 1) * 2 + 1];
			if (curr.y < pre.y)
			{
				text += verbsChinese[2] + verbsChinese[3] + numberChinese[1][(pre.y - curr.y - 1) * 2] + numberChinese[1][(pre.y - curr.y - 1) * 2 + 1];
			}
			else
			{
				text += verbsChinese[4] + verbsChinese[5] + numberChinese[1][(curr.y - pre.y - 1) * 2] + numberChinese[1][(curr.y - pre.y - 1) * 2 + 1];
			}
		}
		else if(pre.y==curr.y)
		{
			text += chineseKind + numberChinese[1][(pre.x - 1) * 2] + numberChinese[1][(pre.x - 1) * 2 + 1] + verbsChinese[0] + verbsChinese[1] + numberChinese[1][(curr.x - 1) * 2] + numberChinese[1][(curr.x - 1) * 2 + 1];
		}
		else 
		{
			text += chineseKind + numberChinese[1][(pre.x - 1) * 2] + numberChinese[1][(pre.x - 1) * 2 + 1];
			if (curr.y < pre.y)
			{
				text += verbsChinese[2] + verbsChinese[3] + numberChinese[1][(curr.x - 1) * 2] + numberChinese[1][(curr.x - 1) * 2 + 1];
			}
			else
			{
				text += verbsChinese[4] + verbsChinese[5] + numberChinese[1][(curr.x - 1) * 2] + numberChinese[1][(curr.x - 1) * 2 + 1];
			}
		}
	}
	else 
	{
		text = "黑：";
		if (pre.x == curr.x)
		{
			text += chineseKind + numberChinese[0][(pre.x - 1) * 2] + numberChinese[0][(pre.x - 1) * 2 + 1];
			if (curr.y < pre.y)
			{
				text += verbsChinese[4] + verbsChinese[5] + numberChinese[0][(pre.y - curr.y - 1) * 2] + numberChinese[0][(pre.y - curr.y - 1) * 2 + 1];
			}
			else
			{
				text += verbsChinese[2] + verbsChinese[3] + numberChinese[0][(curr.y - pre.y - 1) * 2] + numberChinese[0][(curr.y - pre.y - 1) * 2 + 1];
			}
		}
		else if (pre.y == curr.y)
		{
			text += chineseKind + numberChinese[0][(pre.x - 1) * 2] + numberChinese[0][(pre.x - 1) * 2 + 1] + verbsChinese[0] + verbsChinese[1] + numberChinese[0][(curr.x - 1) * 2] + numberChinese[0][(curr.x - 1) * 2 + 1];
		}
		else
		{
			text += chineseKind + numberChinese[0][(pre.x - 1) * 2] + numberChinese[0][(pre.x - 1) * 2 + 1];
			if (curr.y < pre.y)
			{
				text += verbsChinese[4] + verbsChinese[5] + numberChinese[0][(curr.x - 1) * 2] + numberChinese[0][(curr.x - 1) * 2 + 1];
			}
			else
			{
				text += verbsChinese[2] + verbsChinese[3] + numberChinese[0][(curr.x - 1) * 2] + numberChinese[0][(curr.x - 1) * 2 + 1];
			}
		}
	}
	report.push_back(text);
}
const uint16_t Game::playerNow() const
{
    return player;
}