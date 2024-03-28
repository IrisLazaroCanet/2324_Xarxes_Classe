#pragma once
#include "Piece.h"

class Tower : public Piece {
public:
	Tower(bool w);
	~Tower();

	bool moved;
	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;

};