#pragma once
#include <functional>
#include <map>
#include <thread>
#include <mutex>
#include <vector>

#include "Packet.h"

class TcpSocket : public sf::TcpSocket 
{
public:
	//Li deleguem la feina a la persona que posa aquesta lambda
	//La feina de etreure la informació del package se la deleguem a qui se suposa que sap què ha de decodificar
	//(ex un message enlloc d'una carta).
	typedef std::function<void(Packet packet)> OnReceivePacket;

	//A més a més, guardarem una llista d'interessats en saber si estem desconnectats (el chat, els escacs, el socketManager...)
	typedef std::function<void(TcpSocket* socket)> OnSocketDisconnect;

	//Retorna un bool perquè amb la gestió que farem no ens cal status (sols ha funcionat / no ha funcionat)
	bool Connect(std::string ip, unsigned short port);
	void Receive();

	//Fem dues perquè quan estem treballant amb online (comunicació per comandes), hi ha vegades que només sabent de quin
	//socket és i sabent que vol fer algo, no ens cal informació addicional.
	bool Send(Packet::PacketKey key);
	bool Send(Packet::PacketKey key, Packet packet);

	//Key amb funció lambda que espera que rebi el packet
	void Subscribe(Packet::PacketKey key, OnReceivePacket onReceivePacket);

	//Com treballem amb mutex, es pot donar el cas que bloquegem el mutex, i que executem coses.
	//Pot ser que aquestes coses també vulguin fer servir el mateix mutex. 
	void SubscribeAsync(Packet::PacketKey key, OnReceivePacket onReceivePacket);

	void SubscribeOnDisconnect(OnSocketDisconnect onSocketDisconnect);

private:
	std::map<Packet::PacketKey, OnReceivePacket> _subscriptions;
	//No cal que sigui un punter perquè és privat: no el passarem a ningú.
	//El podem fer per còpia perquè així quan es destrueixi l'objecte es destrueixi sol.
	std::mutex _subscriptionsMutex;

	std::vector<OnSocketDisconnect> _onSocketDisconnectList;
	std::mutex _onSocketDisconnectMutex;

	void ProcessPacket(Packet packet);
};

