#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Chess.h"

using namespace std;

typedef vector<vector<Chess>> BattleArea;

class ChessBoard
{
public:
    ChessBoard();

    void setChess(const int32_t &uid, const int32_t &kind, const Coord &loc);
    Chess &getChess(const Coord &loc);
    void moveChess(Chess &c, const Coord &cursorLoc);

    void setTurn(const int32_t &t);
    const int32_t getTurn() const;

    void drawBoard(const BattleArea &board) const;
    void undo();
    void redo();

private:
    // A "2 dim vector" that store chess
    // Size = 9 * 10   (Definition in .Cpp)
    BattleArea area;
    int32_t turn;
};