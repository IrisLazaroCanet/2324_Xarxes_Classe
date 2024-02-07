#include "Chat.h"
#include <thread>
#include "ConsoleControl.h"

void Chat::ShowMessage(std::string message)
{
    _messagesMutex.lock();
    _messages.push_back(message);
    _messagesMutex.unlock();
    
    ConsoleControl::LockMutex();
    std::cout << message << std::endl;
    ConsoleControl::UnlockMutex();
}

void Chat::ShowWarning(std::string message)
{
    ConsoleControl::LockMutex();
    ConsoleControl::SetColor(ConsoleControl::YELLOW);
    std::cout << message << std::endl;
    ConsoleControl::SetColor(ConsoleControl::WHITE);
    ConsoleControl::UnlockMutex();
}

void Chat::ShowError(std::string message)
{
    ConsoleControl::LockMutex();
    ConsoleControl::SetColor(ConsoleControl::RED);
    std::cout << message << std::endl;
    ConsoleControl::SetColor(ConsoleControl::WHITE);
    ConsoleControl::UnlockMutex();
}

void Chat::ListenClientsConnections(unsigned short port)
{
    //Crear un listener para escuchar las conexiones
    sf::TcpListener listener;

    //listen() devuelve si ha funcionado o no.
    //Ponerse a escuchar no da los sockets todav�a, hay que aceptar la entrada de los sockets.
    if (listener.listen(3000) != sf::Socket::Done)
    {
        std::cout << "Error on start listener" << std::endl;
        return;
    }

    sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
    std::cout << "Listening on IP: " + ipAddress.toString() << std::endl;

    sf::TcpSocket client;

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Error on accept Client" << std::endl;
        return;
    }
}

Chat* Chat::Server(unsigned short port)
{
	Chat* chat = new Chat();
	chat->_serverAddress = sf::IpAddress::getLocalAddress();



	return chat;
}

Chat* Chat::Client(std::string ip, unsigned short port)
{
	Chat* chat = new Chat();
	return chat;
}
