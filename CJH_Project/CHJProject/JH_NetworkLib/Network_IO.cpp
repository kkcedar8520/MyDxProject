#pragma once
#include"Network.h"


bool Network::SendMsg(SOCKET sock,UPACKET&Packet)
{
	char* buffer = (char*)&Packet;

	int iSendByte= send(sock, (char*)&Packet, Packet.ph.len, 0);
	if (iSendByte==SOCKET_ERROR)
	{
		return false;
	}
	while (iSendByte< Packet.ph.len)
	{
		buffer += iSendByte;
		iSendByte += send(sock, buffer, Packet.ph.len - iSendByte, 0);
		
	}


	return true;
}
bool Network::SendMsg(SOCKET sock, const char*buf, int iLength)
{
	UPACKET packet;
	packet.ph.len = PACKET_HEADER_SIZE + iLength;
	packet.ph.type = PACKET_CHAT_MSG;

	memcpy(&packet.Msg, buf, packet.ph.len);
	char* pTempBuffer = (char*)&packet;

	int iSendByte = send(sock, pTempBuffer, packet.ph.len, 0);
	if (iSendByte == SOCKET_ERROR)
	{
		return false;
	}
	pTempBuffer += iSendByte;
	while (iSendByte<packet.ph.len)
	{
		iSendByte += send(sock, pTempBuffer, packet.ph.len - iSendByte, 0);
		pTempBuffer += iSendByte;
		
	}
	std::cout << "Send" << std::endl;
	return true;
}