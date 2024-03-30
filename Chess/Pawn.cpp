#include "Pawn.h"

Pawn::Pawn(bool w)
{
	isWhite = w;
	type = PAWN;
	
	if (w)
		spritepath = "../Pieces/PawnG.png";
	else
		spritepath = "../Pieces/PawnS.png";
}
