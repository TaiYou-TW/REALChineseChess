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
void ChessBoard::setChess(const int32_t& uid, const int32_t& kind, const Coord& loc)
{
    area[loc.y][loc.x] = Chess(uid, kind, loc);
}
// draw
void ChessBoard::drawBoard(const BattleArea& board) const
{

}

void ChessBoard::undo()
{

}
void ChessBoard::redo()
{
    
}

// get chessID
const int32_t ChessBoard::getChessID(const Coord& loc) const
{
    return area[loc.y][loc.x].getID();
}
// get chessKind (By loc)
const int32_t ChessBoard::getChessKind(const Coord& loc) const
{
    return area[loc.y][loc.x].getKind();
}
// get chessKind (By uid)
const int32_t ChessBoard::getChessKind(const int32_t& uid) const
{
    
}