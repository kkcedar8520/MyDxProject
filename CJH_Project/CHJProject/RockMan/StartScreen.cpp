#pragma once
#include "StartScreen.h"

class StageSene;
class Stage;

void StartScreen::Process(JHObject*owner)
{


	m_pOwner->Load(L"bitmap/start.bmp");
	if (G_Input.KeyCheck(VK_RETURN))
	{
		m_pOwner->CutAway(EVENT_KEY_INPUT);
	
	}

	
}

StartScreen::~StartScreen()
{
}
