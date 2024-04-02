#include "Tower.h"

Tower::Tower(bool w)
{
	isWhite = w;
	type = TOWER;
	moved = false;

	if (w)
		spritepath = "Pieces/RookG.png";
	else
		spritepath = "Pieces/RookS.png";
}
