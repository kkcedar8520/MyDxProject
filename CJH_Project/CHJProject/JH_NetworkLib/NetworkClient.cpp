#include "NetworkClient.h"


bool NetworkClient::Run()
{
	char Buffer[256];
	fgets(Buffer, sizeof(Buffer), stdin);
	SendMsg(m_Socket, Buffer, strlen(Buffer) - 1);

	return true;
}
bool NetworkClient::Frame()
{


	if (!m_pModel->Frame())
	{
		ShutDown();
		return false;
	}

	return true;
}
bool  NetworkClient::RunClient()
{
	if (m_StreamPacket.AddBuffer(m_Socket))
	{
		PacketProcess();
		return true;
	}
	return false;
}

bool  NetworkClient::Connect(const char* addr, int iSocketType, int PortNumber, u_long Mode)
{
	if (!CreateSocket(iSocketType, Mode))
	{
		return false;
	}

	ZeroMemory(&m_sockaddr, sizeof(m_sockaddr));
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(PortNumber);
	m_sockaddr.sin_addr.s_addr = inet_addr(addr);

	int iRet = connect(m_Socket, (SOCKADDR*)&m_sockaddr, sizeof(m_sockaddr));
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;

}
NetworkClient::NetworkClient()
{
}


NetworkClient::~NetworkClient()
{
}
