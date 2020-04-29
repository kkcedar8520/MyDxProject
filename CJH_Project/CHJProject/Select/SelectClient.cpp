#pragma once
#include"JH_Client.h"
#include"Network.h"

JH_Client NetClient;

void RecvChattMsg(UPACKET&t)
{
	std::cout << t.Msg << std::endl;
}

int main(void)
{



	if (!NetClient.Connect("192.168.0.122", SOCK_STREAM, 10000))
	{
		return false;
	}


	Network::m_funtionExcute[PACKET_CHAT_MSG] = RecvChattMsg;
	NetClient.CreateThread();
	while (1)
	{
		char buffer[256] = { 0, };
		fgets(buffer, sizeof(buffer), stdin);
		
		Network::SendMsg(NetClient.m_Socket, buffer, strlen(buffer) - 1);
		
	}
	return true;
}

