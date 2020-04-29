

#include"GlobalExp.h"
#include"resource.h"
#define cjhMaxExporterID Class_ID(0x6cc47a6, 0x5b9967f2)



class UtilityExporter : public UtilityObj {
public:
	GlobalExp	m_Exp;
	HWND		m_Pannel;

	Interface*	m_pip;
	IUtil*		m_pUtil;
public:	

	~UtilityExporter() {};
public:
	//void	Init();
	//void	Destroy();
	virtual void BeginEditParams(Interface *ip, IUtil *iu) ;//Messege Box in 
	virtual void EndEditParams(Interface *ip, IUtil *iu) ;//Messege Box Out
	virtual void SelectionSetChanged(Interface *ip, IUtil *iu);
	virtual void DeleteThis();
	virtual void SetStartupParam(MSTR param);
	
	static UtilityExporter*GetInstance()
	{
		static UtilityExporter exp;
		return &exp;
	}
private:
	static INT_PTR CALLBACK DlgProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
	);
	UtilityExporter() {};
};

class ExportClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return  UtilityExporter::GetInstance(); }
	virtual const TCHAR *	ClassName() { return _T("UtilitySkinExp"); }
	virtual SClass_ID SuperClassID() { return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() { return cjhMaxExporterID; }
	virtual const TCHAR* Category() { return _T("cjhMaxExporter"); }

	virtual const TCHAR* InternalName() { return _T("cjhMaxExporterClassDesc"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle



};
ClassDesc2* GetExportDesc() {
	static ExportClassDesc cjhExporterDesc;
	return &cjhExporterDesc;
}


INT_PTR CALLBACK UtilityExporter::DlgProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{

	switch (msg)
	{
	case WM_INITDIALOG:
		break;
	case WM_DESTROY:
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON1:
			{
				//::GetInstance()->m_Exp.ExporterSkin();
				UtilityExporter::GetInstance()->m_Exp.ExporterSkin();
				MessageBox(NULL, L"Succeeded!", L"ExporterSkin", MB_OK);
			}break;
			case IDC_BUTTON2:
			{
				UtilityExporter::GetInstance()->m_Exp.ExporterMatrix();
				//SkinExporter::GetInstance()->m_Exp.ExporterMatrix();
				MessageBox(NULL, L"Succeeded!", L"ExporterSkin", MB_OK);
			}break;
		}
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		GetCOREInterface()->RollupMouseMessage(hWnd, msg, wParam, lParam);
		break;
	default:

		return 0;
	}
	return 1;
}


void UtilityExporter::BeginEditParams(Interface *ip, IUtil *iu)
{

	m_Pannel = ip->AddRollupPage(
		hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1),
		DlgProc,
		_T("param"));

}
void UtilityExporter::EndEditParams(Interface *ip, IUtil *iu)
{
	ip->DeleteRollupPage(m_Pannel);
	m_Pannel = nullptr;
}

void UtilityExporter::SelectionSetChanged(Interface *ip, IUtil *iu)
{
	if (ip->GetSelNodeCount() <= 0) return;

	m_Exp.Release();
	if (m_Exp.Init(ip))
	{
		m_Exp.Convert();
	}

	for (int iObj = 0; iObj < ip->GetSelNodeCount(); iObj++)
	{
		INode* pNode = ip->GetSelNode(iObj);
		m_Exp.GetSelectNode(pNode);
	}
}
void UtilityExporter::DeleteThis()
{

}
void UtilityExporter::SetStartupParam(MSTR param)
{

}