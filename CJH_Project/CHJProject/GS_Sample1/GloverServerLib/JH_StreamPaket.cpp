#include "JH_StreamPaket.h"



bool JH_StreamPacket::AddPacket(const char* RecvBuffer, int DataSize)
{
	if (DataSize> PACKET_MAX_SIZE)
	{

	}
	return true;
}
bool JH_StreamPacket::RecvData()
{
	return true;
}
JH_StreamPacket::JH_StreamPacket()
{
	ZeroMemory(Recvbuffer, sizeof(Recvbuffer));
	iWritePos = 0;
	pWritePos = Recvbuffer;


}


JH_StreamPacket::~JH_StreamPacket()
{
}

