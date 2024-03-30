#pragma once
#include <List>

#include "SocketSelector.h"

enum PackagesIds : Packet::PacketKey { Message = 0 };

class SocketsManager
{
public:
	typedef std::function<void(TcpSocket* socket)> OnSocketConnected;
	
	//Per construir un Manager, li hem de dir qu� volem que faci quan es connecti un socket.
	SocketsManager(OnSocketConnected onSocketConnected);
	//Necessitem destructor perqu� els sockets s�n punters
	~SocketsManager();

	//No li donarem l'opci� a l'usuari de sockets de no treballar amb threads.
	void StartLoop();
	
	//Quan sigui peer to peer, s'executaran les dues funcions.
	//La classe SocketManager ens ha de servir tant per peer to peer com per a imperatius.
	bool StartListener(unsigned short port);
	bool ConnectToServer(std::string ip, unsigned short port);

	//TEST
	TcpSocket* GetServerSocket();
	std::list<TcpSocket*> GetAllSockets();
	
private:
	bool _isRunning = false;
	std::mutex _isRunningMutex;

	//Com que nom�s l'utilitzar� aquesta classe, no ens cal fer-lo punter
	SocketSelector _selector;

	//sf::Socket �s NonCopyable: hem d'usar-los com a punters, no per c�pia
	TcpListener* _listener;
	std::mutex _listenerMutex;

	std::list<TcpSocket*> _sockets;
	std::mutex _socketsMutex;

	//Si volgu�ssim, podr�em posar una llista de OnSocketConnected, per� volem tenir-ho centralitzat.
	//Podem tenir 2 SocketsManager per separat: un que se subscriu als moviments d'escacs, un altre que se subscriu als missatges del chat
	OnSocketConnected _onSocketConnected;

	TcpSocket* _serverSocket;

	void SelectorLoop();
	void CheckListener();
	void CheckSockets();

	void AddSocket(TcpSocket* socket);
	void RemoveSocket(TcpSocket* socket);
	void RemoveSocketAsync(TcpSocket* socket);
};

