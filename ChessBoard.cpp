#include "ChessBoard.h"

// default constructor
// create a 9*10 area that all chess are NULL_CHESS
ChessBoard::ChessBoard()
{
    area.clear();
    Chess emptyChess;
    area = BattleArea(9, vector<Chess>(10, emptyChess));
    turn = 0;
}

// set chess on board
void ChessBoard::setChess(const int32_t &uid, const int32_t &kind, const Coord &loc)
{
    area[loc.y][loc.x] = Chess(uid, kind, loc);
}
// get chess ref
Chess &ChessBoard::getChess(const Coord &loc) { return area[loc.y][loc.x]; }
void ChessBoard::moveChess(Chess &c, const Coord &cursorLoc)
{
    if (c.isMovable(cursorLoc, c.getCurrCoord()))
    {
        // replace the chess on cursor loc
        area[cursorLoc.y][cursorLoc.x] = c;

        // clear current loc
        Chess cleaner;
        area[c.getCurrCoord().y][c.getCurrCoord().x] = cleaner;

        // update the loc
        c.moveCoord(cursorLoc);
    }
}

// set turn
void ChessBoard::setTurn(const int32_t &t) { turn = t; }
// get turn
const int32_t ChessBoard::getTurn() const { return turn; }

// draw
void ChessBoard::drawBoard(const BattleArea &board) const {}
void ChessBoard::undo() {}
void ChessBoard::redo() {}
