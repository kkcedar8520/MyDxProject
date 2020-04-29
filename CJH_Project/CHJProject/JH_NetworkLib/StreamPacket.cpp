#pragma once
#include "StreamPacket.h"
#include"Network.h"

bool StreamPacket::AddBuffer(SOCKET sock)
{
	if (iWritePos<PACKET_HEADER_SIZE)
	{
		int RecvData = recv(sock, pWritePos, PACKET_HEADER_SIZE-iWritePos, 0);
		if (RecvData==SOCKET_ERROR)
		{
			return false;
		}
		iWritePos += RecvData;
		pWritePos = &Recvbuffer[iWritePos];
		if (iWritePos== PACKET_HEADER_SIZE)
		{
			m_pRecvPacket = (UPACKET*)&Recvbuffer;
		}
	}
	else
	{
		iWritePos += recv(sock, pWritePos,m_pRecvPacket->ph.len - PACKET_HEADER_SIZE, 0);
		pWritePos = &Recvbuffer[iWritePos];
		if (iWritePos==m_pRecvPacket->ph.len)
		{
			UPACKET packet;
			memcpy(&packet, m_pRecvPacket, sizeof(UPACKET));
			Network::m_Recvlist.push_back(packet);

			iWritePos = 0;
			ZeroMemory(Recvbuffer, PACKET_MAX_SIZE);
			pWritePos =&Recvbuffer[iWritePos];

		}

	}
	return true;
}
bool StreamPacket::RecvData()
{
	return true;
}
StreamPacket::StreamPacket()
{
	ZeroMemory(Recvbuffer, sizeof(Recvbuffer));
	iWritePos=0;
	pWritePos=Recvbuffer;


}


StreamPacket::~StreamPacket()
{
}
