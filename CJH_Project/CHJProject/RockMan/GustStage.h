#pragma once
#include"Stage.h"
class StageSene;
class Stage;

class GustStage:public StageSene
{
public:
	void Process(JHObject*Obj);
public:

	GustStage(Stage*owner) :StageSene(owner)
	{
		
	}
	virtual ~GustStage();
};

