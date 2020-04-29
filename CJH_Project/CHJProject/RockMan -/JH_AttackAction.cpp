#pragma once

#include "JH_AttackAction.h"
#include<time.h>


void JH_AttackAction::Process(JHObject* user)
{
	srand(time(NULL));
	int iD = 0;
	if (m_pattern==0)
	{
		m_pattern = 1+rand() % 2;
	}
	if (m_pattern=1)
	{
		
		m_pOwner->Set(m_pOwner->m_dRtList[DASH_ATTACK], 1.0f, true);
		if (user->GetPositoin().x>m_pOwner->GetPositoin().x)
		{
			iD = 1;
			m_pOwner->m_fPosX = m_pOwner->m_fPosX*g_SecondPerFrame*iD*200;
		}
		m_pOwner->Frame();
	}
}

JH_AttackAction::~JH_AttackAction()
{
}
