#include "NetworkBase.h"



NetworkBase::NetworkBase()
{
	InitializeCriticalSection(&m_CS);
}


NetworkBase::~NetworkBase()
{
	DeleteCriticalSection(&m_CS);
}
