#pragma once
#include <iostream>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>

class Chat
{
private:
	//Considerar abstraer en clase "SafeList"
	std::vector<std::string> _messages;			//Si alguien entra y ya había mensajes, se los enviamos todos
	std::mutex _messagesMutex;					//Jamás pasar por parámetro un mutex por copia (no haría nada)
	
	sf::IpAddress _serverAddress;

	Chat() {};

	void ShowMessage(std::string message);
	void ShowWarning(std::string message);
	void ShowError(std::string message);

	void ListenClientsConnections(unsigned short port);

public:
	static Chat* Server(unsigned short port);

	//Usamos una string porque el usuario del chat no tiene por qué conocer los sockets.
	static Chat* Client(std::string ip, unsigned short port);
};