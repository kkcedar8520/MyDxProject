#define _CRT_SECURE_NO_WARNINGS
#include"studentmg.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
extern int T_Num;
int num;
int main()
{
	int n = 0;
	while (num != 99)
	{
		system("cls");
		printf("생성:0 저장:1 로드:2 신규:3 출력:4 검색:5 종료:(99) :");
		scanf("%d", &num);
		switch (num)
		{
		case 0:
			S_SampleData();
			break;
		case 1:
			n=S_DataSave();
			break;
		case 2:
			if (S_DataLoad())
			{
				printf("파일오픈 실패!");
				printf("계속하려면 아무키나 눌러주세요");
				_getch();
			}
			break;
		case 3:
			S_NewData();
			break;
		case 4:
			PrintAll();
		case 5:
			int s;
			system("cls");
			printf("검색할 번호 입력:");
			scanf("%d", &n);
			S_DataSh(n);
		case 99:
			break;
		default:
			printf("옳지않은 값 입력 다시 입력하세요.\n");
			break;
		}
	}

}