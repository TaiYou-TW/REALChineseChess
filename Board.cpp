#include "Board.h"

// default constructor
// create a 9*10 area that all chess are NULL_CHESS
ChessBoard::ChessBoard()
{
    area.clear();
    Chess emptyChess;
    area = BattleArea(9, vector<Chess>(10, emptyChess));
}

// set chess on board
void ChessBoard::setChess(const int32_t &uid, const int32_t &kind, const Coord &loc)
{
    area[loc.y][loc.x] = Chess(uid, kind, loc);
}
// draw
void ChessBoard::drawBoard(const BattleArea &board) const
{
}

void ChessBoard::undo()
{
}
void ChessBoard::redo()
{
}

// get chess ref
const Chess &ChessBoard::getChess(const Coord &loc)
{
    return area[loc.y][loc.x];
}