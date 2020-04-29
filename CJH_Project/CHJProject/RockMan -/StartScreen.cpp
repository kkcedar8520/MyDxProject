#pragma once
#include "StartScreen.h"

class StageSene;
class Stage;

void StartScreen::Process(JHObject*owner)
{


	if (G_Input.KeyCheck(VK_RETURN))
	{
		
		m_pOwner->CutAway(EVENT_KEY_INPUT);
	
	}

	
}

StartScreen::~StartScreen()
{
}
