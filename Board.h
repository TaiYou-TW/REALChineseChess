#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Chess.h"

using namespace std;

typedef vector<vector<uint32_t>> BattleArea;
typedef struct
{
    uint32_t x;
    uint32_t y;
} Coord;

class ChessBoard
{
public:
    ChessBoard(const string &fileName);

    const uint32_t getChessID(const Coord &location) const;
    const string getChessName(const uint32_t &chessID) const;
    void drawBoard(const BattleArea &board) const;

    void undo();
    void redo();

    const uint16_t playerNow() const;

private:
    // A "2 dim vector" that store chess's unique ID
    // Size = 9 * 10   (Definition in .Cpp)
    BattleArea area;

    // Chess list
    vector<Chess> chess;
};