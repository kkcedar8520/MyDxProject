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
	Input(SENE_START, EVENT_KEY_INPUT, SENE_GUST);

	Input(SENE_GUST,EVENT_STAGE1_CLEAR, SENE_BOSS);
	Input(SENE_GUST, EVENT_STAGE1_FAIL, SENE_START); //스테이지 장면 전환 흐름제어

	Input(SENE_BOSS, EVENT_STAGE2_CLEAR, SENE_ENDING);
	Input(SENE_BOSS, EVENT_STAGE2_FAIL, SENE_START);

	
	Input(STATE_STAND, EVENT_STAGE1_START1, STATE_ATTACK);
	Input(STATE_STAND, EVENT_STAGE1_START2, STATE_ATTACK);
	Input(STATE_STAND, EVENT_GAME_END, SENE_START);

	Input(STATE_ATTACK, EVENT_DASH_ATTACK, STATE_ATTACK);
	Input(STATE_ATTACK, EVENT_STON_THROWING, STATE_ATTACK);
	Input(STATE_ATTACK, EVENT_PLAYER_DEAD, STATE_STAND);
	Input(STATE_ATTACK, EVENT_HEALTH_DRYUP, STATE_DEAD);
	
	Input(STATE_DEAD, EVENT_STAGE2_START, SENE_BOSS);
		return true;
}
bool JH_FSM::Release()
{
	/*for(mapiter iter = m_MapList.begin();iter!=m_MapList.end();)
	{
		iter->second->Release();
		iter = m_MapList.erase(iter);
	}*/
	return true;
}

JH_FSM::JH_FSM()
{
}


JH_FSM::~JH_FSM()
{
}
