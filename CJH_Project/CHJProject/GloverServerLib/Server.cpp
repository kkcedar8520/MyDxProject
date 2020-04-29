#include "Server.h"
#include"SessionMgr.h"
#include"JH_IOCP.h"

bool Server::Init()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2.2, 0), &wsa);


	// 패킷콜함수 등록
	m_fnExecutePacket[PACKET_SELECT_CHARACTER_REQ] = &Server::GameStart;


	I_IOCP.Init();

	if(!m_Acceptor.Setting(10000, "119.195.167.25"))
	{
		std::cout << "SOCKET ERROR!" << std::endl;
		return false;
	}

	CreateThread();


	
	return true;
}
bool Server::Release()
{
	WSACleanup();
	return true;
}
void Server::Broadcast(std::stringstream & SendStream)
{
	SendBroadcastPool(SendStream);
}
void Server::BroadcastNewPlayer(JH_Character& player)
{
	stringstream data;
	data << player;
	
	//Broadcast(MakePacket(PACKET_ZONE_NEW_PLAYER, data));
	//T_LOG("PACKET_ZONE_NEW_PLAYER Send\r\n");
}
void Server::SendBroadcastPool(UPACKET& sendmsg)
{
	JPACKET Packet;
	CopyMemory(&Packet.uPacket, (char*)&sendmsg, sendmsg.ph.len);
	m_SendBroadcastPool.AddPacket(Packet);
}
void Server::SendBroadcastPool(std::stringstream & SendStream)
{
	UPACKET packet;
	CopyMemory(&packet, (CHAR*)SendStream.str().c_str(), SendStream.str().length());
	SendBroadcastPool(packet);
}

void Server::SendBroadcastPacket()
{
	I_Session.Lock();
	m_SendPacketPool.Lock();


	for (JPacketIter packet = m_SendBroadcastPool.Get().begin();
		packet != m_SendBroadcastPool.Get().end();
		packet++)
	{
		JPACKET tPacket = (*packet);
		for (UserIter iter = I_Session.GetUserList().begin();
			iter != I_Session.GetUserList().end();
			iter++)
		{
			User* pUser = (User*)iter->second;
			if (SendPacket(pUser, tPacket.uPacket) <= 0)
			{
				continue;
			}
		}
	}
	m_SendPacketPool.Unlock();
	I_Session.UnLock();

	m_SendPacketPool.Lock();
	m_SendBroadcastPool.PacketClear();
	m_SendPacketPool.Unlock();
}
bool Server::Run()
{

	while (bStart == true)
	{
		// Recv
		{
			m_RecvPacketPool.Lock();
			for (JPacketIter iter = m_RecvPacketPool.Get().begin();
				iter != m_RecvPacketPool.Get().end();
				iter++)
			{
				UPACKET PacketMsg;
				ZeroMemory(&PacketMsg, sizeof(PacketMsg));
				JPACKET pSendUser = (*iter);
				FunctionIterator calliter = m_fnExecutePacket.find(pSendUser.uPacket.ph.type);
				if (calliter != m_fnExecutePacket.end())
				{
					CallFuction call = calliter->second;
					(this->*call)(*iter);
					//T_LOG("%s%d[%d]\r\n", "TYPE=", pSendUser.packet.ph.type, pSendUser.packet.ph.len );
				}
			}
			/*m_RecvPacketPool.Unlock();
			InterlockedExchangeAdd(&m_dwRecvPacket, m_RecvPacketPool.Get().size());
			m_RecvPacketPool.Lock();*/
			m_RecvPacketPool.PacketClear();
			m_RecvPacketPool.Unlock();
		}
	
		SendBroadcastPacket();
		{
			m_SendPacketPool.Lock();

			for (JPacketIter iter = m_SendPacketPool.Get().begin();
				iter != m_SendPacketPool.Get().end();
				iter++)
			{
				JPACKET jPacket = (*iter);
				jPacket.ov = new OVERLAPPED_EX(MODE_SEND);
				jPacket.buffer.buf = (char*)&jPacket.uPacket;
				jPacket.buffer.len = (ULONG)jPacket.uPacket.ph.len;
				DWORD dwFlags = 0;
				int iRet = WSASend(jPacket.sock, &jPacket.buffer, 1, NULL, dwFlags,
					(LPOVERLAPPED)jPacket.ov, NULL);
				if (iRet == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
				{
					delete jPacket.ov;
					I_Session.DeleteUser(jPacket.pUser);
				}
			}
	/*		m_SendPacketPool.Unlock();
			InterlockedExchangeAdd(&m_dwSendPacket, m_SendPacketPool.Get().size());
			m_SendPacketPool.Lock();*/
			m_SendPacketPool.PacketClear();
			m_SendPacketPool.Unlock();
		}
		Sleep(1);
	}
	return true;
}
Server::Server()
{

}
void  Server::AddRecvPacket(JPACKET pack)
{
	m_RecvPacketPool.AddPacket(pack);
}
bool Server::SendPacket(User* pUser, std::stringstream& Data)
{
	JPACKET jPacket;
	
	jPacket.pUser = pUser;
	CopyMemory(&jPacket.uPacket, Data.str().c_str(), Data.str().length());
	
	m_SendPacketPool.m_PacketList.push_back(jPacket);
	return true;
}

int Server::SendPacket(User* pUser, UPACKET& sendmsg)
{
	JPACKET Packet;
	CopyMemory(&Packet.uPacket, (char*)&sendmsg, sendmsg.ph.len);
	Packet.pUser = pUser;
	Packet.sock = pUser->m_Sock;
	m_SendPacketPool.AddPacket(Packet);
	return 1;
}
void Server::SendPacket(User * pUser, size_t iSendByte)
{
	JPACKET Packet;
	CopyMemory(&Packet.uPacket, (char*)&pUser->m_sendBuffer, iSendByte);
	Packet.pUser = pUser;
	Packet.sock = pUser->m_Sock;
	m_SendPacketPool.AddPacket(Packet);
}
Server::~Server()
{
	Release();

}
std::ostream& operator<<(std::ostream& stream, Server& sv_Info)
{
	stream << I_Session.m_UserList.size();
	for(auto& User:I_Session.GetUserList())
	{
		stream << User.first;
		stream << *User.second;
	}

	return stream;
}


