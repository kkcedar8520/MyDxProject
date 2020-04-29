// NetClient.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


/// 네트워크 수업은 항상 문제점을 찾는 수업을 할것
//그날의 문제점이 뭔지 항상 알고있어야한다.
int main()
{
	WSADATA wsa;

	
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);//호스트주소를 네트워크주소로 쇼트로
	sa.sin_addr.s_addr = inet_addr("192.168.0.111");
	int iRet=connect(sock,(SOCKADDR*)&sa,sizeof(sa));
	
	if (iRet==SOCKET_ERROR)
	{
		return 1; 
		
	}
	int iLoop = 5;
	while (iLoop>0)
	{
		
		char buf[256] = { 0, };
		fgets(buf, sizeof(char) * 256, stdin);
		if (buf[0] == '\n') break;
		
		
		int iSendbyte = send(sock, buf, strlen(buf)-1, 0); // 내부적으로 핸드 셰이킹 진행중 
		if (iSendbyte <= 0)// 음수면 강제종료 0이면 정상적인 종료
		{

			break;
		}
		
		
		char recvbuf[256] = { 0, };


		int recvbyte = recv(sock, recvbuf, 256, 0);

		if (recvbyte<=0)
		{
			
			break;
		}


		std::cout << recvbuf << std::endl;

		Sleep(1000);

	}
	

	closesocket(sock); // 소켓을 나간다 이것을 안해주면 강제 종료가 된다. 

	WSACleanup();
 
}

