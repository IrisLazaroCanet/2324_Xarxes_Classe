#pragma once
#include <iostream>
#include <list>
#include <conio.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "Server.h"
#include "Client.h"
#include "../Chat.h"
#include "../ConsoleControl.h"
#include "SocketsManager.h"
#include "../WindowsHelpers/Window.h"
#include "../Chess/Game.h"


class NetManager
{
public:
	NetManager();
	~NetManager();
	void Init();

	unsigned short port = 3000;

private:
	void RunClient();
	void RunServer();
	void RunWindows();

	Server* _server;
	Client* _client;
	Game* _game;
};

