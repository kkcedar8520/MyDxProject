#include "Lock.h"



Lock::Lock(NetworkBase*obj) :m_pObj(obj)
{
	EnterCriticalSection(&m_pObj->m_CS);
}


Lock::~Lock()
{
	LeaveCriticalSection(&m_pObj->m_CS);
}
