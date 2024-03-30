#include "Knight.h"

Knight::Knight(bool w)
{
	isWhite = w;
	type = KNIGHT;
	
	if (w)
		spritepath = "../Pieces/KnightG.png";
	else
		spritepath = "../Pieces/KnightS.png";
}
