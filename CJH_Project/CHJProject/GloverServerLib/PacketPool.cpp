#include "PacketPool.h"


bool PacketPool::AddPacket(JPACKET Packet)
{
	
	m_PacketList.push_back(Packet);
	return true;
}
bool PacketPool::PacketClear()
{
	m_PacketList.clear();
	return true;
}
void PacketPool::Lock()
{
	if (InterlockedExchange(&m_iLockCheck, 1) != 0)
	{
		//	T_LOG("%s\r\n", "DeadLock!! PacketPool");
	}
	WaitForSingleObject(m_hMutex, INFINITE);
}
void  PacketPool::Unlock()
{
	ReleaseMutex(m_hMutex);
	InterlockedExchange(&m_iLockCheck, 0);
}
std::list<JPACKET>& PacketPool::Get()
{
	return m_PacketList;
}

PacketPool::PacketPool()
{
	m_hMutex = CreateMutex(NULL, 1,L"PacketMutex");
}


PacketPool::~PacketPool()
{
	ReleaseMutex(m_hMutex);
}
