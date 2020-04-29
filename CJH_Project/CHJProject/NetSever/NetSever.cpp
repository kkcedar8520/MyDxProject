// NetSever.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa)!=0)
	{
		return 1;
	}

	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.122");

	bind(listensock, (SOCKADDR*)&sa, sizeof(sa));

	listen(listensock, SOMAXCONN);

	SOCKET ClientSocket;
	SOCKADDR_IN ClientAddr;

	int adrlen = sizeof(ClientAddr);
	
	while (true)
	{
		ClientSocket = accept(listensock, (SOCKADDR*)&ClientAddr,&adrlen);
		
		std::cout << "ip=" << inet_ntoa(ClientAddr.sin_addr) << "Port=" << ntohs(ClientAddr.sin_port) << std::endl;

		while (true)
		{
			char Recvbuf[256] = { 0, };
			int iRecv = recv(ClientSocket, Recvbuf, sizeof(Recvbuf), 0);
			if (iRecv<=0)
			{
				closesocket(ClientSocket);
				break;
			}
			
			std::cout << Recvbuf<<std::endl;

			int iSend = send(ClientSocket, Recvbuf, sizeof(Recvbuf), 0);
			if (iSend)
			{
				closesocket(ClientSocket);
				break;
			}
		}
	}

	closesocket(listensock);
	// 윈속 소멸

	WSACleanup();
}

