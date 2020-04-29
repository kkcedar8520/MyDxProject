#include "JH_StreamPaket.h"
#include"Server.h"

bool  JH_StreamPacket::ParityCheck(User* pUser)
{
	m_pPacketStart = (UPACKET*)InterlockedExchangePointer(&m_pPacket, nullptr);
	if (m_pPacketStart != nullptr)
	{
		if (m_pPacketStart->ph.iotype == 777 && m_iReadPos > 0)
		{
			return true;
		}
		if (m_pPacketStart->ph.iotype != 777 && m_pPacketStart->ph.len < 0 || m_pPacketStart->ph.len > 512)
		{
			return false;
		}
	}
	return true;
}

bool   JH_StreamPacket::GetPacket(User* pUser)
{
	int iPacketCnt = 0;
	if (m_iReadPos < PACKET_HEADER_SIZE)
	{
		return true;
	}
	// ��Ŷ�� ����
	InterlockedExchangePointer(&m_pPacket, (void*)&m_RecvBuffer[m_iStartPos]);

	if (ParityCheck(pUser) == false)
	{
		return false;
	}
	// 1���� ��Ŷ �����ŭ �޾Ҵٸ�
	if (m_iReadPos >= m_pPacketStart->ph.len)
	{
		do {
			JPACKET    add;
			ZeroMemory(&add, sizeof(add));
			CopyMemory(&add.uPacket, m_pPacketStart, m_pPacketStart->ph.len);
			add.pUser = pUser;

			InterlockedAdd64(&m_iReadPos, -m_pPacketStart->ph.len);
			InterlockedAdd64(&m_iStartPos, m_pPacketStart->ph.len);
			InterlockedExchangePointer(&m_pPacket, (void*)&m_RecvBuffer[m_iStartPos]);
			I_Server.AddRecvPacket(add);

			// �ܿ����� ��Ŷ ������� ���� ���
			if (m_iReadPos < PACKET_HEADER_SIZE || m_iReadPos < m_pPacketStart->ph.len)
			{
				break;
			}
			if (ParityCheck(pUser) == false)
			{
				return false;
			}
		} while (m_iReadPos >= m_pPacketStart->ph.len);
	}
	return true;
}
bool   JH_StreamPacket::Put(char* recvBuffer, int iRecvSize, User* pUser)
{
	// ������  ���� ��Ŷ�� ũ�⺸�� WSARecv ���۰� ������ �ɰ����� ���´�.
	// �޴� ������ �뷮�� �����ϸ�		
	if ((m_iWritePos + iRecvSize) >= MAX_RECV_STREAM_SIZE)
	{
		if (m_iReadPos > 0)
		{
			memmove(m_RecvBuffer, &m_RecvBuffer[m_iStartPos], m_iReadPos);
		}
		InterlockedExchange64(&m_iStartPos, 0);
		InterlockedExchange64(&m_iWritePos, m_iReadPos);
		InterlockedExchangePointer(&m_pWritePos, (void*)&m_RecvBuffer[m_iWritePos]);
	}
	CopyMemory(m_pWritePos, recvBuffer, iRecvSize);
	InterlockedAdd64(&m_iWritePos, iRecvSize);
	InterlockedAdd64(&m_iReadPos, iRecvSize);
	InterlockedExchangePointer(&m_pWritePos, (void*)&m_RecvBuffer[m_iWritePos]);
	return true;
};
void JH_StreamPacket::Reset()
{
	//m_RecvBuffer = new char[MAX_RECV_STREAM_SIZE];
	ZeroMemory(m_RecvBuffer, sizeof(char) * MAX_RECV_STREAM_SIZE);
	m_iStartPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
	m_pPacket = nullptr;
	m_pPacketStart = nullptr;
	m_pWritePos = nullptr;
	InterlockedExchangePointer(&m_pPacket, (void*)&m_RecvBuffer[m_iStartPos]);
	m_pPacketStart = (UPACKET*)m_pPacket;
	m_pWritePos = m_pPacket;
}
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
	ZeroMemory(m_RecvBuffer, sizeof(m_RecvBuffer));
	m_iWritePos = 0;
	m_pWritePos = m_RecvBuffer;


}


JH_StreamPacket::~JH_StreamPacket()
{
}

