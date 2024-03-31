#pragma once
#include <iostream>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>
#include <list>

#include "../ConnectionAbstraction/SocketsManager.h"
#include "../ConsoleControl.h"


class NewChat
{
public:
	NewChat(SocketsManager* SM, bool isServer, TcpSocket* socket);
	void OnClientEnter(TcpSocket* socket);

private:
	SocketsManager* _SM;

	bool _isServer = false;
	std::mutex _isServerMutex;

	std::vector<std::string> _messages;
	std::mutex _messagesMutex;

	void ShowMessage(std::string message);
	void ShowAlert(std::string message);
	void ShowError(std::string message);

	void ListenMessages(sf::TcpSocket* socket);
	void ListenKeyboardToSendMessage();
	void SendMessage(std::string message);
};