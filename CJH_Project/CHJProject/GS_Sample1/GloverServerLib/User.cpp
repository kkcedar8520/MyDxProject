#include "User.h"
#include"SessionMgr.h"

IMPLEMENT_DYNCREATE(User) 
IMPLEMENT_DYNMIC(User)

bool User::Dispatch(DWORD dwByteSize, OVERLAPPED_EX* OV)
{
	if(OV->iMode == MODE_RECV&& dwByteSize==0)
	{
		I_Session.DeleteUser(this);
		return false;
	}
	if (OV->iMode == MODE_RECV && dwByteSize == 0)
	{
		m_iRecvData += dwByteSize;

		if (!WaitZeroRecv())
		{
			return false;
		}
		return true;
	}
	if (OV->iMode==MODE_ZERORECV)
	{
		if (!WaitRecv())
		{
			return true;
		}
	}
	
	return true;
}
void User::DisConnect()
{
	closesocket(m_Sock);
}
OVERLAPPED_EX* User::Overlapped()
{
	ZeroMemory(&m_OV, sizeof(OVERLAPPED_EX));
	
	m_OV.iMode = MODE_RECV;
	m_WSARecvBuf.buf =&m_RecvBuffer[m_iRecvData];
	m_WSARecvBuf.len = MAX_USER_RECVSIZE;

	return &m_OV;
}

OVERLAPPED_EX* User::OverlappedZero()
{
	ZeroMemory(&m_ZeroOV, sizeof(OVERLAPPED_EX));

	m_ZeroOV.iMode = MODE_ZERORECV;
	ZeroMemory(&m_WSARecvBuf, sizeof(WSABUF));
	m_WSARecvBuf.buf = nullptr;
	m_WSARecvBuf.len = 0;
	
	return &m_ZeroOV;
}

bool User::WaitRecv()
{
	OVERLAPPED_EX* pOV;
	pOV = Overlapped();
	DWORD dwTransfer=0;
	DWORD dwFlags=0;
	int Ret=WSARecv(m_Sock, &m_WSARecvBuf,1, &dwTransfer, &dwFlags, (LPOVERLAPPED)pOV, NULL);

	if (Ret==SOCKET_ERROR)
	{
		if (WSAGetLastError()==ERROR_IO_PENDING)
		{
			return false;
		}
	}

	return true;
}
bool User::WaitZeroRecv()
{
	DWORD dwTrans;
	OVERLAPPED_EX* pOV;
	pOV = OverlappedZero();

	DWORD dwFlags = 0;
	int Ret = WSARecv(m_Sock, &m_WSARecvBuf,1, &dwTrans, &dwFlags, (LPOVERLAPPED)pOV, NULL);

	if (Ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return true;
}

User::User()
{
	m_iRecvData = 0;
	ZeroMemory(m_RecvBuffer, sizeof(m_RecvBuffer));
}


User::~User()
{
	closesocket(m_Sock);
}
