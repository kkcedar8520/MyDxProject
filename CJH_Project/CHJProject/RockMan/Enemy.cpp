#pragma once
//#include "Enemy.h"
//
//bool Enemy::Init()
//{
//	JHNpcObj::Init();
//	m_dwState = STATE_STAND;
//
//	m_pActionList[STATE_STAND] = new JH_StandAction(this);
//	m_pActionList[STATE_ATTACK] = new JH_AttackAction(this);
//
//	m_pAction = m_pActionList[m_dwState];
//
//}
//bool Enemy::Frame()
//{
//	return true;
//}
//void Enemy::Process(JHObject*user)
//{
//	m_pAction->Process(user);
//
//}
//void Enemy::SetTransition(DWORD dwEvent)
//{
//	m_dwState = FSM.output(m_dwState, dwEvent);
//	m_pAction = m_pActionList[m_dwState];
//
//}
//
//Enemy::Enemy()
//{
//}
//
//
//Enemy::~Enemy()
//{
//}
