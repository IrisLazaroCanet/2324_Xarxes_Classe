#pragma once
#include "Piece.h"

class Knight: public Piece {
public:
	Knight(bool w);
	~Knight();

	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;

};