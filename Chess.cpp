#include "Chess.h"
#include "ChessBoard.h"

// default constructor (NULL_CHESS)
// uid = -1
// kindCode = -1
// both coord = (0, 0)
Chess::Chess()
{
    uniqueID = NULL_CHESS;
    kindCode = NULL_CHESS;
    currCoord.x = 0;
    currCoord.y = 0;
    prevCoord.x = 0;
    prevCoord.y = 0;
}

// create chess by reading file
// uid = uid
// kindCode = kind
// currCoord = loc
// TODO: prevCoord = <read from file>
Chess::Chess(const int32_t &uid, const int32_t &kind, const Coord &loc)
{
    uniqueID = uid;
    kindCode = kind;
    currCoord.x = loc.x;
    currCoord.y = loc.y;
    // TODO: prevCoord
    // prevCoord.x = <somthing>;
    // prevCoord.y = <somthing>;
}

// TODO: horse / elephant / Soldier 's rules
bool Chess::isMovable(const Coord &cursorLoc, const Coord &loc) {}
void Chess::moveCoord(const Coord &cursorLoc)
{
    // store current coord
    prevCoord.x = currCoord.x;
    prevCoord.y = currCoord.y;
    // move to cursor's location
    currCoord.x = cursorLoc.x;
    currCoord.y = cursorLoc.y;
}

void Chess::promptCapture(Coord *container) const {}
void Chess::promptMovement(Coord *container) const {}

const int32_t Chess::getID() const { return uniqueID; }
const int32_t Chess::getKind() const { return kindCode; }
const Coord Chess::getPrevCoord() const { return prevCoord; }
const Coord Chess::getCurrCoord() const { return currCoord; }

Chess &Chess::operator=(const Chess &temp)
{
    this->uniqueID = temp.uniqueID;
    this->kindCode = temp.kindCode;

    this->currCoord.x = temp.currCoord.x;
    this->currCoord.y = temp.currCoord.y;
    this->prevCoord.x = temp.prevCoord.x;
    this->prevCoord.y = temp.prevCoord.y;
    return *this;
}