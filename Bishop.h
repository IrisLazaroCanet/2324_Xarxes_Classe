#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(bool w);
	~Bishop();

	virtual std::vector<vector2> GetMoveOptions(Grid* grid, vector2 p) override;
};