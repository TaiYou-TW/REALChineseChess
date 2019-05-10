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
    save.open(fileName);
    if(save.is_open())
    {   // uid start at 0 
        for(uint16_t row = 0, uid = 0; row < 10; row++)
        {
            for(uint16_t col = 0; col < 9; col++, uid++)
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
	return false;
}
const bool Game::isCheck() const
{
	return false;
}

void Game::controll()
{

}
void Game::writeReport()
{

}
const uint16_t Game::playerNow() const
{
    return player;
}