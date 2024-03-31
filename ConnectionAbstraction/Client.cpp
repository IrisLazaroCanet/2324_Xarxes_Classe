#include "Client.h"

Client::Client(unsigned short port)
{
    std::cout << "Client" << std::endl;
    std::cout << "Set server IP --> " << std::endl;

    std::string ip;
    std::getline(std::cin, ip);

    SM = new SocketsManager([this](TcpSocket* socket)
        {
            //Printar per consola que s'ha connectat un socket, i la seva ip
            std::cout << std::endl << "Socket Connected: " << socket->getRemoteAddress().toString();

            //Què ha de fer el socket quan rep un packet tipus Message?
            socket->Subscribe(Message, [socket](Packet packet)
                {
                    //Simplement desempaquetar-lo i printar el missatge per pantalla
                    std::string message;
                    packet >> message;
                    std::cout << std::endl << "New Message: " << message;
                });

            //Què ha de fer el socket quan es desconnecti?
            socket->SubscribeOnDisconnect([](TcpSocket* socket)
                {
                    //Printar per consola la seva ip.
                    std::cout << std::endl << "Socket disconnected: " << socket->getRemoteAddress().toString();
                });

            //El SM del Client envia al socket que s'acaba de connectar el missatge "Hola soy el cliente"
            std::string message = "Hola soy el cliente";
            Packet packet;
            packet << message;

            socket->Send(Message, packet);
        });

    if (SM->ConnectToServer(ip, port))
    {
        SM->StartLoop();
    }

    //OLD
    /*sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("10.40.1.123", port);

    if (status != sf::Socket::Done)
    {
        std::cout << std::endl << "Error on connect to server";
        return;
    }

    while (true)
    {
        std::cout << std::endl << "Next Message: ";
        std::string message;
        std::getline(std::cin, message);

        char data[100];

        int stringSize = message.length();
        for (int i = 0; i < stringSize; i++)
        {
            char c = message[i];
            data[i] = c;
        }

        if (socket.send(data, 100) != sf::Socket::Done)
        {
            std::cout << std::endl << "Error Sending Message";
        }
    }*/
}
