#pragma once
#include"JH_Std.h"

class JHBitMap
{
public:
	HBITMAP m_hBitMap;
	HBITMAP m_hOffScreenBitMap;
	HDC		m_TempScreenDC;
	BITMAP  m_BMInfo;
	HWND	m_hwnd;
	RECT	m_rtDesk;
	RECT	m_rtSrc;
	
public:
	void Set(RECT&rtDesk,RECT&rtSrc);

	bool PreRender();
	bool PostRender();
	bool LoadBitMap(const TCHAR* pFileName);
	bool Draw(RECT m_rtDesk,RECT m_rtSrc);
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
	JHBitMap();
	~JHBitMap();
};

