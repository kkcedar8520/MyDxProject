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

	

	Input(STATE_STAND,EVENT_GAME_START,STATE_ATTACK);

	Input(STATE_ATTACK, EVENT_RAGE_MODE, STATE_ATTACK);
	Input(STATE_ATTACK, EVENT_HEALTH_DRYUP, STATE_WAITING);
	

		return true;
}
JH_FSM::JH_FSM()
{
}


JH_FSM::~JH_FSM()
{
}
