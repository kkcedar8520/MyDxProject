#pragma once


//#include "JH_ShapePlane.h"
#include "../../include/DX/JH_ShapePlane.h"
enum STATE
{
	STATE_STAND = 0,
	STATE_WAITING,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_DEAD,
	STATE_COMWIN,
	STATE_BE_ATTACKED,
	STATE_COUNT,
};

enum EVENT
{
	EVENT_FIND_TARGET = 0, // Ÿ�� �߰�
	EVENT_GAME_START,
	EVENT_GAME_END,
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
	EVENT_DASH_ATTACK,
	EVENT_STON_THROWING,
	EVENT_STAGE1_CLEAR,
	EVENT_STAGE2_CLEAR,
	EVENT_STAGE1_START1,
	EVENT_STAGE1_START2,
	EVENT_STAGE2_START,
	EVENT_COUNT,
};
enum SCREEN
{
	START_SCREEN = 0,
	CHARACTER_SLECT_SCREEN,
	STAGE_SLECT_SCREEN,
	GUSTMAN_SCREEN,
	SCREEN_COUNT,
};
enum SCREEN_EVENT
{
	EVENT_PRESSKEY = 0,
	EVENT_SELECT_CHARACTER,
	EVENT_SELECT_STAGE,
	EVENT_STAGE_CLEAR,
	EVENT_STAGE_FAILED,
	EVENT_ENDING,
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
	bool Release();
public:
	JH_FiniteState();
	virtual ~JH_FiniteState();
};


class JH_FSM
{
public:
	std::map<DWORD, JH_FiniteState*> m_MapList;
	typedef std::map<DWORD, JH_FiniteState*>::iterator mapiter;
public:
	DWORD output(DWORD dwState, DWORD dwEvent);
	void Input(DWORD dwState, DWORD dwEvent, DWORD dwOutput);
public:
	static JH_FSM&Get()
	{
		static JH_FSM mgr;
		return mgr;
	}
	bool Init();
	bool Release();
public:
	JH_FSM();
	virtual ~JH_FSM();
};
#define FSM JH_FSM::Get()
