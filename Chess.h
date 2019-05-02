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

class Chess
{
public:
    Chess(const uint32_t &uid, const uint32_t &code);

    const void move();
    const void capture();

    void promptMovement(Coord *container) const;
    void promptCapture(Coord *container) const;

    const bool isAlive() const;

private:
    // A uniqueID
    // Same kind won't have same ID
    uint32_t uniqueID;

    // Which kind of chess
    // Code 99 stand for "null chess"
    uint32_t kindCode;

    bool alive;

    Coord preCoord;
    Coord oldCoord;
};