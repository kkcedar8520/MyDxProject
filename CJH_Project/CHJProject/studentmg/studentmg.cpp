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
		printf("����:0 ����:1 �ε�:2 �ű�:3 ���:4 �˻�:5 ����:(99) :");
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
				printf("���Ͽ��� ����!");
				printf("����Ϸ��� �ƹ�Ű�� �����ּ���");
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
			printf("�˻��� ��ȣ �Է�:");
			scanf("%d", &n);
			S_DataSh(n);
		case 99:
			break;
		default:
			printf("�������� �� �Է� �ٽ� �Է��ϼ���.\n");
			break;
		}
	}

}