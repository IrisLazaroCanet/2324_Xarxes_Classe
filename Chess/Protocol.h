#pragma once
#include <iostream>
#include <ctime>
#include <vector>

//TODO: Crear fitxers per cada classe

//PacketKey = 1
class CreateRoomRequest 
{
public:
	std::string name;
};


//PacketKey = 2
class CreateRoomResponse
{
public:
	unsigned int id;
};


//Tindrem una altra classe Room, que ens servirà per treballar (la room de veritat)
//RoomData sols conté la informació que hem de compartir amb tothom
class RoomData
{
public:
	unsigned long id;
	std::string name;
	__time32_t timestamp;		//Timestamp seed
};

//PacketKey = 3
class RoomsUpdate
{
public:
	std::vector<RoomData> rooms;
};