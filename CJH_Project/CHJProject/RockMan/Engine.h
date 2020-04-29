#pragma once
#include"HCore.h"
#include"JH_Std.h"
#include"Stage.h"
#include"StartScreen.h"
#include"GustStage.h"
#include"player.h"
using namespace std;
typedef vector<RECT> RT;
class Engine:public HCore
{
public:
	
	Stage* StageMgr;
	std::vector<Stage*> m_StageList;
	std::vector<RT> m_rtList;
	Player m_Player;
	JHObject m_UI;
	DWORD m_PlayerState;
	float PosX;
	float PosY;
public:
	//bool (*CutAway)(JHMapObj* stage);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	
	Engine();
	virtual ~Engine();
};

