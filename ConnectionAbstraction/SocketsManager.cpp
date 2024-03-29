#include "SocketsManager.h"

SocketsManager::SocketsManager(OnSocketConnected onSocketConnected)
{
	_onSocketConnected = onSocketConnected;
}

SocketsManager::~SocketsManager()
{
	delete _listener;

	for (TcpSocket* socket : _sockets)
	{
		delete socket;
	}
}

void SocketsManager::StartLoop()
{
	_isRunningMutex.lock();

	if (_isRunning) //Prevent multiple loops
	{
		_isRunningMutex.unlock();
		return;
	}

	_isRunning = true;

	_isRunningMutex.unlock();

	std::thread* loopThread = new std::thread(&SocketsManager::SelectorLoop, this);
	loopThread->detach();
}

bool SocketsManager::StartListener(unsigned short port)
{
	_listenerMutex.lock();

	if (_listener != nullptr)		//Prevenir múltiples listeners. Només fer algo si encara no tenim listener (cada cosa del joc sols necessita un listener).
	{
		_listenerMutex.unlock();
		return false;
	}

	_listener = new TcpListener();
	if (!_listener->Listen(port))
	{
		delete _listener;
		_listenerMutex.unlock();
		return false;
	}

	//Si ha anat tot bé (no ha fet return abans pels errors):
	_selector.Add(*_listener);		//TODO

	_listenerMutex.unlock();
	return true;
}

bool SocketsManager::ConnectToServer(std::string ip, unsigned short port)
{
	TcpSocket* socket = new TcpSocket();
	if (!socket->Connect(ip, port))	//TODO
	{
		delete socket;
		return false;
	}

	//Ja la tenim implementada perquè és exactament la mateixa que crida el listener (la podem reaprofitar)
	AddSocket(socket);

	return true;
}

TcpSocket* SocketsManager::GetServerSocket()
{
	return _serverSocket;
}

std::list<TcpSocket*> SocketsManager::GetAllSockets()
{
	_socketsMutex.lock();
	std::list<TcpSocket*> sockets = _sockets;
	_socketsMutex.unlock();
	return sockets;
}

void SocketsManager::SelectorLoop()
{
	_isRunningMutex.lock();
	bool isRunning = true;
	_isRunningMutex.unlock();

	while (isRunning)
	{
		if (_selector.Wait())
		{
			CheckListener();
			CheckSockets();
		}

		_isRunningMutex.lock();
		isRunning = _isRunning;
		_isRunningMutex.unlock();
	}
}

void SocketsManager::CheckListener()
{
	_listenerMutex.lock();

	if (_listener != nullptr && _selector.IsReady(*_listener));
	{
		TcpSocket* socket = new TcpSocket();
		if (_listener->Accept(*socket))
		{
			AddSocket(socket);
		}
		else
		{
			//Evitar que el punter es quedi perdut en memòria si no ha funcionat.
			delete socket;
			//TODO: Gestionar l'error
		}
	}

	_listenerMutex.unlock();
}

void SocketsManager::CheckSockets()
{
	_socketsMutex.lock();
	for (TcpSocket* socket : _sockets)
	{
		if (_selector.IsReady(*socket))
		{
			socket->Receive();
		}
	}
	_socketsMutex.unlock();
}

void SocketsManager::AddSocket(TcpSocket* socket)
{
	_socketsMutex.lock();

	if (_sockets.empty())
		_serverSocket = socket;

	_sockets.push_back(socket);
	_selector.Add(*socket);			//Perquè pugui escoltar si hi ha hagut canvis al socket

	_onSocketConnected(socket);

	//TODO
	//Cal subscriure's a OnDisconnect, per així gestionar el que passa si un socket es desconnecta:
	//ex: regalar-li la partida a l'oponent, treure'l del Mario Kart, posar un bot perquè el controli...
	socket->SubscribeOnDisconnect([this](TcpSocket* socket) {
		//Async perquè la cridarà un thread a part.
		//Treu el socket i el destrueix.
		//Si _onSocketConnected es cridés abans que aquesta lambda i el socket s'hagués destruït, podrien sorgir errors.
		//Podríem o bé invertir l'ordre de crida, o bé que el socket s'autodestruís.
		//Com que les autodestruccions poden donar problemes, invertim l'ordre.
		RemoveSocketAsync(socket);	
	});

	_socketsMutex.unlock();
}

void SocketsManager::RemoveSocket(TcpSocket* socket)
{
	_selector.Remove(*socket);
	_socketsMutex.lock();
	_sockets.remove(socket);		//Podem fer remove perquè és una llista i no un vector. Si fos vector, faríem erase.
	_socketsMutex.unlock();
	
	delete socket;					//Quan ja ningú té la referència del socket, podem fer delete.
}

void SocketsManager::RemoveSocketAsync(TcpSocket* socket)
{
	//Cridarà la funció real amb un thread.
	//Si hi ha algun mutex per enmig, no farà el lock infinit, sinó que s'esperarà a que es pugui executar.
	std::thread* removeSocketThread = new std::thread(&SocketsManager::RemoveSocket, this, socket);
	removeSocketThread->detach();
}
