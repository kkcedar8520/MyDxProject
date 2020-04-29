#pragma once
#include"GutsMan.h"
class GustActionState:public GutsManState
{
public:
	void Process(JH_Model*Player) override;
	GustActionState(GutsMan* owner) :GutsManState(owner)
	{
		
	}
	virtual ~GustActionState();
};

