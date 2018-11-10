#include "Server.h"

using namespace std;

Server& Server::startupWinsock()
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version, &data);

	try
	{
		if (wsOk)
		{
			throw runtime_error("Can't start Win Socket: " + to_string(wsOk));
		}	

	}
	catch (const std::exception& e)
	{
		cout << "Error: " << e.what();
	}

	return *this;
}

Server& Server::bindSocket()
{
	int protocol = 0;
	m_inSocket = socket(AF_INET, SOCK_DGRAM, protocol);

	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000);  // Convert LE -> BE

	try
	{
		if (bind(m_inSocket, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
		{
			throw runtime_error("Can't bind socket: " + to_string(WSAGetLastError()));
		}
	}
	catch (const std::exception& e)
	{
		cout << "Error: " << e.what();
	}

	return *this;
}

Server & Server::closeSocket()
{
	closesocket(m_inSocket);

	return *this;
}

Server & Server::cleanup()
{
	WSACleanup();

	return *this;
}

Server & Server::initClientMetaData()
{
	m_clientLength = sizeof(m_client);
	SecureZeroMemory(&m_client, m_clientLength);

	return *this;
}

Server & Server::initLoop()
{
	// Start Loop
	while (true)
	{
		SecureZeroMemory(m_buffer, sizeof(m_buffer));

		// Wait for msg
		int bytesIn = recvfrom(m_inSocket, m_buffer, sizeof(m_buffer), 0, (sockaddr*)&m_client, &m_clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Receiving from Client Error: " << WSAGetLastError() << "\n";
			continue;
		}

		// Display msg & client info
		char clientIP[CLIENT_IP_BUFFER_SIZE];
		SecureZeroMemory(clientIP, sizeof(clientIP));

		inet_ntop(AF_INET, &m_client.sin_addr, clientIP, sizeof(clientIP));

		cout << "Message received from: " << clientIP << " : " << m_buffer << "\n";
	}

	return *this;
}
