#pragma once
#include"JH_ServerStd.h"

#define DECLARE_DYNCREATE static ServerObj* CreateObj();
#define DECLARE_DYNMIC(s) static RuntimeClass class##s;

#define IMPLEMENT_DYNCREATE ServerObj* s::CreateObj(){return s;};
#define IMPLEMENT_DYNMIC(s) RuntimeClass s::class##s={#s,sizeof(s),s::CreateObj()};

struct RuntimeClass
{
	char m_lpszClassName[30];
	int ClassSZ;
	ServerObj* (*ptrfunction)();
	
	ServerObj* CreateObj()
	{
		return (*ptrfunction)();
	}
};
class ServerObj
{
public:
	CRITICAL_SECTION m_CS;
public:
	ServerObj();
	virtual ~ServerObj();
};

