#include "Server.h"



void Server::GameStart(JPACKET& t)
{
	BroadcastNewPlayer(t.pUser->m_CharacterList[t.pUser->m_dwCharacter]);
	std::stringstream data;

	data << t.uPacket.Msg;
}

void Server::CharacterSelectAck(JPACKET& t)
{
	JH_Character Character;
	Character<<t.uPacket.Msg
	m_CharactorList.push_back
}



//void Server::LoginMessage(JPACKET& t)
////{
////	JPCKET
////}