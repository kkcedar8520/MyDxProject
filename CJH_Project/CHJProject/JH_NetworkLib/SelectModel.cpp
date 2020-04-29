#include "SelectModel.h"
#include"Network.h"

bool SelectModel::Init()
{
	return true;
}
bool SelectModel:: Frame() 
{
	return true;
}
bool SelectModel::Render()
{
	return true;
}
bool SelectModel::Release()
{
	return true;
}

bool SelectModel::SendMsg(SOCKET sock, UPACKET&Packet)
{
	char* buffer = (char*)&Packet;

	int iSendByte = send(sock, (char*)&Packet, Packet.ph.len, 0);
	if (iSendByte == SOCKET_ERROR)
	{
		return false;
	}
	while (iSendByte < Packet.ph.len)
	{
		buffer += iSendByte;
		iSendByte += send(sock, buffer, Packet.ph.len - iSendByte, 0);

	}


	return true;
}
bool SelectModel::SendMsg(SOCKET sock, const char*buf, int iLength)
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
	while (iSendByte < packet.ph.len)
	{
		iSendByte += send(sock, pTempBuffer, packet.ph.len - iSendByte, 0);
		pTempBuffer += iSendByte;

	}
	std::cout << "Send" << std::endl;
	return true;
}
bool SelectModel::RecvData(SOCKET sock)
{
	
	if (m_iWritePos < PACKET_HEADER_SIZE)
	{
		int RecvData = recv(sock, m_pWritePos, PACKET_HEADER_SIZE - m_iWritePos, 0);
		if (RecvData == 0)
		{
			return false;
		}
		if (RecvData == SOCKET_ERROR)
		{
			if (WSAGetLastError() !=WSAEWOULDBLOCK)
			{
				return false;
			}
		}
		else
		{
			m_iWritePos += RecvData;
			m_pWritePos += m_iWritePos;
			m_pWritePos = &m_Recvbuffer[m_iWritePos];
			UPACKET*Packet = (UPACKET*)m_Recvbuffer;

			if (Packet->ph.len==m_iWritePos)
			{
				Network::m_Recvlist.push_back(*Packet); // 
			}
		}
	
	}
	else
	{
		UPACKET* Packet = (UPACKET*)m_Recvbuffer;
		m_iWritePos += recv(sock, m_pWritePos, Packet->ph.len - PACKET_HEADER_SIZE, 0);
		m_pWritePos += m_iWritePos;
		m_pWritePos = &m_Recvbuffer[m_iWritePos];
		if (m_iWritePos == Packet->ph.len)
		{
			
			Network::m_Recvlist.push_back(*Packet);

			m_iWritePos = 0;
			ZeroMemory(m_Recvbuffer, PACKET_MAX_SIZE);
			m_pWritePos = &m_Recvbuffer[m_iWritePos];

		}

	}
	return true;
}
bool SelectModel::RecvMsg(SOCKET sock, char* Buffer, int iSize)
{
	int RecvData = 0;
	while (iSize>RecvData)
	{
		int RecvByte = recv(sock, &Buffer[RecvData], iSize - RecvData, 0);
		if (RecvByte==0)
		{
			return false;
		}
		if (RecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return false;
			}
		}
		RecvData += RecvByte;
	}
	return true;
}
SelectModel::SelectModel()
{
	m_iWritePos=0;
	m_pWritePos=m_Recvbuffer;
}
SelectModel::~SelectModel()
{
}