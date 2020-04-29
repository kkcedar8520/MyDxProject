#pragma once
#include "JH_FSM.h"

void  JH_FSM::Input(DWORD dwState, DWORD dwEvent, DWORD dwOutput)
{
	JH_FiniteState* state = nullptr;
	mapiter iter = m_MapList.find(dwState);
	if (iter == m_MapList.end())
	{
		state = new JH_FiniteState;
		m_MapList[dwState] = state;
	}
	else
	{
		state = (JH_FiniteState*)iter->second;
	}

	state->Input(dwEvent, dwOutput);
}
DWORD JH_FSM::output(DWORD dwState, DWORD dwEvent)
{
	JH_FiniteState* state = m_MapList[dwState];
	return state->Output(dwEvent);
}
bool JH_FSM::Init()
{
	// GutsMan
	Input(STATE_STAND, EVENT_STAGE1_START1, STATE_ATTACK);
	Input(STATE_STAND, EVENT_STAGE1_START2, STATE_ATTACK);
	Input(STATE_STAND, EVENT_GAME_END,STATE_DEAD);

	Input(STATE_ATTACK, EVENT_DASH_ATTACK, STATE_ATTACK);
	Input(STATE_ATTACK, EVENT_STON_THROWING, STATE_ATTACK);
	Input(STATE_ATTACK, EVENT_PLAYER_DEAD, STATE_STAND);
	Input(STATE_ATTACK, EVENT_HEALTH_DRYUP, STATE_DEAD);
	
	Input(STATE_DEAD, EVENT_STAGE2_START, STATE_STAND);

	//Stage
	Input(START_SCREEN, EVENT_PRESSKEY, CHARACTER_SLECT_SCREEN);
	Input(CHARACTER_SLECT_SCREEN, EVENT_SELECT_CHARACTER, GUSTMAN_SCREEN);


		return true;
}
bool JH_FSM::Release()
{
	for(mapiter iter = m_MapList.begin();iter!=m_MapList.end();)
	{
		iter->second->Release();
		iter = m_MapList.erase(iter);
	}
	return true;
}

JH_FSM::JH_FSM()
{
}


JH_FSM::~JH_FSM()
{
}
