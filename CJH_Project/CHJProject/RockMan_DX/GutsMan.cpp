#pragma once
#include "GutsMan.h"
#include"GutsStandState.h"
#include"GutsActionState.h"
#include<time.h>

bool GutsMan::Init()
{
	JH_Model::Init();
	m_GutManState = G_STAND;

	m_dwEnemySate = STATE_STAND;

	m_pActionList[STATE_STAND] = make_shared<GutsStandState>(this);
	m_pActionList[STATE_ATTACK] = make_shared<GustActionState>(this);

	m_pAction = m_pActionList[m_dwEnemySate];

	m_VectorList.resize(GCOUNT);
	m_VectorList[G_STAND].resize(1);
	m_VectorList[COM_WIN].resize(2);
	m_VectorList[DASH_ATTACK].resize(3);
	m_VectorList[STON_THROWING].resize(8);
	m_VectorList[BE_DAMAGED].resize(1);



	m_VectorList[G_STAND][0] = { 300,106,98,71 };

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

	srand(time(NULL));
	m_RandomNum = rand() % 3;


	SetArrayRect(m_VectorList,495,660,1.0f);
	return  true;
}
bool  GutsMan::Frame()
{
	m_iIndex = 0;
	m_fTimer += g_SecondPerFrame;
	if (m_fTimer > 0.5f / m_VectorList[m_GutManState].size())
	{
		m_fTimer -= 0.5f / m_VectorList[m_GutManState].size();
		m_iIndex++;
	}
	if (m_iIndex >= m_VectorList[m_GutManState].size())
	{
		m_iIndex = 0;
		m_fTimer = 0;
		m_GutManState = G_STAND;
		m_RandomNum = rand() % 3;
	}
	return true;
}

void GutsMan::Process(JH_Model*user)
{
	m_pAction->Process(user);

}
bool GutsMan::PostRender()
{
	/*m_VertexData[0].t = m_uvList[m_GutManState][m_iIndex].uv[0];
	m_VertexData[1].t = m_uvList[m_GutManState][m_iIndex].uv[1];
	m_VertexData[2].t = m_uvList[m_GutManState][m_iIndex].uv[2];
	m_VertexData[3].t = m_uvList[m_GutManState][m_iIndex].uv[3];

	m_VertexData[0].p.x = m_GutsManPos.x - m_VectorList[m_GutManState][m_iIndex].right;
	m_VertexData[0].p.y = m_GutsManPos.y + m_VectorList[m_GutManState][m_iIndex].bottom * 2;
	m_VertexData[1].p.x = m_GutsManPos.x + m_VectorList[m_GutManState][m_iIndex].right;
	m_VertexData[1].p.y = m_GutsManPos.y + m_VectorList[m_GutManState][m_iIndex].bottom * 2;
	m_VertexData[2].p.x = m_GutsManPos.x - m_VectorList[m_GutManState][m_iIndex].right;
	m_VertexData[2].p.y = m_GutsManPos.y;			   
	m_VertexData[3].p.x = m_GutsManPos.x + m_VectorList[m_GutManState][m_iIndex].right;
	m_VertexData[3].p.y = m_GutsManPos.y;*/
	return true;
}
GutsMan::GutsMan()
{
	m_GutManState = 0;
	m_GutsManPos=D3DXVECTOR3(0,0,0);
	m_dwEnemySate = STATE_STAND;
	m_RandomNum = 0;
}


GutsMan::~GutsMan()
{
}
