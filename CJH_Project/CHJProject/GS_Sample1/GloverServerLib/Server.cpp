#include "Server.h"


bool Server::Init()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2.2, 0), &wsa);

	I_IOCP.Init();

	if(!m_Acceptor.Setting(10000, "119.195.167.25"))
	{
		std::cout << "SOCKET ERROR!" << std::endl;
		return false;
	}

	CreateThread();
	return true;
}
bool Server::Release()
{
	WSACleanup();
	return true;
}

bool Server::Run()
{

	while (bStart == true)
	{

	}
	return true;
}
Server::Server()
{

}


Server::~Server()
{
	Release();

}
