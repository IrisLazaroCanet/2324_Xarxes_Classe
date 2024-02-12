#pragma once
#include <iostream>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>

class Chat
{
private:
	bool _isServer = false;
	std::mutex _isServerMutex;

	std::list<sf::TcpSocket*> _sockets;
	std::mutex _socketsMutex;

	//Considerar abstraer en clase "SafeList"
	std::vector<std::string> _messages;			//Si alguien entra y ya había mensajes, se los enviamos todos
	std::mutex _messagesMutex;					//Jamás pasar por parámetro un mutex por copia (no haría nada)
	
	sf::IpAddress _serverAddress;

	Chat() {};

	void ShowMessage(std::string message);
	void ShowAlert(std::string message);
	void ShowError(std::string message);

	void ListenClientsConnections(unsigned short port);
	void ConnectToServer(std::string ip, unsigned short port);

	void OnClientEnter(sf::TcpSocket* client);
	void ListenMessages(sf::TcpSocket* socket);
	void ListenKeyboardToSendMessage();
	void SendMessage(std::string message);

public:
	static Chat* Server(unsigned short port);

	//Usamos una string porque el usuario del chat no tiene por qué conocer los sockets.
	static Chat* Client(std::string ip, unsigned short port);
};