#include "Tower.h"

Tower::Tower(bool w)
{
	isWhite = w;
	type = TOWER;
	moved = false;

	if (w)
		spritepath = "../Pieces/TowerG.png";
	else
		spritepath = "../Pieces/TowerS.png";
}
