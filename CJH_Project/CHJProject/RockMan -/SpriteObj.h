#pragma once
#include"JH_Std.h"
#include"JHObject.h"
typedef std::vector<RECT> RTList;
using namespace std;
class SpriteObj :public JHObject
{
public:
	float	 m_fTimer;
	int		m_SpriteIndex;
	float	m_fOffSetTime;
	float	m_fSpeed;
	RECT	m_rtEffectSrc;
	vector<RECT>	m_rtList;
	vector<RECT>	m_rtList_2;
	vector<RTList>	m_dRtList;
public:
	void SetSrcRect(
		vector<RECT>& rtList, float fTimer, float bLoop)
	{
		m_fOffSetTime = fTimer / rtList.size();
		m_rtList = rtList;
	}
	void Set(
		vector<RECT>& rtList, float fTimer, bool bLoop)
	{
		m_fOffsetTime = fTimer / rtList.size();
		m_rtList = rtList;

	}
	void SetRTList(RTList RL,RTList RLa)
	{
		m_rtList = RL;
		m_rtList_2 = RLa;
	}

	void SetRTList(RTList RL)
	{
		m_rtList = RL;

	}
	bool Init()
	{
		JHObject::Init();

		return true;
	}

public:
	SpriteObj()
	{
		float m_fSpeed = 500;
		float m_fTimer = 0;
		int m_SpriteIndex=0;
		float m_fOffSetTime=0;
	}
	virtual ~SpriteObj();
};

