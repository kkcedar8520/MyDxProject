#pragma once
#include "JH_Std.h"
using namespace std;
enum STATE
{
	STATE_STAND = 0,
	STATE_WAITING,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_END,
	STATE_COUNT,
	
};
enum EVENT
{
	EVENT_FIND_TARGET = 0, // Ÿ�� �߰�
	EVENT_GAME_START,
	EVENT_PLAYER_DEAD,
	EVENT_STAGE1_FAIL,
	EVENT_STAGE2_FAIL,
	EVENT_KEY_INPUT,
	EVENT_LOST_TARGET,     // Ÿ�� �Ҹ�
	EVENT_STOPMOVE,        // ����
	EVENT_HEALTH_DRYUP,    // �������Ҹ� 
	EVENT_PATROL,          // ����
	EVENT_BE_ATTACKED,     // �ǰ�
	EVENT_RAGE_MODE,
	EVENT_STAGE1_CLEAR,
	EVENT_STAGE2_CLEAR,
	EVENT_STAGE_START,
	EVENT_COUNT,
};
class JH_FiniteState
{
	DWORD m_dwstate;
	std::map<DWORD, DWORD> m_Statemap;
public:
	void Input(DWORD Event, DWORD Output)
	{
		m_Statemap[Event] = Output;
	}

	DWORD Output(DWORD Event)
	{
		return m_Statemap[Event];
	}
public:
	JH_FiniteState();
	virtual ~JH_FiniteState();
};

