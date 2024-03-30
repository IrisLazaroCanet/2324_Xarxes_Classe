#include "King.h"

King::King(bool w)
{
	isWhite = w;
	type = KING;
	moved = false;

	if (w)
		spritepath = "../Pieces/KingG.png";
	else
		spritepath = "../Pieces/KingS.png";
}
