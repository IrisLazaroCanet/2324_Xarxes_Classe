#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(bool w);
	~Pawn();

	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;
};