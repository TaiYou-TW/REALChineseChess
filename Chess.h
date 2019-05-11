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
    Chess(const int32_t &uid, const int32_t &kind, const Coord &loc);

    bool isMovable(const Coord &cursorLoc, const Coord &loc);
    void moveCoord(const Coord &cursorLoc);

    void promptMovement(Coord *container) const;
    void promptCapture(Coord *container) const;

    const int32_t getID() const;
    const int32_t getKind() const;
    const Coord getPrevCoord() const;
    const Coord getCurrCoord() const;

    Chess &operator=(const Chess &temp);

private:
    // A uniqueID
    // Same kind won't have same ID
    // ID -1 stand for "null chess"
    int32_t uniqueID;

    // Which kind of chess
    // Code -1 stand for "null chess"
    int32_t kindCode;

    Coord currCoord;
    Coord prevCoord;
};