#include "NewChat.h"

NewChat::NewChat(SocketsManager* SM, bool isServer, TcpSocket* socket)
{
	_SM = SM;
	_isServer = isServer;

	//Tant servidor com clients escoltaran input del teclat
	std::thread keyboardThread = std::thread(&NewChat::ListenKeyboardToSendMessage, this);
	keyboardThread.detach();

	if (isServer)
	{
		//Escoltar missatges pels clients
		//Cada cop que es connecta un client, hem de cridar a ListenMessages per aquell socket

		//Temp: Listen to messages
		std::thread listenMessageThread = std::thread(&NewChat::ListenMessages, this, socket);
		listenMessageThread.detach();
	}
	else
	{
		//Listen to messages
		std::thread listenMessageThread = std::thread(&NewChat::ListenMessages, this, socket);
		listenMessageThread.detach();
	}
}

void NewChat::ShowMessage(std::string message)
{
	_messagesMutex.lock();
	_messages.push_back(message);
	_messagesMutex.unlock();

	ConsoleControl::LockMutex();
	std::cout << message << std::endl;
	ConsoleControl::UnlockMutex();
}

void NewChat::ShowAlert(std::string message)
{
	ConsoleControl::LockMutex();
	ConsoleControl::SetColor(ConsoleControl::YELLOW);
	std::cout << message << std::endl;
	ConsoleControl::SetColor(ConsoleControl::WHITE);
	ConsoleControl::UnlockMutex();
}

void NewChat::ShowError(std::string message)
{
	ConsoleControl::LockMutex();
	ConsoleControl::SetColor(ConsoleControl::RED);
	std::cout << message << std::endl;
	ConsoleControl::SetColor(ConsoleControl::WHITE);
	ConsoleControl::UnlockMutex();
}

void NewChat::ListenMessages(sf::TcpSocket* socket)
{
	//S'estarà fent en bucle mentre duri l'execució
	while (true)
	{
		sf::Packet packet;
		std::string message;

		if (socket->receive(packet) != sf::Socket::Done)
		{
			ShowError("Error on receiving message");
		}
		else
		{
			//Si hem rebut bé el paquet, desempaquetem
			packet >> message;
			
			//Tots (tant servidor com clients) mostraran el missatge
			ShowMessage(message);

			_isServerMutex.lock();
			bool isServer = _isServer;
			_isServerMutex.unlock();

			//Si és el servidor, envia aquest missatge a tots els sockets
			//Perquè així rebin el paquet i puguin mostrar el missatge en pantalla
			if (isServer)
			{
				SendMessage(message);
			}
		}
	}
}

void NewChat::ListenKeyboardToSendMessage()
{
	std::string message = "";

	//S'estarà fent en bucle mentre duri l'execució
	while (true)
	{
		char c = ConsoleControl::WaitForReadNextChar();

		//Si l'usuari li ha donat a enviar...
		if (c == KB_Enter)
		{
			//Enviem el missatge a tots els sockets
			SendMessage(message);

			//"Clear" de la string on aquesta funció es guarda el missatge
			message = "";

			_isServerMutex.lock();
			bool isServer = _isServer;
			_isServerMutex.unlock();

			//Si és el servidor, mostrem aquest missatge per pantalla
			if (isServer)
			{
				ShowMessage(message);
			}
		}
		else
		{
			//Si l'usuari encara no li ha donat a enviar...
			//La funció segueix guardant-se a la string els chars que escriu l'usuari
			message += c;
		}
	}
}

void NewChat::SendMessage(std::string message)
{
	//Crear un paquet on posar la string a enviar
	sf::Packet packet;
	packet << message;

	//Li demanem al SocketManager tots els sockets
	std::list<TcpSocket*> sockets = _SM->GetAllSockets();

	ConsoleControl::LockMutex();
	std::cout << "Num sockets: " << sockets.size() << std::endl;
	ConsoleControl::UnlockMutex();

	for (sf::TcpSocket* socket : sockets)
	{
		//Enviar el paquet per cada socket i comprovar si ha anat bé
		if (socket->send(packet) != sf::Socket::Status::Done)
		{
			ShowError("Error on sending message");
		}
	}
}
