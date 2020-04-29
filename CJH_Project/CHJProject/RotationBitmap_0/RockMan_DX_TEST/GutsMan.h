#pragma once
#include"JH_FSM.h"
#include"JH_Sprite.h"
#include"Enemy.h"

class GutsMan;
class GutsManState;


class GutsManState
{
protected:
	GutsMan* m_pOwner;
public:
	GutsManState(GutsMan*owner) :m_pOwner(owner)
	{

	}
	virtual ~GutsManState() {}
public:
	virtual void Process(JH_Model*obj) = 0;

};
typedef std::vector<RECT> rtList;
class GutsMan :public Enemy
{
public:
	int m_RandomNum;
	DWORD	m_GutManState;
	shared_ptr<GutsManState> m_pAction;
	shared_ptr<GutsManState> m_pActionList[STATE_COUNT];
	D3DXVECTOR3	m_GutsManPos;
public:
	float		m_fAttackSize;
public:
	bool Init();
	bool Frame();
	bool PostRender();
	void Process(JH_Model*user);
public:
	GutsMan();
	virtual ~GutsMan();
};

