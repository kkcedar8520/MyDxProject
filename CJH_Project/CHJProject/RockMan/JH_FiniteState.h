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
	EVENT_FIND_TARGET = 0, // 타켓 발견
	EVENT_GAME_START,
	EVENT_PLAYER_DEAD,
	EVENT_STAGE1_FAIL,
	EVENT_STAGE2_FAIL,
	EVENT_KEY_INPUT,
	EVENT_LOST_TARGET,     // 타켓 소멸
	EVENT_STOPMOVE,        // 정지
	EVENT_HEALTH_DRYUP,    // 에너지소멸 
	EVENT_PATROL,          // 순찰
	EVENT_BE_ATTACKED,     // 피격
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

