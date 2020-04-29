#pragma once

#include"Enemy.h"


class JH_BeAttacked:public EnemyState
{
public:
	void Process(JHObject*);
public:
	JH_BeAttacked(Enemy* owner) :EnemyState(owner)
	{
	}
	virtual ~JH_BeAttacked();
};

