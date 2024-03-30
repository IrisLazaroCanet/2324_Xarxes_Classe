#include "Queen.h"

Queen::Queen(bool w)
{
	isWhite = w;
	type = QUEEN;
	
	if (w)
		spritepath = "../Pieces/QueenG.png";
	else
		spritepath = "../Pieces/QueenS.png";
}
