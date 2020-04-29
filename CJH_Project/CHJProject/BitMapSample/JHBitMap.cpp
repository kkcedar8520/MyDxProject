#pragma once
#include "JHBitMap.h"
#include "HWindow.h"
HWND g_hwnd;
HDC g_hScreenDC;
HDC g_hOffScreenDC;
bool JHBitMap::LoadBitMap(const TCHAR* pFileName)
{
	m_hBitMap = (HBITMAP)::LoadImage(g_hInstance, 
		pFileName, 
		IMAGE_BITMAP, 
		0, 0, 
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	g_hScreenDC = GetDC(g_hwnd);
	g_hOffScreenDC = CreateCompatibleDC(g_hScreenDC);
	m_hOffScreenBitMap = CreateCompatibleBitmap(g_hScreenDC, 500, 500);
	
	m_TempScreenDC = CreateCompatibleDC(g_hScreenDC);
	
	SelectObject(g_hOffScreenDC, m_hOffScreenBitMap);
	SelectObject(m_TempScreenDC, m_hBitMap);
	GetObject(m_hBitMap, sizeof(BITMAP),&m_BMInfo);

	m_rtSrc.left = 0;
	m_rtSrc.top = 0;
	m_rtSrc.right = m_BMInfo.bmWidth;
	m_rtSrc.bottom = m_BMInfo.bmHeight;

	return true;
	
}

void JHBitMap::Set(RECT&rtDesk, RECT&rtSrc)
{
	m_rtDesk = rtDesk;
	m_rtSrc = rtSrc;

}
bool JHBitMap::Init()
{
	return true;

}
bool JHBitMap::PreRender()
{
	PatBlt(g_hOffScreenDC, 0, 0, 500, 500, SRCCOPY);
	
	return true;
}
bool JHBitMap::Render()
{
	BitBlt(g_hOffScreenDC, m_rtDesk.left,m_rtDesk.top,m_rtDesk.right,m_rtDesk.bottom,
		m_TempScreenDC, m_rtSrc.left,m_rtSrc.top, SRCCOPY);

	return true;
}
bool JHBitMap::PostRender()
{
	BitBlt(g_hScreenDC, 0, 0, 500, 500,
		g_hOffScreenDC, 0,0, SRCCOPY);

	return true;
}

bool JHBitMap::Draw(RECT rtDesk, RECT rtSrc)
{
	BitBlt(g_hOffScreenDC, rtDesk.left, rtDesk.top, rtDesk.right, rtDesk.bottom,
		m_TempScreenDC, rtSrc.left, rtSrc.top,SRCCOPY);
	
	return true;
}
bool JHBitMap::Frame()
{
	return true;
}
bool JHBitMap::Release()
{
	DeleteObject(m_hBitMap);
	ReleaseDC(g_hwnd, m_TempScreenDC);
	ReleaseDC(g_hwnd,g_hScreenDC );
	return true;
}
JHBitMap::JHBitMap()
{

}


JHBitMap::~JHBitMap()
{
}
