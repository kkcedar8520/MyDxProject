

#include <iostream>
#include<winsock2.h>
#include<list>
#pragma comment(lib,"ws2_32.lib")
DWORD WINAPI SendProc(LPVOID arg);
DWORD WINAPI ReceiveProc(LPVOID arg);
int main()
{
    WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}
	
	SOCKET Clientsock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.122");
	sa.sin_port = htons(10000);



	int iRet = connect(Clientsock, (SOCKADDR*)&sa,sizeof(sa));

	if (iRet == SOCKET_ERROR)
	{
		return true;
	}

	//DWORD dwID;
	DWORD dwSendID;
	//HANDLE ThreadHandle = CreateThread(0, 0, ReceiveProc, (void*)Clientsock, 0, &dwID);
	HANDLE SendThHandle = CreateThread(0, 0, SendProc, (void*)Clientsock, 0, &dwSendID);


	while (1)
	{
		char bufRecv[256] = { 0, };
		int iRecvByte = recv(Clientsock, bufRecv, sizeof(bufRecv) - 1, 0);
		if (iRecvByte < 0) break;
		bufRecv[iRecvByte] = 0;
		printf("recv=%s\n", bufRecv);

	}
	
	WSACleanup();
	CloseHandle(SendThHandle);
}

DWORD WINAPI ReceiveProc(LPVOID arg)
{
	SOCKET Sock = (SOCKET)arg;

	while (true)
	{
		char recvbuf[256] = { 0, };
		int iRecvSz = recv(Sock, recvbuf, sizeof(recvbuf)-1, 0);
		if (iRecvSz==SOCKET_ERROR)
		{
			if (WSAGetLastError()!=WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			std::cout << recvbuf << std::endl;
		}
	}
	closesocket(Sock);

	return true;

}

DWORD WINAPI SendProc(LPVOID arg)
{
	SOCKET Sock = (SOCKET)arg;

	while (true)
	{
		char sendbuf[256] = { 0, };
		fgets(sendbuf, sizeof(sendbuf), stdin);
		
		int iSendSz = send(Sock, sendbuf, sizeof(sendbuf)-1, 0);
		if (iSendSz == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			std::cout << sendbuf << std::endl;
		}
	}
	closesocket(Sock);

	return true;

}