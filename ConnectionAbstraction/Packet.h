#pragma once
#include "SFML/Network.hpp"

class Packet : public sf::Packet
{
public:
	//Li posem un typedef perqu� si m�s endavant el volem canviar, canviant-lo aqu� funcionar� a tot arreu
	typedef unsigned short PacketKey;
};

