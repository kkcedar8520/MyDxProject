#pragma once
#include"GutsMan.h"
class GustActionState:public GutsManState
{
public:
	GustActionState(GutsMan* owner) :GutsManState(owner)
	{
		
	}
	virtual ~GustActionState();
};

