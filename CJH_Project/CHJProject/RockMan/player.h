#pragma once
#include"JH_Std.h"
#include"JHObject.h"
#include"JHActor.h"
#include<Windows.h>

struct HPoint
{
	float x;
	float y;
};
enum PlayerState
{
	LEFTSTAND,
	RIGHTSTAND,
	LEFTRUN,
	RIGHTRUN,
	JUMP,
	BE_ATTACKED,
	BE_ATTACKED2,
	DEAD,
	COUNT,
};

typedef std::vector<RECT> RTList;
class Player :public JHObject
{
public:

	HDC m_StrechDC;
	vector<RECT>  m_rtList;
	vector<RTList>	  m_dRtList;
	int m_JSpriteIndex;
	int m_RSpriteIndex;
	int m_LSpriteIndex;
	int m_iSpriteIndex;

	bool b_Left;
	bool b_Jumping;
	bool b_Right;
	float   m_fOffestTime;
	float   m_fTimer;
	bool    m_bLoop;
	bool    m_bFinish;
	
	DWORD	m_dwPlayerSate;
	float	m_Jump;
public:
	void Set(
		vector<RECT>& rtList, float fTimer, bool bLoop)
	{
		m_fOffestTime = fTimer / rtList.size();
		m_rtList = rtList;
		m_bLoop = bLoop;
	}
	HPoint GetPositoin()
	{
		HPoint pos;
		pos.x = m_fPosX;
		pos.y = m_fPosY;
		return  pos;
	}
	void SetRTList(RTList RL)
	{
		m_rtList = RL;
	}
	DWORD &GetState()
	{
		return m_dwPlayerSate;
	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Player()
	{
		b_Left=0;
		b_Jumping=0;
		b_Right=0;
		m_iSpriteIndex;
	
		m_fTimer = 0.0f;
		m_fOffestTime = 0.1f;
		m_bFinish = true;
		m_Jump = 0;
	};
	virtual ~Player() {};
};

