#include "JH_IOCP.h"

bool JH_IOCP::Init()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, MAX_THREAD_COUNT);

	for (int  i = 0; i < MAX_THREAD_COUNT; i++)
	{
		m_WorkerThreadHandle[i].CreateThread();
	}
	return true;
}

void JH_IOCP::AddSocket(HANDLE hSock,ULONG_PTR Key)
{
	::CreateIoCompletionPort(hSock, m_hIOCP, Key, 0);

}
JH_IOCP::JH_IOCP()
{
}


JH_IOCP::~JH_IOCP()
{
}
