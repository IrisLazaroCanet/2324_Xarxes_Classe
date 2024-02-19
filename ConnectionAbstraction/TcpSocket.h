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
	//La feina de etreure la informaci� del package se la deleguem a qui se suposa que sap qu� ha de decodificar
	//(ex un message enlloc d'una carta).
	typedef std::function<void(Packet packet)> OnReceivePacket;

	//A m�s a m�s, guardarem una llista d'interessats en saber si estem desconnectats (el chat, els escacs, el socketManager...)
	typedef std::function<void(TcpSocket* socket)> OnSocketDisconnect;

	//Retorna un bool perqu� amb la gesti� que farem no ens cal status (sols ha funcionat / no ha funcionat)
	bool Connect(std::string ip, unsigned short port);
	void Receive();

	//Fem dues perqu� quan estem treballant amb online (comunicaci� per comandes), hi ha vegades que nom�s sabent de quin
	//socket �s i sabent que vol fer algo, no ens cal informaci� addicional.
	bool Send(Packet::PacketKey key);
	bool Send(Packet::PacketKey key, Packet packet);

	//Key amb funci� lambda que espera que rebi el packet
	void Subscribe(Packet::PacketKey key, OnReceivePacket onReceivePacket);

	//Com treballem amb mutex, es pot donar el cas que bloquegem el mutex, i que executem coses.
	//Pot ser que aquestes coses tamb� vulguin fer servir el mateix mutex. 
	void SubscribeAsync(Packet::PacketKey key, OnReceivePacket onReceivePacket);

	void SubscribeOnDisconnect(OnSocketDisconnect onSocketDisconnect);

private:
	std::map<Packet::PacketKey, OnReceivePacket> _subscriptions;
	//No cal que sigui un punter perqu� �s privat: no el passarem a ning�.
	//El podem fer per c�pia perqu� aix� quan es destrueixi l'objecte es destrueixi sol.
	std::mutex _subscriptionsMutex;

	std::vector<OnSocketDisconnect> _onSocketDisconnectList;
	std::mutex _onSocketDisconnectMutex;

	void ProcessPacket(Packet packet);
};

