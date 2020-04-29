#pragma once
#include"GutsMan.h"
#include"JH_Map.h"

class GutsStandState:public GutsManState
{
public:
	GutsStandState(GutsMan* owner):GutsManState(owner)
	{
		
	}
	void Process(JH_Model*Player);
	virtual ~GutsStandState();
};

