// NonBlock.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include<winsock2.h>
#include<list>
#pragma comment(lib,"ws2_32.lib")
std:: list<SOCKET> userlist;

int Receive(SOCKET sock);
int Send(SOCKET sock, int iRetRecv);
int main()
{

	WSADATA wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);



	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);

	u_long Switch=TRUE;

	ioctlsocket(listenSock, FIONBIO, &Switch);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.122");
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

	if (iRet==SOCKET_ERROR)
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

	while (1)
	{

		ClientSock = accept(listenSock, (SOCKADDR*)&client_addr,&addrlen);

		if (ClientSock==SOCKET_ERROR)
		{
			if (WSAGetLastError()!= WSAEWOULDBLOCK)
			{
				closesocket(ClientSock);
				break;
			}
		}
		else
		{
			std::cout << "ip:" << inet_ntoa(client_addr.sin_addr) << "Port:" << ntohs(client_addr.sin_port) << std::endl;
			userlist.push_back(ClientSock);
		}
		iRet = Receive(ClientSock);
		Send(ClientSock, iRet);

	
	}
	closesocket(listenSock);
	
	


	WSACleanup();

}

int Receive(SOCKET sock)
{
	int iRetRecv=0;

	std::list<SOCKET>::iterator iter;
	
	for ( iter = userlist.begin(); iter!=userlist.end();)
	{
		sock = *iter;
		char Recvbuf[256] = { 0, };
		ZeroMemory(Recvbuf, sizeof(Recvbuf));
		 iRetRecv = recv(sock, Recvbuf, sizeof(Recvbuf), 0);

		if (iRetRecv == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				iter = userlist.erase(iter);
				closesocket(sock);
				return false;
			}
		}
		std::cout << Recvbuf << std::endl;
	}
	

	return iRetRecv;
}

int Send(SOCKET sock,int iRetRecv)
{
	int iSend;
	std::list<SOCKET>::iterator iter;

	for (iter = userlist.begin(); iter != userlist.end();)
	{
		char buf[256] = { 0. };
		ZeroMemory(buf, sizeof(buf));
		sock = *iter;
		iSend = send(sock, buf, iRetRecv, 0);
	
		if (iSend == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				iter = userlist.erase(iter);
				
				closesocket(sock);
				return false;
			}
		}
		std::cout << buf << std::endl;
	}
}