#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

struct S_GradeNode  //�л����� ����ü
{
	int mnum;
	char name[4];
	int national_language;
	int english;
	int math;
	int total;
	double average;
	S_GradeNode*pNextNode;
};
S_GradeNode*g_HeadNode =0;//��� ���
S_GradeNode*g_TailNode = 0;//���� ���;
S_GradeNode*g
S_GradeNode*g_pStudenData = 0;
S_GradeNode*g_CurrentNode = 0;

int S_Num=1;
int T_Num;
void PrintAll();//���â ���
int S_DataSave();//��������
void S_DelData(int n);//���� ����
int S_DataLoad();//�����ε�	
void S_Insert();
S_GradeNode* S_NewNode();//������
void S_SampleData();
void S_NewData();//�űԳ�� �������̱�
void S_SampleData()
{
	if (g_HeadNode==NULL)
	{
		for (int i = 0; i < 11; i++)
		{
			S_GradeNode*NewNode = S_NewNode();
			NewNode->pNextNode = NULL;
			if (g_HeadNode == NULL)
				g_HeadNode = NewNode;
			else
				g_TailNode->pNextNode = NewNode;
			
			g_TailNode = NewNode;
		}
		PrintAll();
		_getch();
	}
}

void PrintAll()
{
	system("cls");
	if (S_Num==1)
	{
		printf("���� ������� �����Ͱ� �����ϴ�.\n");
	}
	else
	{
		puts("							���� ���� ���α׷�									");
		puts("\n===================================================================================================================\n");
		puts("��ȣ		�̸�		����		����		����		����		���\n");
		puts("======================================================================================================================\n");
		S_GradeNode*T_Node = g_HeadNode;
		while (T_Node->pNextNode != NULL)
		{
			printf("%d\t\t", T_Node->mnum);
			printf("%s\t\t", T_Node->name);
			printf("%d\t\t", T_Node->national_language);
			printf("%d\t\t", T_Node->english);
			printf("%d\t\t", T_Node->math);
			printf("%d\t\t", T_Node->total);
			printf("%f\n", T_Node->average);
			T_Node = T_Node->pNextNode;
		}
	}
	printf("����Ϸ��� �ƹ�Ű�� �Է��ϼ���\n");
	_getch();
}

S_GradeNode* S_NewNode()
{

	S_GradeNode*NewNode = (S_GradeNode*)malloc(sizeof(S_GradeNode));
	NewNode->mnum = S_Num;
	NewNode->name[0] = 65 + rand() % 26;
	NewNode->name[1] = 65 + rand() % 26;
	NewNode->name[2] = 65 + rand() % 26;
	NewNode->name[3] = 0;

	NewNode->national_language = rand() % 101;
	NewNode->english = rand() % 101;
	NewNode->math = rand() % 101;
	NewNode->total = (NewNode->national_language + NewNode->math + NewNode->english);
	NewNode->average = (NewNode->national_language + NewNode->math + NewNode->english) / 3.0;
	NewNode->pNextNode = NULL;
	S_Num++;
	return  NewNode;
}
void S_NewData()
{

	S_GradeNode*NewNode = S_NewNode();
	S_GradeNode*T_Node = g_HeadNode;
	while (T_Node->pNextNode != NULL)
	{
		T_Node = T_Node->pNextNode;
	}
	NewNode->pNextNode = T_Node->pNextNode;
	T_Node->pNextNode = NewNode;
	PrintAll();

}
int S_DataSave()
{
	if (g_HeadNode==NULL)
	{
		printf("������ �����Ͱ� �����ϴ� �����͸� �������ּ���");
		return 1;
	}
	FILE*fp=fopen("stdent.mg","w");
	S_GradeNode*T_Node = g_HeadNode;
	while (T_Node->pNextNode != NULL)
	{
		fprintf(fp, "%d\t\t", T_Node->mnum);
		fprintf(fp, "%s\t\t", T_Node->name);
		fprintf(fp, "%d\t\t", T_Node->national_language);
		fprintf(fp, "%d\t\t", T_Node->english);
		fprintf(fp, "%d\t\t", T_Node->math);
		fprintf(fp, "%d\t\t", T_Node->total);
		fprintf(fp, "%f\n", T_Node->average);
		T_Node = T_Node->pNextNode;
	}
	T_Node = 0;
	printf("������ �Ϸ�ƽ��ϴ� ����Ϸ��� �ƹ�Ű�� ��������");
	_getch();
	fclose(fp);
	return 0;
}
int S_DataLoad()
{
	FILE*fp = fopen("stdent.mg", "r");
	char buffer[256] = { 0 };

	if (fp==NULL)
	{
		return 1;
	}
	puts("							���� ���� ���α׷�									");
	puts("\n===================================================================================================================\n");
	puts("��ȣ		�̸�		����		����		����		����		���\n");
	puts("======================================================================================================================\n");
	while (fgets(buffer,sizeof(buffer),fp)!=0)
	{
		printf("%s", buffer);
	}
	fclose(fp);
	return 0;
}

void S_DataSh(int n)
{
	if (g_HeadNode==NULL)
	{

	}
	else
	{
		S_GradeNode*T_Node = g_HeadNode;
		S_GradeNode*g_TempNextNode = T_Node->pNextNode;
		while (T_Node->pNextNode != NULL)
		{
			if (T_Node->mnum == n)
			{
				printf("%d\t\t", T_Node->mnum);
				printf("%s\t\t", T_Node->name);
				printf("%d\t\t", T_Node->national_language);
				printf("%d\t\t", T_Node->english);
				printf("%d\t\t", T_Node->math);
				printf("%d\t\t", T_Node->total);
				printf("%f\n", T_Node->average);

				T_Node->pNextNode = NULL;
			}
			T_Node = g_TempNextNode;
			g_TempNextNode = T_Node->pNextNode;
		}
	}
	printf("����Ϸ��� �ƹ�Ű�� ��������");
	_getch();
}
void S_DelData()
{
	if (g_HeadNode==NULL)
	{
		printf("������ �����Ͱ� ���������ʽ��ϴ�.");
	}
	else
	{
		S_GradeNode*DelNode = g_HeadNode;
		S_GradeNode*DelNextNode = DelNode->pNextNode;
		free(DelNode);
		while (DelNextNode->pNextNode != NULL)
		{
			DelNode = DelNextNode;
			DelNextNode = DelNextNode->pNextNode;
			free(DelNode);
		}
	}
}
void S_Insert()
{
	system("cls");
	int num;

	if (g_HeadNode == NULL)
	{
		printf("�����Ͱ� �����ϴ� �������ּ���");
	}
	else
	{
		printf("������ ��ȣ�� �Է��ϼ���:");
		scanf("%d", &num);
		S_GradeNode*T_Node = g_HeadNode;
		S_GradeNode*g_TempNextNode = T_Node->pNextNode;
		while (T_Node->pNextNode != NULL)
		{
			if (T_Node->mnum ==num )
			{
				S_GradeNode*NewNode = S_NewNode();
				T_Node->pNextNode = NewNode;
				NewNode->pNextNode = g_TempNextNode;
				PrintAll();
				_getch();
				printf("����Ϸ��� �ƹ�Ű�� �Է��ϼ���");
			}
			T_Node = g_TempNextNode;
			g_TempNextNode = T_Node->pNextNode;
		}
	}
	S_GradeNode*T_Node = NULL;
	
}