#pragma once
#include "Piece.h"
#include "WindowsHelpers/Button.h"
class Cell {
private:
	Piece* _piece;
	Button* _button;
public:
	Cell(vector2 position);
	Cell(Piece* p, Button* b, vector2 position);
	~Cell();

	vector2 pos;
	bool hasPiece();
	Piece* getPiece();
	OnClick getOnclick();
	void setOnclick(OnClick function);
};
