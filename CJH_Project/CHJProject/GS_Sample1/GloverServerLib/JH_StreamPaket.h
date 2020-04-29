#pragma once

#include"JH_ServerStd.h"
class JH_StreamPacket
{
public:
	char Recvbuffer[PACKET_MAX_SIZE];
	long long iWritePos;
	char* pWritePos;
	UPACKET* m_pRecvPacket;
public:

	bool AddPacket(const char* RecvBuffer, int DataSize);
	bool RecvData();
public:
	JH_StreamPacket();
	virtual ~JH_StreamPacket();
};

