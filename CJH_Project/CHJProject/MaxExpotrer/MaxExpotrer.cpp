

#include"GlobalExp.h"
#define cjhMaxExporterID Class_ID(0x4c804dff, 0x7dc142b);
////이중 대부분은 플러그인의 파일 확장자나 정보를 돌려주기 위한 TCHAR* 형을 반환하는 함수이고
//가장 중요한 함수는 바로 DoExport이다.
//이 녀석은 맥스에서 실제로 Export명령이 실행되었을때 불려지게 되고
//이 곳에서 파일을 열고 맥스에서 오브젝트 정보를 얻어와서 파일에 쓰는 라인을 작성해 주면 된다.

class cjhExporter : public SceneExport {
public:
	GlobalExp m_Exp;

	cjhExporter() {};
	~cjhExporter() {};
public:
	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);

};

class ExportClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return new cjhExporter(); }
	virtual const TCHAR *	ClassName() { return _T("cjhMaxExporter100"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return cjhMaxExporterID; }
	virtual const TCHAR* Category() { return _T("cjhMaxExporter"); }

	virtual const TCHAR* InternalName() { return _T("cjhMaxExporterClassDesc"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle


};
ClassDesc2* GetExportDesc() {
	static ExportClassDesc cjhExporterDesc;
	return &cjhExporterDesc;
}


int				 cjhExporter::ExtCount()
{
	return 1;
}
const TCHAR *	cjhExporter::Ext(int n)
{
	return _T("cjh");
}
const TCHAR *	cjhExporter::LongDesc()
{
	return _T("CJH_MAX_Exporter");
}
const TCHAR *	cjhExporter::ShortDesc()
{
	return _T("CJH_Exporter");
}
const TCHAR *	cjhExporter::AuthorName()
{
	return _T("PROKVIP");
}
const TCHAR *	cjhExporter::CopyrightMessage()
{
	return _T("");
}
const TCHAR *	cjhExporter::OtherMessage1()
{
	return _T("");
}
const TCHAR *	cjhExporter::OtherMessage2()
{
	return _T("");
}
unsigned int	cjhExporter::Version()
{
	return 100;
}
void			cjhExporter::ShowAbout(HWND hWnd)
{

}
BOOL cjhExporter::SupportsOptions(int ext, DWORD options)
{
	return TRUE;
}
// name:: 파일이름 ei : i: max인터페이스 
int cjhExporter::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts , DWORD options)
{
	if (m_Exp.Init(i))
	{
		m_Exp.Exporter(name);

	}
	
	return FALSE;
}