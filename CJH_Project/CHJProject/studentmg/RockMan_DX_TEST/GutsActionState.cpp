#include "GutsActionState.h"




void GustActionState::Process(JH_Model*Player)
{
	switch (m_pOwner->m_RandomNum)
	{
	case 0:
		m_pOwner->m_dwEnemySate = DASH_ATTACK;
		m_pOwner->m_GutsManPos.x +
			m_pOwner->Frame();
	case 1:
		m_pOwner->m_dwEnemySate = STON_THROWING;
		m_pOwner->Frame();
	default:
		break;
	}
}
GustActionState::~GustActionState()
{
}

