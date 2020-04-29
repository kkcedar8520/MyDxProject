#pragma once
#include "JH_Client.h"

bool JH_Client::EventRun()
{

	int Ret = WSAEventSelect(m_Socket,m_hEventObject, FD_READ | FD_WRITE);
	if (Ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
		return true;
	}
	 Ret = WSAWaitForMultipleEvents(1, &m_hEventObject, FALSE, 1, NULL);
	
	if (Ret==WSA_WAIT_FAILED)
	{
		return false;
	}
	Ret -=WSA_WAIT_EVENT_0;

	WSANETWORKEVENTS NetworkEvents;
	Ret=WSAEnumNetworkEvents(m_Socket, &m_hEventObject, &NetworkEvents);
	if (Ret==SOCKET_ERROR)
	{
		return false;
	}
	
	if (NetworkEvents.lNetworkEvents&FD_READ)
	{
		if (NetworkEvents.iErrorCode[FD_READ_BIT]!=0)
		{
			return false;
		}
		if (!RunClient())
		{
			return false;
		}
	
		m_Recvlist.clear();

	}
	if (NetworkEvents.lNetworkEvents&FD_WRITE)
	{
		if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
		{
			return false;
		}
	}
	
	WSACloseEvent(m_hEventObject);
	return true;
}
bool JH_Client::SelectRun()
{
	FD_SET rSet; // FD( FILE DESCRIPTOR 약자 자신이 사용할 파일 또는 장치에대한 고유 식별값)
	FD_SET wSet; // 소켓함수를 쓰면 정수값이 반환되는데 이값이 FD( FILE DESCRIPTOR) 
				
					//	이값은 같은 프로그램안에서 중복되지않기 때문에  고유값으로 사용가능

	FD_ZERO(&rSet); 
	FD_ZERO(&wSet);

	FD_SET(m_Socket, &rSet);
	FD_SET(m_Socket, &wSet);

	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 1;
	int iRet = select(0, &rSet, &wSet, NULL, &time);
	if (FD_ISSET(m_Socket, &rSet))
	{
		while (!RunClient())
		{
			return false;
		}
	}

	if (FD_ISSET(FD_WRITE,&wSet))
	{	
		for (auto packet : m_Recvlist)
		{
			SendMsg(m_Socket, packet);
		}
		m_Recvlist.clear();
	}
	return true;
}
JH_Client::JH_Client()
{
	

}


JH_Client::~JH_Client()
{
}


bool JH_Client::Run()
{
	while (!EventRun())
	{
		return true;
	}
	return true;
}