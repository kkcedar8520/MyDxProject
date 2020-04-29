
#include"NetStd.h"
struct User
{
	SOCKET Sock;
	SOCKADDR_IN sock_addr;
	char Buffer[256];

};

std::list<User> userlist;
std::list<std::string>UserPacketlist;


DWORD WINAPI Receive(LPVOID arg);
DWORD WINAPI SendPacket(LPVOID arg);
void AddUser(SOCKET sock,SOCKADDR_IN sock_addr);



CRITICAL_SECTION g_Sync;
CRITICAL_SECTION g_UserSync;
int main()
{

	InitializeCriticalSection(&g_Sync);
	InitializeCriticalSection(&g_UserSync);
	WSADATA wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);



	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);

	u_long Switch = TRUE;

	ioctlsocket(listenSock, FIONBIO, &Switch);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.111");
	sa.sin_port = htons(10000);

	int	iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));

	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(listenSock);
			return false;
		}

	}
	iRet = listen(listenSock, SOMAXCONN);

	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(listenSock);
			return false;
		}
	}

	SOCKADDR_IN client_addr;

	int addrlen = sizeof(client_addr);
	SOCKET ClientSock;

	DWORD dwSendID,dwRecvID;

	HANDLE SendThreadHandle,ReceiveThreadHandle;



	while (1)
	{

		ClientSock = accept(listenSock, (SOCKADDR*)&client_addr, &addrlen);

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
			
			AddUser(ClientSock, client_addr);
		}
		SendThreadHandle = CreateThread(0, 0, SendPacket, (void*)ClientSock, 0, &dwSendID);
		ReceiveThreadHandle = CreateThread(0, 0, Receive, (void*)ClientSock, 0, &dwRecvID);


	}
	closesocket(listenSock);




	WSACleanup();
	DeleteCriticalSection(&g_Sync);
	DeleteCriticalSection(&g_UserSync);
}

DWORD WINAPI Receive(LPVOID arg)
{
	
	if (userlist.size()<=0)
	{
		return false;
	}
	std::list<User>::iterator iter;
	
	for (iter = userlist.begin(); iter != userlist.end();)
	{
		SOCKET Sock = iter->Sock;
		ZeroMemory(iter->Buffer, sizeof(iter->Buffer));
		int iRetRecv = recv(Sock, iter->Buffer, sizeof(iter->Buffer), 0);


		if (iRetRecv ==SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				EnterCriticalSection(&g_Sync);
				iter = userlist.erase(iter);
				LeaveCriticalSection(&g_Sync);
				closesocket(Sock);
				return false;
			}
		}
		else
		{
			UserPacketlist.push_back(iter->Buffer);
		}
		
	}


	return true;
}

DWORD WINAPI SendPacket(LPVOID arg)
{
	int iSend;
	std::list<User>::iterator iter;
	std::list<std::string>::iterator Message;
	if (userlist.size() <= 0)return false;
	for (Message = UserPacketlist.begin(); Message !=UserPacketlist.end(); Message++)
	{


		for (iter = userlist.begin(); iter != userlist.end();)
		{
			
			SOCKET sock = iter->Sock;

			iSend = send(sock, Message->c_str(), Message->size(), 0);

		
			if (iSend <=0)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					EnterCriticalSection(&g_Sync);
					iter = userlist.erase(iter);
					LeaveCriticalSection(&g_Sync);
					closesocket(sock);
					return false;
				}
			}
		}
	}
}



void AddUser(SOCKET sock,SOCKADDR_IN sock_addr)
{
	User NewUser;
	NewUser.Sock = sock;
	NewUser.sock_addr = sock_addr;
		

	std::cout << "ip:" << inet_ntoa(sock_addr.sin_addr) << "Port:" << ntohs(sock_addr.sin_port) << std::endl;

	EnterCriticalSection(&g_UserSync);
	userlist.push_back(NewUser);
	LeaveCriticalSection(&g_UserSync);
}