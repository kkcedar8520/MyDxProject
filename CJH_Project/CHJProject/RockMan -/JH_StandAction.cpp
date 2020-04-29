#pragma once
#include"JH_StandAction.h"

void JH_StandAction::Process(JHObject* obj)
{

	m_pOwner->SetTransition(EVENT_STAGE1_START1);
	
}
JH_StandAction::~JH_StandAction()
{
}
