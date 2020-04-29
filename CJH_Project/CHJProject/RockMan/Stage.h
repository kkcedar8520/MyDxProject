#pragma once
#include"JHMapObj.h"
#include"JH_FSM.h"
class Stage;
enum Sene
{
	SENE_START = 0,
	SENE_GUST,
	SENE_BOSS,
	SENE_ENDING,
	SENE_COUNT,
};

class StageSene
{
public:
	StageSene(Stage*owner):m_pOwner(owner), m_flag(1)
	{
		
	}
	virtual ~StageSene(){}
public:
	virtual void Process(JHObject*) = 0;
protected:
	Stage* m_pOwner;
	DWORD m_flag;
};
class Stage :public JHMapObj //스테이지 관리
{
public:
	DWORD m_dwSene;
	StageSene* m_pMapSene;
	StageSene* m_pMapList[SENE_COUNT];// 스테이지 저장
public:
	bool Init();
	void Process(JHObject* User);
	void CutAway(DWORD dwEvent);
	Stage();
	virtual ~Stage();
};

