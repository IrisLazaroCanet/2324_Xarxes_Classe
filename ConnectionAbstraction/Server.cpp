#include "Server.h"

Server::Server(unsigned short port)
{
    std::cout << "Server" << std::endl;

    //Chat* chat = Chat::Server(port);

    SM = new SocketsManager([this](TcpSocket* socket)
        {
            //Printar per consola que s'ha connectat un socket, i la seva ip
            std::cout << std::endl << "Socket Connected: " << socket->getRemoteAddress().toString();

            //Què fer quan es rep un packet amb key Message?
            socket->Subscribe(Message, [socket](Packet packet)
                {
                    //Desempaquetar i printar el missatge per consola
                    std::string message;
                    packet >> message;
                    std::cout << std::endl << "New Message: " << message;

                    //Respondre amb "Pues yo soy el server"
                    std::string response = "Pues yo soy el server";
                    Packet responsePacket;
                    responsePacket << response;

                    socket->Send(Message, responsePacket);
                });

            //Què ha de fer el socket quan es desconnecti?
            socket->SubscribeOnDisconnect([](TcpSocket* socket)
                {
                    //Printar per consola la seva ip.
                    std::cout << std::endl << "Socket disconnected: " << socket->getRemoteAddress().toString();
                });

            //Guardar-se el socket del server
            //Si és el primer socket en connectar-se, ha de ser per força el server.
            SM->TryToSetServerSocket(socket);
            
            //El SM del Server envia "Hola soy el server" al socket que s'acaba de connectar
            /*
            std::string message = "Hola soy el server";
            Packet messagePacket;
            messagePacket << message;
            socket->Send(Message, messagePacket);
            */
        });

    if (SM->StartListener(port))
    {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
        std::cout << "Listening on IP: " << ipAddress.toString();
        SM->StartLoop();
    }

    /*sf::TcpListener listener;

    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cout << std::endl << "Error on start listener";
        return;
    }
    sf::IpAddress ipAdress = sf::IpAddress::getLocalAddress();  //El client sha de conectar a tu, aixi que has de saber la ip previament
    //En aquest cas es red local

    std::cout << std::endl << "Listening on IP: " + ipAdress.toString();

    sf::TcpSocket client;

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << std::endl << "Error on accept client";
        return;
    }

    std::cout << std::endl << "Client Connected " << client.getRemoteAddress().toString();

    while (true)
    {
        char data[100];
        std::size_t received;

        std::string message;

        if (client.receive(data, 100, received) != sf::Socket::Done)
        {
            std::cout << std::endl << "Error recieve message";
        }
        else
        {
            for (size_t i = 0; i < received; i++)
            {
                char c = data[i];
                message += c;


                std::cout << std::endl << message;
            }
        }
    }*/
}
