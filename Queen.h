#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(bool w);
	~Queen();

	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;
};