#pragma once
#include "Chess.h"

using namespace std;

typedef vector<vector<Chess>> BattleArea;

class ChessBoard
{
public:
    ChessBoard();
    
    void setChess(const int32_t& uid, const int32_t& kind, const Coord& loc);
    void drawBoard(const BattleArea &board) const;

    void undo();
    void redo();

    const int32_t getChessID(const Coord& loc) const;
    const int32_t getChessKind(const Coord& loc) const;
    const int32_t getChessKind(const int32_t &uid) const;
    
private:
    // A "2 dim vector" that store chess
    // Size = 9 * 10   (Definition in .Cpp)
    BattleArea area;
};