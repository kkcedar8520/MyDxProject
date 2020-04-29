#pragma once
#include "Stage.h"
#include"StartScreen.h"
#include"GustStage.h"

bool Stage::Init()
{
	JHMapObj::Init();
	m_dwSene = SENE_START;

	m_pMapList[SENE_START] = new StartScreen(this);

	m_pMapList[SENE_GUST] = new GustStage(this);

	m_pMapSene = m_pMapList[m_dwSene];
	return true;
}
void Stage::CutAway(DWORD dwEvent)
{
	m_dwSene = FSM.output(m_dwSene, dwEvent);
	m_pMapSene = m_pMapList[m_dwSene];

}
void Stage::Process(JHObject* obj)
{
	m_pMapSene->Process(obj);
}

Stage::Stage()
{
}


Stage::~Stage()
{
}
