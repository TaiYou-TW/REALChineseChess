#pragma once
#include <cstdint>
#include <string>
#include "Board.h"
#include "Chess.h"

using namespace std;

typedef vector<BattleArea> BattleHistory;
typedef vector<string> BattleReport;

class Game
{
public:
    Game();
    Game(const string &fileName);

    const void saveFile(const string &fileName) const;
    const void loadFile(const string &fileName);

    const bool isCheckmate() const;
    const bool isCheck() const;

    const void controll();
    const void writeReport();
    const uint16_t playerNow() const;

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
    Coord controller;
};