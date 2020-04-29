#include "SessionMgr.h"

void SessionMgr::Create()
{
	for ( int i = 0;  i < MAX_QUEUE_COUNT;  i++)
	{
		ServerObj* Obj = CreateObj();
		m_QueueList.Push()
	}
}

void SessionMgr::RemoveSession(ServerObj*pSession)
{
	m_QueueList.Push(pSession);
}
void  SessionMgr::AddUser(User* pUser)
{
	m_UserList.insert(make_pair())
}
User*  SessionMgr::CreateSession()
{
	User* NewSession = dynamic_cast<User*>(m_QueueList.Pop);
	return NewSession;
}


SessionMgr::SessionMgr()
{
}


SessionMgr::~SessionMgr()
{
}
