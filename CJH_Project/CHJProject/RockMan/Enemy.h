//#pragma once
//#include"JHObjList.h"
//#include"JH_Std.h"
//#include"JH_FiniteState.h"
//#include"JH_AttackAction.h"
//#include"JH_StandAction.h"
//#include"JH_FSM.h"
//class Enemy;
//
//class EnemyState
//{
//public:
//	EnemyState(Enemy*owner) :m_pOwner(owner)
//	{
//
//	}
//	virtual ~EnemyState(){}
//public:
//	virtual void Process(JHObject*obj) = 0;
//protected:
//	Enemy* m_pOwner;
//};
//
//class Enemy:public JHNpcObj
//{
//	DWORD		m_dwState;
//	EnemyState* m_pAction;
//	EnemyState* m_pActionList[STATE_COUNT];
//public:
//	float		m_fAttackSize;
//public:
//	bool Init();
//	bool Frame();
//	void Process(JHObject*user);
//	void SetTransition(DWORD dwEvent);
//public:
//	Enemy();
//	virtual ~Enemy();
//};
//
