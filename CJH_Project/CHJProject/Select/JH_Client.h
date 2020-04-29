#pragma once
#include"NetworkClient.h"

class JH_Client:public NetworkClient
{
public:
	WSAEVENT m_hEventObject;
	
public:
	bool EventRun();
	bool SelectRun();
	bool Run()override;
public:
	JH_Client();
	virtual ~JH_Client();
};

