#pragma once
#define PLAYER_RED 1
#define PLAYER_BLACK 0
#define max_x 50
#define max_y 22

#include "ChessBoard.h"

using namespace std;

typedef vector<BattleArea> BattleHistory;
typedef vector<string> BattleReport;

class Game
{
public:
    Game();
    Game(const string &fileName);

    void saveFile(const string &fileName);
    void loadFile(const string &fileName);

    ChessBoard &getboard();

    const bool isCheckmate();
    const bool isCheck();

    vector<Coord> promptMovement(Coord);
    vector<Coord> promptCapture(Coord);

    void writeReport();
    void writeHistory(const BattleArea &oldArea);
    void setPlayer(const uint16_t&);
    const uint16_t playerNow() const;

    static void controll(const int32_t &xOffset, const int32_t &yOffSet);
    static void controll(const int32_t &specified);

private:
    // Store old battle area
    BattleHistory history;

    // Store battle report(text)
    BattleReport report;

    // player's identity
    uint16_t player;

    // Chess board
    ChessBoard board;

    // Controller's coord
    static Coord controller;
};