
#include "ServerObj.h"


ServerObj::ServerObj()
{
	InitializeCriticalSection(&m_CS);
}


ServerObj::~ServerObj()
{
	DeleteCriticalSection(&m_CS);
}
