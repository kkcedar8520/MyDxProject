#include "StdSelect.h"

bool StdSelect::Frame()
{
	
	FD_ZERO(&m_rSet);
	FD_ZERO(&m_wSet);

	FD_SET(m_Socket, &m_rSet);
	FD_SET(m_Socket, &m_wSet);

	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 1;
	int iRet = select(0, &m_rSet, &m_wSet, NULL, &time);
	if (FD_ISSET(m_Socket, &m_rSet))
	{
		if (RecvData(m_Socket)==false)
		{
			return false;
		}
		
	}

	if (FD_ISSET(FD_WRITE, &m_wSet))
	{
		/*for (auto packet : Network::m_Recvlist)
		{
			SendMsg(m_Socket, packet);
		}
		Network::m_Recvlist.clear();*/
	}
	return true;
}

StdSelect::StdSelect(SOCKET sock)
{
	m_Socket = sock;
}


StdSelect::~StdSelect()
{
}
