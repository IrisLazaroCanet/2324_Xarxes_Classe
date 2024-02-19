#pragma once
#include "TcpListener.h"

class SocketSelector : sf::SocketSelector
{
public:
	//Esperar a què un dels sockets vinculats li digui que ha passat quelcom.
	//Si no ha passat res, retorna un false (podem continuar amb un bucle infinit).
	bool Wait();
	bool IsReady(TcpListener& listener);
	bool IsReady(TcpSocket& socket);

	void Add(TcpListener& listener);
	void Add(TcpSocket& socket);

	void Remove(TcpListener& listener);
	void Remove(TcpSocket& socket);

private:
	std::mutex _mutex;	
};

