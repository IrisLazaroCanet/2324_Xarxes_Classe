#pragma once
#include <iostream>

#include "SocketsManager.h"
#include "../Chat/NewChat.h"

class Client
{
public:
	Client(unsigned short port);
	SocketsManager* SM;

private:
	NewChat* _chat;
};

