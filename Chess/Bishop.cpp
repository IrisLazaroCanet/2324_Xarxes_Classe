#include "Bishop.h"

Bishop::Bishop(bool w)
{
	isWhite = w;
	type = BISHOP;

	if (w)
		spritepath = "../Pieces/BishopG.png";
	else
		spritepath = "../Pieces/BishopS.png";
}
