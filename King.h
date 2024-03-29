#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(bool w);
	~King();

	bool moved;
};
