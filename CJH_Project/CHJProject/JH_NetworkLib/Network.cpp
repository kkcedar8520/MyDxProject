#pragma once
#include "Network.h"

std::map<int, CallFuction> Network::m_funtionExcute;
std::list<UPACKET>	Network::m_Recvlist;
std::list<UPACKET>	Network::m_Sendlist;
bool Network::m_bConnect = false;

bool Network::Run()
{
	
	return true;
}

 void  Network::PacketProcess()
 {
	 std::list<UPACKET>::iterator data;
	 std::map<int, CallFuction>::iterator fnCallIter;


	 for (data  = Network::m_Recvlist.begin();
		 data != Network::m_Recvlist.end(); 
		 data++)
	 {
		 fnCallIter = m_funtionExcute.find(data->ph.type);
		 if (fnCallIter!= m_funtionExcute.end())
		 {
			 (fnCallIter->second)(*data);
		 }


	 }
	 Network::m_Recvlist.clear();

 }


bool Network::CreateSocket(int iSocketType,u_long Mode)
{
	m_Socket = socket(AF_INET, iSocketType,0);
	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}
	
	ioctlsocket(m_Socket, FIONBIO,&Mode);


	return true;
}


bool Network::Init()
{
	WSADATA wa;
	WSAStartup(MAKEWORD(2, 2), &wa);
	bool bRet = std::cout.sync_with_stdio(true);
	
	return true;
}
bool Network::SetModel(std::shared_ptr<SelectModel> pModel)
{
	m_pModel = pModel;
	m_pModel ->Init();
	return true;
}
bool Network::Frame()
{
	return true;
}
void Network::CloseSocket()
{
	closesocket(m_Socket);
}
bool Network::ShutDown()
{
	m_bConnect = false;
	m_Recvlist.clear();
	m_Sendlist.clear();
	return true;
}
bool Network::Release()
{
	closesocket(m_Socket);
	WSACleanup();
	return true;
}

Network::Network()
{
	Init();

}


Network::~Network()
{
	Release();
}
