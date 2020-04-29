#include "Lock.h"



Lock::Lock(ServerObj*Obj)
{
	m_ServerObj = Obj;
	EnterCriticalSection(&m_ServerObj->m_CS);
}


Lock::~Lock()
{
	LeaveCriticalSection(&m_ServerObj->m_CS);
}
