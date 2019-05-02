#pragma once
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<uint32_t>> Coord;

class ChessBoard
{
public:
    ChessBoard(const string &);
    const void saveFile();
    const void loadFile();
    const void drawVoard();
    const uint32_t getChessID(const uint32_t &, const uint32_t &);
    const bool isCheckmate();
    const bool isCheck();

private:
    // Coord content(9, vector<uint32_t>(10, 0));
};