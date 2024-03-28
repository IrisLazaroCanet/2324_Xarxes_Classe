#pragma once
#include <string>
#include <vector>
#include "Grid.h"

struct vector2
{
	int x;
	int y;
};

enum pieceType
{
	PAWN,
	TOWER,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

class Piece {
public:
	Piece();
	~Piece();

	bool isWhite;
	pieceType type;
	std::string spritepath;
	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p);
};