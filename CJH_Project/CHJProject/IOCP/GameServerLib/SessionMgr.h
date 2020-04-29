#pragma once
#include"Queue.h"
#include"JH_ServerStd.h"
#include"User.h"

#define MAX_QUEUE_COUNT 1000
typedef std::map<DWORD, User*> UserList;
typedef std::map<DWORD, User*>::iterator UserIter;

class SessionMgr:public Singleton<SessionMgr>
{
private:
	friend class  Singleton< SessionMgr>;
public:
	UserList m_UserList;
	Queue m_QueueList;
public:
	void RemoveSession(ServerObj*pSession);
	User* CreateSession();
	void AddUser(User*pUser);
	void Create();
public:

	SessionMgr();
	virtual ~SessionMgr();
};

#define I_Session SessionMgr::GetInstance()