#pragma once
#include"Stage.h"
class StageSene;
class Stage;

class GustStage:public StageSene
{
	int m_iCheck;
public:
	void Process(JHObject*Obj);
public:

	GustStage(Stage*owner) :StageSene(owner)
	{
		m_iCheck = 0;
	}
	virtual ~GustStage();
};

