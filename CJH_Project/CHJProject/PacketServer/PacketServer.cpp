
#include"Network.h"
#include"StreamPacket.h"
#pragma comment(lib,"JH_NetworkLib.lib")
Network NetServer;

std::list<UPACKET>::iterator Message;
struct User
{
	SOCKET Sock;
	SOCKADDR_IN sock_addr;
	char buffer[2048];

	int iWritePos;
	char* pWritePos;
	int ID;

	User()
	{
		iWritePos=0;
		pWritePos=0;
		ID;
	}


};
HANDLE g_hMutex;


std::list<User> userlist;


DWORD WINAPI Receive(LPVOID arg);
DWORD WINAPI SendPacket(LPVOID arg);

void GreetMessage(SOCKET sock, SOCKADDR_IN sock_addr);


CRITICAL_SECTION g_Sync;
CRITICAL_SECTION g_UserSync;
int main()
{
	HANDLE g_hMutex = CreateMutex(NULL, FALSE, L"OnceMutex");
	if (GetLastError()==ERROR_ALREADY_EXISTS)
	{
		CloseHandle(g_hMutex);
	}


	InitializeCriticalSection(&g_Sync);
	InitializeCriticalSection(&g_UserSync);
	


	SOCKADDR_IN client_addr;

	int addrlen = sizeof(client_addr);
	SOCKET ClientSock=NULL;

	DWORD dwSendID, dwRecvID;

	HANDLE SendThreadHandle, ReceiveThreadHandle;

	
	NetServer.CreateServer("192.168.0.122",SOCK_STREAM,10000,1);

	
	SendThreadHandle = CreateThread(0, 0, SendPacket, (void*)NetServer.m_Socket, 0, &dwSendID);
	ReceiveThreadHandle = CreateThread(0, 0, Receive, (void*)NetServer.m_Socket, 0, &dwRecvID);
	while (1)
	{

		ClientSock = accept(NetServer.m_Socket, (SOCKADDR*)&client_addr, &addrlen);
	
		if (ClientSock == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(ClientSock);
				break;
			}
		}
		else
		{

			GreetMessage(ClientSock, client_addr);
		}
	}


	CloseHandle(SendThreadHandle);
	CloseHandle(ReceiveThreadHandle);

	DeleteCriticalSection(&g_Sync);
	DeleteCriticalSection(&g_UserSync);
	return true;
}

DWORD WINAPI Receive(LPVOID arg)
{

	
	while (1)
	{
		WaitForSingleObject(g_hMutex, INFINITE);

		std::list<User>::iterator iter;
		for (iter = userlist.begin(); iter != userlist.end(); iter++)
		{

			NetServer.m_StreamPacket.AddBuffer(iter->Sock);
		}


		ReleaseMutex(g_hMutex);
		Sleep(1);
	}
	return true;
}

DWORD WINAPI SendPacket(LPVOID arg)
{

	while (1)
	{

		WaitForSingleObject(g_hMutex, INFINITE);
		std::list<User>::iterator iter;

		for (Message = NetServer.m_Recvlist.begin(); Message != NetServer.m_Recvlist.end(); Message++)
		{


			for (iter = userlist.begin(); iter != userlist.end(); iter++)
			{

				if (!Network::SendMsg(iter->Sock, *Message))
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						EnterCriticalSection(&g_Sync);
						iter = userlist.erase(iter);
						LeaveCriticalSection(&g_Sync);

						break;
					}
				}
			}
		}

		Network::m_Recvlist.clear();
		ReleaseMutex(g_hMutex);
		Sleep(1);
	}
	return true;
}

//void PackSend(char* message,SOCKET sock, SOCKADDR_IN addr_in)
//{
//	UPACKET pack;
//
//	
//	int ilength =strlen(message);
//	memccpy(pack.Msg, message, ilength);
//
//	int SendByte = 0;
//
//	send(sock,)
//	
//}

void GreetMessage(SOCKET sock, SOCKADDR_IN sock_addr)
{
	User NewUser;
	NewUser.Sock = sock;
	NewUser.sock_addr = sock_addr;

	
	std::cout << "ip:" << inet_ntoa(sock_addr.sin_addr) << "Port:" << ntohs(sock_addr.sin_port) << std::endl;

	//char Buffer[256] = { "안녕하세요 채팅서버접속을 환영합니다!"};
	//PackSend(Buffer, sock, sock_addr);

	
	EnterCriticalSection(&g_Sync);
	userlist.push_back(NewUser);
	LeaveCriticalSection(&g_Sync);
}