#include "Chess.h"

// default constructor
// uid = -1
// kindCode = -1
// alive = false
// both coord = (0, 0)
Chess::Chess()
{
    uniqueID = NULL_CHESS;
    kindCode = NULL_CHESS;
    alive = false;
    currCoord.x = 0;
    currCoord.y = 0;
    prevCoord.x = 0;
    prevCoord.y = 0;
}

// create chess by reading file
// uid = uid
// kindCode = kind
// alive = true (if kind != NULL_CHESS)
// currCoord = loc
// TODO: prevCoord = <read from file>
Chess::Chess(const int32_t& uid, const int32_t& kind, const Coord& loc)
{
    uniqueID = uid;
    kindCode = kind;
    alive = kind != NULL_CHESS;
    currCoord.x = loc.x;
    currCoord.y = loc.y;
    // TODO: prevCoord
    // prevCoord.x = <somthing>;
    // prevCoord.y = <somthing>;
}

void Chess::move(Coord cursorLoc)
{
	currCoord.x = cursorLoc.x;
	currCoord.y = cursorLoc.y;
}
void Chess::capture(Coord cursorLoc)
{
	currCoord.x = cursorLoc.x;
	currCoord.y = cursorLoc.y;
}

void Chess::promptCapture(Coord* container) const
{

}
void Chess::promptMovement(Coord* container) const
{

}

const int32_t Chess::getID() const
{
    return uniqueID;
}
const int32_t Chess::getKind() const
{
    return kindCode;
}
const bool Chess::isAlive() const
{
    return alive;
}

Chess& Chess::operator =(const Chess& temp)
{
    this -> uniqueID = temp.uniqueID;
    this -> kindCode = temp.kindCode;

    this -> alive = temp.alive;
    
    this -> currCoord.x = temp.currCoord.x;
    this -> currCoord.y = temp.currCoord.y;
    this -> prevCoord.x = temp.prevCoord.x;
    this -> prevCoord.y = temp.prevCoord.y;
    return *this;
}