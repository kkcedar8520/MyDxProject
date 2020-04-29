#pragma once
#include"Stage.h"
#include"JH_Input.h"
class StageSene;
class Stage;

class StartScreen:public StageSene
{
public:
	void Process(JHObject* Obj);
public:
	StartScreen(Stage* owner) :StageSene(owner)
	{
	}
	virtual ~StartScreen();
};

