#pragma once
#include <iostream>
#include <ctime>
#include <vector>

//TODO: Crear fitxers per cada classe

/////////////////
// MATCHMAKING //
/////////////////

//PacketKey: OnLogin = 0
std::string name;

//PacketKey: CreateRoomRequest = 1
class CreateRoomRequest 
{
public:
	std::string name;
};


//PacketKey: CreateRoomResponse = 2
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

//PacketKey: RoomsUpdate = 3
class RoomsUpdate
{
public:
	std::vector<RoomData> rooms;
};


//PacketKey: JoinRoomPlayerRequest = 4
unsigned long idRoom;

class Address
{
	std::string ip;
	unsigned short port;
	std::string username;
};

//PacketKey: OnEnterAsPlayer = 5
class OnEnterAsPlayer
{
	std::vector<Address> otherP2PClients;
	bool isFirst;
};

//PacketKey: OnEnterAsPlayerFailure = 6 -> void (no té informació)


//PacketKey: JoinRoomSpectatorRequest = 7
unsigned long idRoom;


//PacketKey: OnEnterAsSpectator = 8
class OnEnterAsSpectator
{
	std::vector<Address> otherP2PClients;
};


//PacketKey: OnEnterAsSpectatorFailure = 9 -> void (no té informació)


//PacketKey: ExitRoom = 10
unsigned long idRoom;


//PacketKey: SetReady = 11
bool isReady;


//PacketKey: GameStart = 12 -> void (no té informació)


//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////
// GAMEPLAY //
//////////////

class Vector2
{
	int x, y;		//Les coordenades de la peça
};

//PacketKey: SelectPiece = 0
Vector2 selectedPosition;


//PacketKey: DeselectKey = 1 -> void (no té informació)


//PacketKey: MovePiece = 2
Vector2 targetPosition;


enum PieceType
{
	Pawn = 0, 
	Knight = 1, 
	Bishop = 2, 
	Tower = 3, 
	Queen = 4, 
	King = 5
};

//PacketKey: Promotion = 3
class Promotion
{
	Vector2 targetPosition;
	PieceType piece;
}; 


//PacketKey: Castle = 4
class Castle
{
	Vector2 kingTargetPosition;
	Vector2 towerTargetPosition;
	Vector2 towerCurrentPosition;
};


//PacketKey: EnPassant = 5
class EnPassant
{
	Vector2 targetPosition;
	Vector2 pawnKilledPosition;
};
