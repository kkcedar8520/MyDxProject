#pragma once
#include"JH_ServerStd.h"


struct RuntimeClass
{
	char file
};
class ServerObj
{
public:
	CRITICAL_SECTION m_CS;
public:
	ServerObj();
	virtual ~ServerObj();
};

