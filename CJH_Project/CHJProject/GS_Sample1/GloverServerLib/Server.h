#pragma once
#include"JH_Thread.h"
#include"Acceptor.h"
#include"SessionMgr.h"
#include"JH_IOCP.h"
class Server:public JH_Thread,public Singleton<Server>
{
private:
	friend class  Singleton<Server>;
public:
	Acceptor m_Acceptor;
public:
	bool Init();
	bool Release();
	bool Run()override;
public:
	Server();
	virtual ~Server();
};

