#pragma once
#include "JHBitMap.h"


bool JHBitMap::LoadBitMap(const TCHAR* pFileName)
{
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, 0,
		NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwRead, dwDataSize;

	DWORD dwHeadSize = sizeof(BITMAPFILEHEADER);

	BITMAPFILEHEADER m_bitmapFileHeader;

	ReadFile(hFile, &m_bitmapFileHeader,
		dwHeadSize, &dwRead, NULL);

	dwDataSize = m_bitmapFileHeader.bfOffBits - dwHeadSize;

	BITMAPINFO* pBitInfo = (BITMAPINFO*)malloc(dwDataSize);

	ReadFile(hFile, pBitInfo,
		dwDataSize, &dwRead, NULL);

	
	DWORD pixelDataSize = m_bitmapFileHeader.bfSize - m_bitmapFileHeader.bfOffBits;

	PVOID pRaster = nullptr;


	m_hBitMap = CreateDIBSection(g_hScreenDC, pBitInfo, DIB_RGB_COLORS,
		&pRaster, NULL,0);

	ReadFile(hFile, pRaster, pixelDataSize, &dwRead, NULL);

	free(pBitInfo);
	CloseHandle(hFile);
	



	/*m_hBitMap = (HBITMAP)::LoadImage(g_hInstance, 
		pFileName, 
		IMAGE_BITMAP, 
		0, 0, 
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
*/
	m_TempScreenDC = CreateCompatibleDC(g_hScreenDC);
	
	HBITMAP oldbitmap=(HBITMAP)SelectObject(m_TempScreenDC, m_hBitMap);

	DeleteObject(oldbitmap);

	GetObject(m_hBitMap, sizeof(BITMAP),&m_BMInfo);

	m_rtSrc.left = 0;
	m_rtSrc.top = 0;
	m_rtSrc.right = m_BMInfo.bmWidth;
	m_rtSrc.bottom = m_BMInfo.bmHeight;

	return true;
	
}

void JHBitMap::Set(RECT&rtDesk, RECT&rtSrc)
{
	m_rtDest = rtDesk;
	m_rtSrc = rtSrc;

}
bool JHBitMap::Init()
{
	return true;

}


bool JHBitMap::Render()
{
	BitBlt(g_hOffScreenDC, m_rtDest.left, m_rtDest.top, m_rtDest.right, m_rtDest.bottom,
		m_TempScreenDC, m_rtSrc.left, m_rtSrc.top, SRCCOPY);
	
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
	
	ReleaseDC(g_hwnd,m_TempScreenDC);
	return true;
}
JHBitMap::JHBitMap()
{

}


JHBitMap::~JHBitMap()
{
}
