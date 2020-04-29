#pragma once
#include"JH_FSM.h"
#include"JH_Sprite.h"
#include"Enemy.h"
#include"GutsStandState.h"
class GutsMan;
class EnemyState;


class GutsManState
{
public:
	GutsManState(GutsMan*owner) :m_pOwner(owner)
	{

	}
	virtual ~GutsManState() {}
public:
	virtual void Process(JH_Model*obj) = 0;
protected:
	GutsMan* m_pOwner;
};
typedef std::vector<RECT> rtList;
class GutsMan :public Enemy
{
public:
	float		m_fTimer;
	bool		b_Left;
	DWORD	m_dwEnemySate;
	shared_ptr<GutsManState> m_pAction;
	shared_ptr<GutsManState> m_pActionList[STATE_COUNT];
	int			m_iSpriteindex;
public:
	float		m_fAttackSize;
public:
	bool Init();
	bool Frame();
	bool Render();
	void Process(JH_Model*user);
public:
	GutsMan();
	virtual ~GutsMan();
};

