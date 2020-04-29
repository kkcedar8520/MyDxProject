#include "WorkerThread.h"
#include"JH_IOCP.h"
#include"User.h"
#include"SessionMgr.h"


bool WorkerThread::Run()
{
	
	DWORD dwTransfer=0;
	ULONG_PTR Key;
	OVERLAPPED* OV;
	bool Ret;
	while (bStart)
	{
		Ret = ::GetQueuedCompletionStatus(I_IOCP.m_hIOCP, &dwTransfer, &Key, &OV, 1);

		User* pSession = (User*)Key;
		OVERLAPPED_EX* pOV = (OVERLAPPED_EX*)OV;

		if (Ret==TRUE&& pSession !=nullptr&&OV!=NULL)
		{
			if (pSession->Dispatch(dwTransfer, pOV) == false)
			{
				I_Session.DeleteUser(pSession);
			}
			continue;
		}
		else
		{
			DWORD dwError = WSAGetLastError();
			if (dwError != ERROR_OPERATION_ABORTED&& dwError != WAIT_TIMEOUT)
			{
				
				if (pOV!=nullptr)
				{
					delete pOV;
				}
				if (pSession!=nullptr)
				{
					I_Session.DeleteUser(pSession);
				}
			}
			
		}
	}

	return true;
}
WorkerThread::WorkerThread()
{
	bLoop = true;
}


WorkerThread::~WorkerThread()
{
	bLoop = false;
}
