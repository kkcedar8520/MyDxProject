#include "SessionMgr.h"
#include"JH_IOCP.h"
void SessionMgr::Create(RuntimeClass* Rt)
{
	for ( int i = 0;  i < MAX_QUEUE_COUNT;  i++)
	{
		ServerObj* Obj = Rt->CreateObj();
		m_QueueList.Push(Obj);
	}
}
void SessionMgr::Lock()
{
	WaitForSingleObject(m_hMutex,INFINITE);
}
void SessionMgr::UnLock()
{
	ReleaseMutex(m_hMutex);
}
void SessionMgr::ReleaseAll()
{
	Lock();
	for (UserIter iter = m_UserList.begin(); iter != m_UserList.end(); iter++)
	{
		iter->second->DisConnect();
		RemoveSession(iter->second);
	}
	m_UserList.clear();
	UnLock();
}
void SessionMgr::DeleteUser(SOCKET sock)
{
	Lock();
	UserIter iter=m_UserList.find(sock);
	if (iter!= m_UserList.end())
	{
		RemoveSession(iter->second);
		m_UserList.erase(sock);
	}

	UnLock();
}
void SessionMgr::DeleteUser(User*pUser)
{
	DeleteUser(pUser->m_Sock);
}
void SessionMgr::RemoveSession(ServerObj*pSession)
{
	m_QueueList.Push(pSession);
}

void  SessionMgr::AddUser(User* pUser)
{
	Lock();
	m_UserList.insert(std::make_pair(pUser->m_Sock, pUser));
	I_IOCP.AddSocket((HANDLE)pUser->m_Sock, (ULONG_PTR)pUser);
	pUser->WaitZeroRecv();
	//pUser->WaitRecv();
	UnLock();
}


void  SessionMgr::CreateSession(SOCKET SOCK, SOCKADDR_IN sockaddr)
{
	User* NewSession = dynamic_cast<User*>(m_QueueList.Pop());
	NewSession->m_Sock = SOCK;
	NewSession->m_SockAddr = sockaddr;
	AddUser(NewSession);
	
}


SessionMgr::SessionMgr()
{
	m_hMutex = CreateMutex(NULL, FALSE, _T("SessionMgr"));
}


SessionMgr::~SessionMgr()
{
	ReleaseAll();
	CloseHandle(m_hMutex);
	while (m_QueueList.m_ObjList.size()>0)
	{
		ServerObj* pObj=m_QueueList.Pop();
		delete pObj;
	}
}
