#pragma once
#include "Piece.h"

class Tower : public Piece {
public:
	Tower(bool w);

	bool moved;
};