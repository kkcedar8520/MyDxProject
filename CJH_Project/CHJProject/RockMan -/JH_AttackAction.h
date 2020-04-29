#pragma once
#include"Enemy.h"
//extern class EnemyState;
//extern class Enemy;


class JH_AttackAction:public EnemyState
{
public:
	int m_pattern;
public:
	void Process(JHObject* obj);
public:
	JH_AttackAction(Enemy* owner): EnemyState(owner)
	{
		m_pattern = 0;
	}
	virtual ~JH_AttackAction();
};

