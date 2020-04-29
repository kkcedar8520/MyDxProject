#include "EventSelect.h"
#include"Network.h"

bool EventSelect::Init()
{
	m_hEvent = WSACreateEvent();

	int iRet = WSAEventSelect(m_Socket, &m_hEvent, FD_READ|FD_WRITE|FD_CLOSE);
	if (iRet==SOCKET_ERROR)
	{
		return false;
	}

	return true;
}
bool EventSelect::Frame()
{
	int iRet = WSAWaitForMultipleEvents(1, &m_hEvent, false, 1, false);
	if (iRet == WSA_WAIT_FAILED)
	{
		return false;
	}
	iRet -= WSA_WAIT_EVENT_0;

	WSANETWORKEVENTS NetworkEvents;

	iRet = WSAEnumNetworkEvents(m_Socket, m_hEvent, &NetworkEvents);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	if (NetworkEvents.lNetworkEvents&FD_READ)
	{
		if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
		{
			return false;
		}
		if (!RecvData(m_Socket))
		{
			return false;
		}
		

	}
	if (NetworkEvents.lNetworkEvents&FD_WRITE)
	{
		if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
		{
			return false;
		}
	}
	if (NetworkEvents.lNetworkEvents&FD_CLOSE)
	{
		if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
		{
			return false;
		}
		if (true)
		{

		}
		Network::m_bConnect = false;
	}

	return true;
}
EventSelect::EventSelect(SOCKET sock)
{
	m_Socket = sock;
}


EventSelect::~EventSelect()
{
}
