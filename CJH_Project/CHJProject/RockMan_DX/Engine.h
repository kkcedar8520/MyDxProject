#pragma once
#include"JHDXCore.h"
#include"JH_Player.h"
#include"JH_Map.h"
#include"JH_Screen.h"
#include"GutsMan.h"
class Engine:public JHDXCore
{
public:

public:
	shared_ptr < JH_Player> m_Player;
	//shared_ptr<JH_Map>	m_Map;
	JH_Map m_Map;
	shared_ptr<GutsMan> m_GutsMan;
	DWORD	m_CorrentStage;
	shared_ptr<JH_Screen>m_Stage;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Engine();
	virtual ~Engine();
};

