#pragma once
#include"ServerObj.h"
class User:public ServerObj
{
public:
	SOCKET m_Sock;
public:
	void DisConnect();
	User();
	virtual ~User();
};

