#pragma once
#include"JH_FiniteState.h"
#include"Stage.h"
#include"JH_Std.h"
using namespace std;

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
public:
	JH_FSM();
	virtual ~JH_FSM();
};
#define FSM JH_FSM::Get()
