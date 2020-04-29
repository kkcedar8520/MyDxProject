#pragma once
#include "Enemy.h"



bool Enemy::Init()
{
	JHObject::Init();

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
void Enemy::Process(JHObject*user)
{
	m_pAction->Process(user);

}
void Enemy::SetTransition(DWORD dwEvent)
{
	m_dwEnemySate = FSM.output(m_dwEnemySate, dwEvent);
	m_pAction = m_pActionList[m_dwEnemySate];

}

Enemy::Enemy()
{
	m_iSpriteindex = 0;
}


Enemy::~Enemy()
{
}
