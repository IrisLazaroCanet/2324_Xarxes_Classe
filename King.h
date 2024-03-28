#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(bool w);
	~King();

	bool moved;
	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;

};
