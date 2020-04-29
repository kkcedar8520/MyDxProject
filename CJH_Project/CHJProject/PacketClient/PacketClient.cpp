#include"NetworkClient.h"

NetworkClient NetClient;
DWORD WINAPI SendPacket(LPVOID arg);
#pragma comment(lib,"JH_NetworkLib.lib")
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
	DWORD ThreadID;
	HANDLE SendThread = CreateThread(0, 0, SendPacket, (void*)NetClient.m_Socket, 0, &ThreadID);

	Network::m_funtionExcute[PACKET_CHAT_MSG] = RecvChattMsg;
	while (1)
	{
		if (!NetClient.RunClient())
		{
			break;
		}
	}
}

DWORD WINAPI SendPacket(LPVOID arg)
{

	SOCKET  sock = (SOCKET)arg;

	while (1)
	{
		char Buffer[256];
		fgets(Buffer, sizeof(Buffer), stdin);

		Network::SendMsg(sock, Buffer, strlen(Buffer) - 1);
		Sleep(1);
	}
	return true;
}