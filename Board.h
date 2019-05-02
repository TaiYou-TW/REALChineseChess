#pragma once
#include "Chess.h"

using namespace std;

typedef vector<vector<Chess>> BattleArea;

class ChessBoard
{
public:
    ChessBoard(const string &fileName);

    const uint32_t getChessID(const Coord &location) const;
    const string getChessKind(const uint32_t &chessID) const;
    void drawBoard(const BattleArea &board) const;

    const void undo();
    const void redo();

private:
    // A "2 dim vector" that store chess
    // Size = 9 * 10   (Definition in .Cpp)
    BattleArea area;

    // Chess list
    vector<Chess> chess;
};