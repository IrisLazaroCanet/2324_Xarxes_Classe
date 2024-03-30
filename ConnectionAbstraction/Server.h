#pragma once
#include <iostream>

#include "SocketsManager.h"
#include "../Chat/NewChat.h"

class Server
{
public:
	Server(unsigned short port);
	SocketsManager* SM;

private:
	NewChat* _chat;
};

