#include "User.h"
#include"SessionMgr.h"

IMPLEMENT_DYNCREATE(User) 
IMPLEMENT_DYNMIC(User)

bool User::Dispatch(DWORD dwByteSize, OVERLAPPED_EX* OV)
{
	
	OVERLAPPED_EX* pOV = reinterpret_cast<OVERLAPPED_EX*>(OV);
	if(pOV->iMode == MODE_RECV&& dwByteSize==0)
	{
		delete pOV;
		//I_Session.DeleteUser(this);
		return false;
	}
	if (pOV->iMode == MODE_RECV && dwByteSize > 0)
	{
		delete pOV;
		m_iRecvData += dwByteSize;

		m_StreamPacket.Put(m_WSARecvBuf.buf, dwByteSize, this);
		if (m_StreamPacket.GetPacket(this)==false)
		{
			Disconnect();
			 return false;
		}
		if (!WaitZeroRecv())
		{
			return false;
		}
		return true;
	}
	if (pOV->iMode==MODE_ZERORECV)
	{
		delete pOV;
		if (!WaitRecv())
		{
			return true;
		}
	}
	delete pOV;
	return false;
}
void User::Disconnect()
{
	if (INVALID_SOCKET == m_Sock)
		return;

	shutdown(m_Sock, SD_BOTH);
	/// 즉각 해제
	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;
	/// no TCP TIME_WAIT
	if (SOCKET_ERROR == setsockopt(m_Sock, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{
		printf_s("[DEBUG] setsockopt linger option error: %d\n", GetLastError());
		return;
	}
	closesocket(m_Sock);
}


OVERLAPPED_EX* User::Overlapped()
{

	OVERLAPPED_EX* OV= new OVERLAPPED_EX(MODE_RECV);

	m_WSARecvBuf.buf =&m_RecvBuffer[m_iRecvData];
	m_WSARecvBuf.len = MAX_USER_RECVSIZE;

	return OV;
}

OVERLAPPED_EX* User::OverlappedZero()
{


	OVERLAPPED_EX* ZeroOV= new OVERLAPPED_EX(MODE_ZERORECV);

	ZeroMemory(&m_WSARecvBuf, sizeof(WSABUF));
	m_WSARecvBuf.buf = nullptr;
	m_WSARecvBuf.len = 0;
	
	return ZeroOV;
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
	m_dwCharacter = 0;
	m_iRecvData = 0;
	ZeroMemory(m_RecvBuffer, sizeof(m_RecvBuffer));
}


User::~User()
{
	closesocket(m_Sock);
}

std::ostream& operator<<(std::ostream& stream, User& u_Info)
{
	stream << u_Info.m_CharacterList.size();
	for(auto& Character: u_Info.m_CharacterList)
	{
		stream << Character.first;
		stream << Character.second;
	}

	return stream;
}