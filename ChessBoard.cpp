#include "ChessBoard.h"
#include <cmath>
// default constructor
// create a 9*10 area that all chess are NULL_CHESS
ChessBoard::ChessBoard()
{
	area.clear();
	Chess emptyChess;
	area = BattleArea(10, vector<Chess>(9, emptyChess));
	turn = 0;
}
// TODO: horse / elephant / Soldier 's rules and all rule
// before -> chess's current loc  after -> cursor's loc
bool ChessBoard::isMovable(const Coord &aftercod, const Coord &beforecod, const int player)
{
	Coord before = beforecod;
	Coord after = aftercod;
	if (player == 0) // PLAYER_BLACK
	{
		switch (area[before.y][before.x].getKind()) // which kind of chess
		{
		case 1: // black general
			if (after.x <= 5 && after.x >= 3 && after.y <= 2 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) == 1)
				{
					return true;
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 0)
				{
					return true;
				}
			}
			if (before.x == after.x && after.y >= 7 && after.y <= 9)
			{
				for (int hasgeneral = 0, i = 0; i <= 9; i++)
				{
					if (area[i][before.x].getKind() == 8)
					{
						hasgeneral += 1;
					}
					else if (area[i][before.x].getKind() != -1)
					{
						break;
					}
					if (i == 9 && hasgeneral == 1)
					{
						return true;
					}
				}
			}
			return false;
			break;
		case 2: // black advisor
			if (after.x <= 5 && after.x >= 3 && after.y <= 2 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 1)
				{
					return true;
				}
			}
			return false;
			break;
		case 3: // black elephant
			if (after.x <= 8 && after.x >= 0 && after.y <= 4 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 2 && area[(after.y + before.y) / 2][(before.x + after.x) / 2].getKind() == -1)
				{
					return true;
				}
			}
			return false;
			break;
		case 4: // black chariot
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
				{
					if (before.y < after.y)
					{
						for (Coord i = before; i.y < after.y; i.y++)
						{
							if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
							{
								return false;
							}
						}
					}
					else
					{
						for (Coord i = before; i.y > after.y; i.y--)
						{
							if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
							{
								return false;
							}
						}
					}
					return true;
				}
				else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
				{
					if (before.x < after.x)
					{
						for (Coord i = before; i.x < after.x; i.x++)
						{
							if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
							{
								return false;
							}
						}
					}
					else
					{
						for (Coord i = before; i.x > after.x; i.x--)
						{
							if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
							{
								return false;
							}
						}
					}
					return true;
				}
			}
			return false;
			break;
		case 5: // black horse
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 1)
				{
					if (before.x < after.x&&before.x != 8)
					{
						if (area[before.y][before.x+1].getKind() == -1)
						{
							return true;
						}
					}
					else if (before.x > after.x&&before.x != 0)
					{
						if (area[before.y ][before.x-1].getKind() == -1)
						{
							return true;
						}
					}
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 2)
				{
					if (before.y < after.y&&before.y != 9)
					{
						if (area[before.y+1][before.x].getKind() == -1)
						{
							return true;
						}
					}
					else if (before.y > after.y&&before.y != 0)
					{
						if (area[before.y-1][before.x].getKind() == -1)
						{
							return true;
						}
					}
				}
				return false;
			}
			return false;
			break;
		case 6: // black cannon
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0)
			{
				if (area[after.y][after.x].getKind() == -1) //move
				{
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									return false;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									return false;
								}
							}
						}
						return true;
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.x < after.x; i.x++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									return false;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									return false;
								}
							}
						}
						return true;
					}
				}
				else if (area[after.y][after.x].getKind() > 7) //eat
				{
					int eatable = 0;
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
					}
					if (eatable == 1)
					{
						return true;
					}
				}
			}
			return false;
			break;
		case 7: // black soldier
			if (before.x <= 8 && before.x >= 0 && before.y <= 4 && before.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == 1)
				{
					return true;
				}
			}
			else if (before.x <= 8 && before.x >= 0 && before.y <= 9 && before.y >= 5 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == 1)
				{
					return true;
				}
				else if (abs(after.x - before.x) == 1 && after.y - before.y == 0)
				{
					return true;
				}
			}
			return false;
			break;
		case -1:
			return false;
			break;
		}
	}
	else if (player == 1) // PLAYER_RED
	{
		switch (area[before.y][before.x].getKind())
		{
		case 8: // red general
			if (after.x <= 5 && after.x >= 3 && after.y <= 9 && after.y >= 7 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) == 1)
				{
					return true;
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 0)
				{
					return true;
				}
			}
			if (before.x == after.x && after.y >= 0 && after.y <= 2)
			{
				for (int hasgeneral = 0, i = 0; i <= 9; i++)
				{
					if (area[i][before.x].getKind() == 1)
					{
						hasgeneral += 1;
					}
					else if (area[i][before.x].getKind() != -1)
					{
						break;
					}
					if (i == 9 && hasgeneral == 1)
					{
						return true;
					}
				}
			}
			return false;
			break;
		case 9: // red advisor
			if (after.x <= 5 && after.x >= 3 && after.y <= 9 && after.y >= 7 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 1)
				{
					return true;
				}
			}
			return false;
			break;
		case 10: // red elephant
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 5 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 2 && area[(after.y + before.y) / 2][(before.x + after.x) / 2].getKind() == -1)
				{
					return true;
				}
			}
			return false;
			break;
		case 11: // red chariot
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
				{
					if (before.y < after.y)
					{
						for (Coord i = before; i.y < after.y; i.y++)
						{
							if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
							{
								return false;
							}
						}
					}
					else
					{
						for (Coord i = before; i.y > after.y; i.y--)
						{
							if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
							{
								return false;
							}
						}
					}
					return true;
				}
				else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
				{
					if (before.x < after.x)
					{
						for (Coord i = before; i.x < after.x; i.x++)
						{
							if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
							{
								return false;
							}
						}
					}
					else
					{
						for (Coord i = before; i.x > after.x; i.x--)
						{
							if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
							{
								return false;
							}
						}
					}
					return true;
				}
			}
			return false;
			break;
		case 12: // red horse
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() > 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 1)
				{
					if (before.x < after.x&&before.x != 8)
					{
						if (area[before.y][before.x+1].getKind() == -1)
						{
							return true;
						}
					}
					else if (before.x > after.x&&before.x != 0)
					{
						if (area[before.y ][before.x-1].getKind() == -1)
						{
							return true;
						}
					}
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 2)
				{
					if (before.y < after.y&&before.y != 9)
					{
						if (area[before.y+1][before.x].getKind() == -1)
						{
							return true;
						}
					}
					else if (before.y > after.y&&before.y != 0)
					{
						if (area[before.y-1][before.x].getKind() == -1)
						{
							return true;
						}
					}
				}
				return false;
			}
			return false;
			break;
		case 13: // red cannon
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0)
			{
				if (area[after.y][after.x].getKind() == -1) //move
				{
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									return false;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									return false;
								}
							}
						}
						return true;
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.x < after.x; i.x++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									return false;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									return false;
								}
							}
						}
						return true;
					}
				}
				else if (area[after.y][after.x].getKind() <= 7 && area[after.y][after.x].getKind() >= 1) //eat
				{
					int eatable = 0;
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.y][i.x].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
					}
					if (eatable == 1)
					{
						return true;
					}
				}
			}
			return false;
			break;
		case 14: // red soldier
			if (before.x <= 8 && before.x >= 0 && before.y <= 9 && before.y >= 5 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == -1)
				{
					return true;
				}
			}
			else if (before.x <= 8 && before.x >= 0 && before.y <= 4 && before.y >= 0 && (area[after.y][after.x].getKind() == -1 || area[after.y][after.x].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == -1)
				{
					return true;
				}
				else if (abs(after.x - before.x) == 1 && after.y - before.y == 0)
				{
					return true;
				}
			}
			return false;
			break;
		case -1:
			return false;
			break;
		}
	}
	return false;
}
void ChessBoard::setChess(const int32_t &uid, const int32_t &kind, const Coord &loc)
{
	if (kind == 0)
	{
		area[loc.y][loc.x] = Chess(uid, kind - 1, loc);
	}
	else
	{
		area[loc.y][loc.x] = Chess(uid, kind, loc);
	}
}
// get chess ref
Chess &ChessBoard::getChess(const Coord &loc) { return area[loc.y][loc.x]; }
bool ChessBoard::moveChess(Chess &c, const Coord &cursorLoc, const int player)
{
	if (isMovable(cursorLoc, c.getCurrCoord(), player))
	{
		// replace the chess on cursor loc
		area[cursorLoc.y][cursorLoc.x] = c;

		// clear current loc
		Chess cleaner;
		area[c.getCurrCoord().y][c.getCurrCoord().x] = cleaner;

		// update the loc
		c.moveCoord(cursorLoc);
		return true;
	}
	return false;
}

// set turn
void ChessBoard::setTurn(const int32_t &t) { turn = t; }
// get turn
const int32_t ChessBoard::getTurn() const { return turn; }

// get board's status
const BattleArea &ChessBoard::getArea() const
{
	return area;
}

// draw
void ChessBoard::drawBoard(const BattleArea &board) const {}
void ChessBoard::undo() {}
void ChessBoard::redo() {}
