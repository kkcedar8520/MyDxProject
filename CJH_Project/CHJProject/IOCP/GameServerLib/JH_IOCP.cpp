#include "JH_IOCP.h"

bool JH_IOCP::Init()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, MAX_THREAD_COUNT);
	return true;
}

bool JH_IOCP::AddSocket(HANDLE hSock,ULONG_PTR Key)
{
	::CreateIoCompletionPort(hSock, m_hIOCP, Key, 0);
	return true;
}
JH_IOCP::JH_IOCP()
{
}


JH_IOCP::~JH_IOCP()
{
}
