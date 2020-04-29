#pragma once
#include"SpriteObj.h"
#include"JH_FSM.h"
#include"Collision.h"
class Enemy;
class EnemyState;

enum Guts
{
	STAND = 0,
	COM_WIN,
	DASH_ATTACK,
	STON_THROWING,
	BE_DAMAGED,
	GCOUNT,
};
class EnemyState
{
public:
	EnemyState(Enemy*owner) :m_pOwner(owner)
	{

	}
	virtual ~EnemyState(){}
public:
	virtual void Process(JHObject*obj) = 0;
protected:
	Enemy* m_pOwner;
};
typedef std::vector<RECT> RTList;


class Enemy:public SpriteObj
{
public:
	float		m_fTimer;
	bool		b_Left;
	DWORD	m_dwEnemySate;
	EnemyState* m_pAction;
	EnemyState* m_pActionList[STATE_COUNT];
	int			m_iSpriteindex;
public:
	float		m_fAttackSize;
public:
	bool Init();
	bool Frame();
	bool Render();
	void Process(JHObject*user);
	void SetTransition(DWORD dwEvent);
public:
	Enemy();
	virtual ~Enemy();
};

