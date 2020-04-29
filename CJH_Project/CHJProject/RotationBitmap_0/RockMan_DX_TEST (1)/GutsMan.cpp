#pragma once
#include "GutsMan.h"



bool GutsMan::Init()
{
	JH_Model::Init();
	m_dwEnemySate = STAND;


	m_pActionList[STAND] = make_shared<GutsStandState>(this);

	m_pAction = m_pActionList[m_dwEnemySate];

	m_VectorList.resize(GCOUNT);
	m_VectorList[STAND].resize(1);
	m_VectorList[COM_WIN].resize(2);
	m_VectorList[DASH_ATTACK].resize(3);
	m_VectorList[STON_THROWING].resize(8);
	m_VectorList[BE_DAMAGED].resize(1);



	m_VectorList[STAND][0] = { 300,106,98,71 };

	m_VectorList[COM_WIN][0] = { 396,106,98,73 };
	m_VectorList[COM_WIN][1] = { 372,180,94,91 };

	m_VectorList[DASH_ATTACK][0] = { 103,584,97,53 };
	m_VectorList[DASH_ATTACK][1] = { 12,579,91,60 };
	m_VectorList[DASH_ATTACK][2] = { 200,573,93,63 };

	m_VectorList[STON_THROWING][0] = { 12,326,89,113 };
	m_VectorList[STON_THROWING][1] = { 100,344,94,98 };
	m_VectorList[STON_THROWING][2] = { 196,346,94,98 };
	m_VectorList[STON_THROWING][3] = { 290,344,94,103 };
	m_VectorList[STON_THROWING][4] = { 383,334,90,116 };
	m_VectorList[STON_THROWING][5] = { 9,451,89,112 };
	m_VectorList[STON_THROWING][6] = { 98,470,146,91 };
	m_VectorList[STON_THROWING][7] = { 244,508,102,53 };

	m_VectorList[BE_DAMAGED][0] = { 252,245,112,86 };

	SetArrayRect(m_VectorList,495,660,1.0f);
	return  true;
}
bool  GutsMan::Frame()
{
	
	return true;
}

void GutsMan::Process(JH_Model*user)
{
	m_pAction->Process(user);

}
bool GutsMan::Render()
{

	return true;
}
GutsMan::GutsMan()
{
	m_dwEnemySate = STATE_STAND;
}


GutsMan::~GutsMan()
{
}
