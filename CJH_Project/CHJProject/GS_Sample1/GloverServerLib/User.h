#pragma once
#include"ServerObj.h"
#include"JH_StreamPaket.h"

#define MAX_WSA_BUFFER 1028
#define MAX_USER_RECVSIZE 4096
enum Mode
{
	MODE_ZERORECV = 0,
	MODE_RECV,
	MODE_SEND,
};
struct  OVERLAPPED_EX
{

	OVERLAPPED OV;
	int iMode;
	OVERLAPPED_EX(int iMode)
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = iMode;
	}
	OVERLAPPED_EX()
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = MODE_ZERORECV;
	}
};
class User:public ServerObj
{
public:

	OVERLAPPED_EX m_OV;
	OVERLAPPED_EX m_ZeroOV;
	SOCKET m_Sock;
	SOCKADDR_IN m_SockAddr;
	WSABUF m_WSARecvBuf;
	WSABUF m_WSASendBuf;
	int m_iRecvData;
	char m_RecvBuffer[MAX_USER_RECVSIZE];
public:
	DECLARE_DYNCREATE
	DECLARE_DYNMIC(User)
public:
	bool Dispatch(DWORD dByteSize,OVERLAPPED_EX* OV);
	bool WaitRecv();
	bool WaitZeroRecv();
	void DisConnect( );
	OVERLAPPED_EX* Overlapped();
	OVERLAPPED_EX* OverlappedZero();
	User();
	virtual ~User();
};

