#pragma once
#include "Enemy.h"



bool Enemy::Init()
{
	JH_Model::Init();
	m_dwEnemySate = STAND;
	return  true;
}
bool  Enemy::Frame()
{

	return true;
}
bool Enemy::Render()
{

	return true;
}
void Enemy::Process(JH_Model*user)
{
	m_pAction->Process(user);

}
void Enemy::SetTransition(DWORD dwEvent)
{
	m_dwEnemySate = FSM.output(m_dwEnemySate, dwEvent);
	m_pAction = m_pActionList[m_dwEnemySate];

}

bool Enemy::SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime)
{



	for (int i = 0; i < GCOUNT; i++)
	{
		m_iNumSpriteIndex = DrtList[i].size();
		for (int rtN = 0; rtN < m_iNumSpriteIndex; rtN++)
		{
			JRECT rt;
			ZeroMemory(&rt, sizeof(JRECT));
			rt.uv[0].x = DrtList[i][rtN].left / (float)width;
			rt.uv[0].y = DrtList[i][rtN].top / (float)height;
			rt.uv[1].x = (DrtList[i][rtN].left + DrtList[i][rtN].right) / (float)width;
			rt.uv[1].y = DrtList[i][rtN].top / (float)height;
			rt.uv[2].x = DrtList[i][rtN].left / (float)width;
			rt.uv[2].y = (DrtList[i][rtN].top + DrtList[i][rtN].bottom) / (float)height;
			rt.uv[3].x = (float)rt.uv[1].x;
			rt.uv[3].y = (float)rt.uv[2].y;


			m_uvList[i].push_back(rt);
		}
		m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
	}
	return true;
}
Enemy::Enemy()
{
	m_iSpriteindex = 0;
}


Enemy::~Enemy()
{
}
