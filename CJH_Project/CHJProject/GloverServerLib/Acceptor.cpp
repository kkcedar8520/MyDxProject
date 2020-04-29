#include "Acceptor.h"

bool Acceptor::Setting(int iPort, const char* addr)
{
	m_listenSock = socket(AF_INET,SOCK_STREAM, NULL);
	
	int optval = 1;
	setsockopt(m_listenSock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

	int option = TRUE;
	setsockopt(m_listenSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));
	
	LINGER ling = { 0, };
	ling.l_onoff = 1;
	ling.l_linger = 1000;

	int iRet = setsockopt(m_listenSock, SOL_SOCKET,
		SO_LINGER, (char*)&ling, sizeof(ling));

	int iSize;
	int typelen = sizeof(iSize);
	 iRet = getsockopt(m_listenSock, SOL_SOCKET, // RecvBuffer 크기와 Sednbuffer 크기 얻기
		SO_SNDBUF, (char*)&iSize, &typelen);
	iRet = getsockopt(m_listenSock, SOL_SOCKET,
		SO_RCVBUF, (char*)&iSize, &typelen);

	 iSize = 0;
	 iRet = setsockopt(m_listenSock, SOL_SOCKET,//
		SO_RCVBUF, (char*)&iSize, typelen);


	SOCKADDR_IN SockAddr;
	ZeroMemory(&SockAddr, sizeof(SOCKADDR_IN));
	if (addr == 0)
	{
		SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		SockAddr.sin_addr.s_addr = inet_addr(addr);
	}
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port =htons(iPort);
	
	int Ret = bind(m_listenSock, (SOCKADDR*)&SockAddr, sizeof(SockAddr));
	if (Ret==SOCKET_ERROR)
	{
		return false;
	}
	Ret = listen(m_listenSock, SOMAXCONN);
	if (Ret==SOCKET_ERROR)
	{
		return false;
	}

	
	CreateThread();
	return true;
}
bool Acceptor::Run()
{
	SOCKET ClientSocket;
	SOCKADDR_IN sockAddr;
	int addlen = sizeof(sockAddr);

	while (bStart == true)
	{

		ClientSocket = accept(m_listenSock, (SOCKADDR*)&sockAddr, &addlen);
		if (ClientSocket == INVALID_SOCKET)
		{
			return false;
		}
		else
		{
			I_Session.CreateSession(ClientSocket, sockAddr);
		}
	
	}
	return true;
}

Acceptor::Acceptor()
{
}


Acceptor::~Acceptor()
{
}
