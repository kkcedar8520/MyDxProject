#pragma once
#include"Enemy.h"
//extern  EnemyState;
//extern  Enemy;

class JH_StandAction:public EnemyState
{
public:
	void Process(JHObject* obj);
public:
	JH_StandAction(Enemy* owner)
		: EnemyState(owner)
	{
	}
	virtual ~JH_StandAction();
};

