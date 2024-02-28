#include "TcpSocket.h"

bool TcpSocket::Connect(std::string ip, unsigned short port)
{
	return connect(ip, port) == sf::Socket::Done;
}

void TcpSocket::Receive()
{
	//1) Crear un packet. El creem per c�pia perqu� no volem que ens els estiguin modificant.
	Packet packet;
	sf::Socket::Status status = receive(packet);

	switch (status)
	{
		case sf::Socket::Done:				//Quan arribi quelcom
		{
			ProcessPacket(packet);
			break;
		}
		case sf::Socket::Disconnected:		//Quan es desconnecti
		{
			//El protocol TCP comprova ell mateix si el socket s'ha desconnectat
			//En el protocol UDP, nosaltres mateixos li hem d'estar preguntant constantment "est�s viu?"
			_onSocketDisconnectMutex.lock();
			for (OnSocketDisconnect onDisconnect : _onSocketDisconnectList)
			{
				onDisconnect(this);
			}
			//T�cnicament, aquest clear no seria necessari.
			//Tanmateix, si tenim un processador molt r�pid, abans que es cridi el thread per fer el delete del socket
			//podria tornar a cridar a la funci� disconnect.
			//Amb aquest clear, evitem que l'event es cridi dos cops.
			_onSocketDisconnectList.clear();
			_onSocketDisconnectMutex.unlock();
			break;
		}
		case sf::Socket::NotReady:
		case sf::Socket::Partial:
		case sf::Socket::Error:
		default:
		{
			//TODO: Gestionar l'error
			break;
		}
	}
}

bool TcpSocket::Send(Packet::PacketKey key)
{
	Packet signedPacket;
	signedPacket << key;	//Li introdu�m la key
	
	//No enviem informaci� perqu� pot ser que vulguem comunicar-nos amb un socket per donar-li una ordre
	//(ex: ja estic preparat per alguna cosa), sense informaci� addicional
	return send(signedPacket) == sf::Socket::Done;
}

bool TcpSocket::Send(Packet::PacketKey key, Packet packet)
{
	Packet signedPacket;
	signedPacket << key;	//Li introdu�m la key

	//Li introdu�m la informaci� que hi ha al packet que passem com a par�metre.
	//Si f�ssim servir el packet que passem per par�metre, la key s'afegiria al final (seria un problema).
	//Com que obliguem a passar la key per par�metre, la llibreria funciona de forma molt s�lida:
	//ning� pot enviar un packet sense una key.
	
	//La funci� append ens permet enganxar-li informaci� extra
	signedPacket.append(packet.getData(), packet.getDataSize());

	return send(signedPacket) == sf::Socket::Done;
}

void TcpSocket::Subscribe(Packet::PacketKey key, OnReceivePacket onReceivePacket)
{
	_subscriptionsMutex.lock();
	//TODO: Fer m�ltiples subscripcions en una key:
	//El map no �s de keys i OnReceivePackets, sin� de keys i llistes d'OnReceivePacket
	_subscriptions[key] = onReceivePacket;	
	_subscriptionsMutex.unlock();
}

void TcpSocket::SubscribeAsync(Packet::PacketKey key, OnReceivePacket onReceivePacket)
{
	std::thread* subscribeThread = new std::thread(&TcpSocket::Subscribe, this, key, onReceivePacket);
	subscribeThread->detach();
}

void TcpSocket::SubscribeOnDisconnect(OnSocketDisconnect onSocketDisconnect)
{
	_onSocketDisconnectMutex.lock();
	_onSocketDisconnectList.push_back(onSocketDisconnect);
	_onSocketDisconnectMutex.unlock();
}

void TcpSocket::ProcessPacket(Packet packet)
{
	Packet::PacketKey key;

	//El primer, treure la key del packet.
	//Com que el socket treu la key, quan utilitzem el packet la key ja no estar�.
	//Aix�, ja no ens molestar� per treballar amb el packet.
	//Si volem enviar el packet, li posem la key i ja est�.
	packet >> key;

	//Amb la key, buscarem al map la funci� que hem d'executar.
	std::map<Packet::PacketKey, OnReceivePacket>::iterator it;

	_subscriptionsMutex.lock();

	it = _subscriptions.find(key);
	if (it != _subscriptions.end())
	{
		//Cridem la funci� corresponent i li passem el packet.
		it->second(packet);
	}

	_subscriptionsMutex.unlock();
}
