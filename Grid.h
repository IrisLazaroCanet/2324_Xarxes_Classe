#pragma once
#include "Cell.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Tower.h"


class Grid {
public:
	Grid();
	~Grid();
	std::vector<std::vector<Cell*>> cells;
private:
	OnClick _pieceSelected;
	OnClick _unSelectPiece;
	OnClick _pieceMoved;
	OnClick _promotion;
	OnClick _castle;

	std::vector<vector2> GetMoveOptions(vector2* c);

	void MovePiece(vector2* from, vector2* to);
	void DeselectPiece(vector2* pos);
};