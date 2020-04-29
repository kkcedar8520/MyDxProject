#pragma once
#include"JH_Sprite.h"
#include"JH_FSM.h"
#include"JH_Model.h"
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
	virtual void Process(JH_Model*obj) = 0;
protected:
	Enemy* m_pOwner;
};
typedef std::vector<RECT> rtList;
class Enemy:public JH_Sprite
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
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual void Process(JH_Model*user);
	virtual void SetTransition(DWORD dwEvent);
	virtual bool SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime);
public:
	Enemy();
	virtual ~Enemy();
};

