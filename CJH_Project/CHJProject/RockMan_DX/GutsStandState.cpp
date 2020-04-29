#include "GutsStandState.h"



void GutsStandState::Process(JH_Model*Player)
{
	
	if (I_Map->m_CorrentStage!=START)
	{
		
	}
	
	m_pOwner->SetTransition(EVENT_STAGE1_START1);
}


GutsStandState::~GutsStandState()
{
}
