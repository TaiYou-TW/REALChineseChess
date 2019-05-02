#pragma once
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<uint32_t>> BattleArea;
typedef vector<BattleArea> BattleHistory;
typedef vector<string> BattleStatus;
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
    const string getChessName(const uint32_t &chessID);
    const void drawBoard();

    const bool isCheckmate();
    const bool isCheck();

    void recovery();
    void unrecovery();

private:
    // A "2 dim vector" that store chess's unique ID
    // Size = 9 * 10   (Definition in .Cpp)
    BattleArea area;

    // Store battle status
    BattleHistory history;
};