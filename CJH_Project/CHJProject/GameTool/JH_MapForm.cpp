// JH_MapForm.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "JH_MapForm.h"
#include "afxdialogex.h"


// JH_MapForm 대화 상자

IMPLEMENT_DYNAMIC(JH_MapForm, CDialog)

JH_MapForm::JH_MapForm(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_JH_MapForm, pParent)
{

}

JH_MapForm::~JH_MapForm()
{
}

void JH_MapForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(JH_MapForm, CDialog)
END_MESSAGE_MAP()


// JH_MapForm 메시지 처리기
