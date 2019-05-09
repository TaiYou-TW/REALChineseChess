#pragma once
#define NULL_CHESS -1

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
    uint32_t x;
    uint32_t y;
} Coord;

class Chess
{
public:
    Chess();
    Chess(const int32_t& uid, const int32_t& kind, const Coord& loc);

    void move(Coord cursorLoc);
    void capture(Coord cursorLoc);

    void promptMovement(Coord *container) const;
    void promptCapture(Coord *container) const;

    const int32_t getID() const;
    const int32_t getKind() const;
    const bool isAlive() const;

    Chess& operator =(const Chess& temp);
private:
    // A uniqueID
    // Same kind won't have same ID
    // ID -1 stand for "undefine chess"
    int32_t uniqueID;

    // Which kind of chess
    // Code -1 stand for "null chess"
    int32_t kindCode;

    bool alive;

    Coord currCoord;
    Coord prevCoord;
};