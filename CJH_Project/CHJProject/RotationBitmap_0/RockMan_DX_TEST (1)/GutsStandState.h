#pragma once
#include"GutsMan.h"

class GutsStandState:public GutsManState
{
public:
	GutsStandState(GutsMan* owner):GutsManState(owner)
	{
		
	}
	void Process(JH_Model*Player);
	virtual ~GutsStandState();
};

