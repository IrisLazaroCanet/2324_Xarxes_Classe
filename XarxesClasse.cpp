#include <iostream>
#include <conio.h>
#include <SFML/Network.hpp>

#include "ConsoleControl.h"

void RunClient();
void RunServer();

int main()
{
    std::cout << "Select" << std::endl << "Client -> C" << std::endl << "Server -> S" << std::endl;

    char mode = ' ';

    do
    {
        mode = ConsoleControl::WaitForReadNextChar();
    } while (mode != 'C' && mode != 'c' && mode != 'S' && mode != 's');

    switch (mode)
    {
        case 'C' :
        case 'c':
        {
            RunClient();
            break;
        }
        case 'S':
        case 's':
        {
            RunServer();
            break;
        }
        default:
        {
            break;
        }
    }

    while (true)
    {

    }
}

void RunClient()
{
    std::cout << "Client" << std::endl;

    /*
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("172.31.98.147", 3000);

    if (status != sf::Socket::Done)
    {
        std::cout << "Error on connect to Server" << std::endl;
        return;
    }

    while (true)
    {
        std::cout << "Next Message: " << std::endl;
        std::string message;
        std::getline(std::cin, message);
        
        char data[100];
        int stringSize = message.length();
        for (int i = 0; i < stringSize; i++)
        {
            char c = message[i];
            data[i] = c;
        }

        if (socket.send(data, 100) != sf::Socket::Status::Done)
        {
            std::cout << "Error on sending message" << std::endl;
        }
    }
    */
}

void RunServer()
{
    std::cout << "Server" << std::endl;
    
    /*
    //Crear un listener para escuchar las conexiones
    sf::TcpListener listener;

    //listen() devuelve si ha funcionado o no.
    //Ponerse a escuchar no da los sockets todavía, hay que aceptar la entrada de los sockets.
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

    std::cout << "Client Connected: " << client.getRemoteAddress().toString() << std::endl;

    while (true)
    {
        char data[100];
        std::size_t received;
        std::string message;

        if (client.receive(data, 100, received) != sf::Socket::Done)
        {
            std::cout << "Error on receiving message" << std::endl;
        }
        else
        {
            for (size_t i = 0; i < received; i++)
            {
                char c = data[i];
                message += c;
            }

            std::cout << message << std::endl;
        }
    }
    */
}