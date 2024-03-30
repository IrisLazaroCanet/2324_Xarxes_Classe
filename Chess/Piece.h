#pragma once
#include <string>
#include <vector>

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
	Piece() = default;

	bool isWhite;
	pieceType type;
	std::string spritepath;
};