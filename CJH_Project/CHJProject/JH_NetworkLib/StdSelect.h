#pragma once
#include"SelectModel.h"
class StdSelect:public SelectModel
{
	FD_SET m_rSet; // FD( FILE DESCRIPTOR ���� �ڽ��� ����� ���� �Ǵ� ��ġ������ ���� �ĺ���)
	FD_SET m_wSet; // �����Լ��� ���� �������� ��ȯ�Ǵµ� �̰��� FD( FILE DESCRIPTOR) 
					//	�̰��� ���� ���α׷��ȿ��� �ߺ������ʱ� ������  ���������� ��밡��
public:
	bool Frame();
public:
	StdSelect(SOCKET sock);
	virtual ~StdSelect();
};

