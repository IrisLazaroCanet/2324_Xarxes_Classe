#pragma once
#include "SFML/Network.hpp"

class Packet : public sf::Packet
{
public:
	//Li posem un typedef perquè si més endavant el volem canviar, canviant-lo aquí funcionarà a tot arreu
	typedef unsigned short PacketKey;
};

