#pragma once
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
    uint32_t x;
    uint32_t y;
} Coord;

class ChessBoard
{
public:
    ChessBoard(const string &fileName);
    const void saveFile(const string &fileName);
    const void loadFile(const string &fileName);

    const uint32_t getChessID(const Coord &location);
    const void drawBoard();

    const bool isCheckmate();
    const bool isCheck();

private:
    // 9 * 10
    // Definition in .Cpp
    vector<Coord> content;
};