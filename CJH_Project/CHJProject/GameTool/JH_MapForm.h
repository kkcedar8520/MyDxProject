#pragma once


// JH_MapForm 대화 상자

class JH_MapForm : public CDialog
{
	DECLARE_DYNAMIC(JH_MapForm)

public:
	JH_MapForm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~JH_MapForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JH_MapForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
