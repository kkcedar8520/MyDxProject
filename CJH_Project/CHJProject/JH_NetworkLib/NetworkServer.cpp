#include "NetworkServer.h"
std::list<User>NetworkServer::userList;

bool NetworkServer::Run()
{

		SOCKET ClientSocket;
		SOCKADDR_IN ClientAddr;
		int addlen = sizeof(ClientAddr);

		ClientSocket = accept(m_Socket, (SOCKADDR*)&ClientAddr,&addlen);
		if (ClientSocket==SOCKET_ERROR)
		{
			if (WSAGetLastError()!=WSAEWOULDBLOCK)
			{
				return false;
			}
		}
		else
		{
			GreetMessage(ClientSocket, ClientAddr);
		}


	return true;
}

bool  NetworkServer::CreateServer(const char* addr, int iSocketType, int PortNumber, u_long Mode)
{
	if (!CreateSocket(iSocketType, Mode))
	{
		return false;
	}
	ZeroMemory(&m_sockaddr, sizeof(m_sockaddr));
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(PortNumber);
	if (addr == nullptr)
	{
		m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		m_sockaddr.sin_addr.s_addr = inet_addr(addr);
	}

	int iRet = bind(m_Socket, (SOCKADDR*)&m_sockaddr, sizeof(SOCKADDR));
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	iRet = listen(m_Socket, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
bool NetworkServer::StdSelectRun()
{
	FD_SET rSet;
	FD_SET wSet;


	

	FD_ZERO(&rSet);
	FD_ZERO(&wSet);

	FD_SET(m_Socket, &rSet);


	if (FD_ISSET(m_Socket,&rSet))
	{
		if (!Run())
		{
			std::cout << "접속 에러" << std::endl;
		}
	}
	timeval time;

	time.tv_sec = 0;
	time.tv_usec = 1;

	int iRet = select(0, &rSet, &wSet, NULL,&time);
	if (iRet==SOCKET_ERROR)
	{
		if (WSAGetLastError()!=WSAEWOULDBLOCK)
		{
			return false;
		}
	}
	std::list<User>::iterator iter;
	for ( iter=userList.begin(); iter!=userList.end();iter++)
	{
		FD_SET(iter->m_Socket, &rSet);
		if (m_Recvlist.size()>0)
		{
			FD_SET(m_Socket, &wSet);
		}
	}

	{
		Lock lock(this);
		for (iter = userList.begin(); iter != userList.end();iter++)
		{
			
			if (FD_ISSET(iter->m_Socket, &rSet))
			{
				if (!m_StreamPacket.AddBuffer(iter->m_Socket))
				{
					iter->m_Connect = false;
					continue;
				}
			}
			if (FD_ISSET(m_Socket,&wSet))
			{
				std::list<UPACKET>::iterator packiter;
				for (packiter = m_Recvlist.begin();packiter!=m_Recvlist.end();packiter++)
				{
					if (!SendMsg(iter->m_Socket, *packiter))
					{
						iter->m_Connect = false;
						break;
					}
				}
			}
		
		}
	}

	for (iter = userList.begin(); iter != userList.end();iter++)
	{
		if (iter->m_Connect == false)
		{
			iter = userList.erase(iter);
		}
	}
	return true;
}
void  NetworkServer::GreetMessage(SOCKET sock, SOCKADDR_IN sock_addr)
{
	User NewUser;
	NewUser.m_Socket = sock;
	NewUser.m_SocketAddrIn = sock_addr;
	NewUser.m_Connect = true;

	std::cout << "ip:" << inet_ntoa(sock_addr.sin_addr) << "Port:" << ntohs(sock_addr.sin_port) << std::endl;

	//char Buffer[256] = { "안녕하세요 채팅서버접속을 환영합니다!"};
	//PackSend(Buffer, sock, sock_addr);


	Lock UserLock(this);

	userList.push_back(NewUser);

}
NetworkServer::NetworkServer()
{
	
}


NetworkServer::~NetworkServer()
{
}
