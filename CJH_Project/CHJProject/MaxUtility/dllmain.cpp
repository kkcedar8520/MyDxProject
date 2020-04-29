// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include"Header.h"

HINSTANCE hInstance;
int controlsInit = FALSE;
extern ClassDesc2* GetExportDesc();
BOOL APIENTRY DllMain( HMODULE hinstDLL,
                      ULONG fdwReason,
                       LPVOID lpReserved
                     )
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// Hang on to this DLL's instance handle.
		hInstance = hinstDLL;
	
		// DO NOT do any initialization here. Use LibInitialize() instead.
	}
	return(TRUE);
}

__declspec(dllexport) const TCHAR* LibDescription()
{
	return _T("kgcaExporter 100");
}

__declspec(dllexport) int LibNumberClasses()
{
	return 1;
}

__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
	switch (i) {
	case 0: return GetExportDesc();
	default: return 0;
	}
}

__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec(dllexport) int LibInitialize(void)
{
#pragma message(TODO("Perform initialization here."))
	return TRUE;
}

__declspec(dllexport) int LibShutdown(void)
{
#pragma message(TODO("Perform un-initialization here."))
	return TRUE;
}