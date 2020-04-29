#pragma once
#include"JH_StreamPaket.h"
class PakcetPool
{
public:
	HANDLE m_hMutex;
	std::list<UPACKET> m_PaketList;
public:
	bool AddPacket(UPACKET Packet);
	bool PacketClear();
public:

	PakcetPool();
	virtual ~PakcetPool();
};

