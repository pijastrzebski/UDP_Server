#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h> // win sockets lib

#pragma comment (lib, "ws2_32.lib")

class Server
{
	enum EBufferType
	{
		CLIENT_IP_BUFFER_SIZE = 256,
		MESSAGE_BUFFER_SIZE = 1024
	};

public:
	Server()  = default;
	~Server() = default;

	Server& startupWinsock();
	Server& bindSocket();
	Server& closeSocket();
	Server& cleanup();
	Server& initClientMetaData();
	Server& initLoop();

private:
	SOCKET      m_inSocket;
	sockaddr_in m_client;
	int         m_clientLength;
	char        m_buffer[MESSAGE_BUFFER_SIZE];
};

