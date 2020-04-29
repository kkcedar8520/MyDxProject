#include "PakcetPool.h"


bool PakcetPool::AddPacket(UPACKET Packet)
{
	
	m_PaketList.push_back(Packet);
	return true;
}
bool PakcetPool::PacketClear()
{
	m_PaketList.clear();
	return true;
}
PakcetPool::PakcetPool()
{
	m_hMutex = CreateMutex(NULL, 1,L"PacketMutex");
}


PakcetPool::~PakcetPool()
{
	ReleaseMutex(m_hMutex);
}
