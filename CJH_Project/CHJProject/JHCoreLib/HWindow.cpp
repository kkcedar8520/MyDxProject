#include "HWindow.h"



HWindow* g_wnd;
HINSTANCE g_hInstance;
HWND g_hwnd;
RECT g_rtClient;
LRESULT CALLBACK S_JWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	int iRET = g_wnd->JWndProc(hwnd, message, wparam, lparam);
	if (iRET >= 0)
	{
		return 1;
	}
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hwnd,message,wparam,lparam);


}
HWindow::HWindow()
{
	g_wnd = this;
}


HWindow::~HWindow()
{
}
bool HWindow::initWindow(const TCHAR* pTitleName, RECT rtClient)
{
	g_hInstance = m_hinstance;
	// 윈도우 클래스 레지스터 등록
	WNDCLASSEX wndcex;
	ZeroMemory(&wndcex, sizeof(WNDCLASSEX));
	wndcex.cbSize = sizeof(WNDCLASSEX);
	wndcex.style = CS_HREDRAW | CS_VREDRAW;
	wndcex.lpfnWndProc = S_JWndProc;
	wndcex.hInstance = m_hinstance;
	wndcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcex.lpszClassName = L"H.WindowSample";
	wndcex.lpszMenuName = NULL;
	if (!RegisterClassEx(&wndcex))
		return false;


	AdjustWindowRect(&rtClient, WS_OVERLAPPEDWINDOW, FALSE);


	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"H.WindowSample",
		NULL,

		WS_OVERLAPPEDWINDOW,

		0,0,rtClient.right-rtClient.left , rtClient.bottom-rtClient.top,
		NULL,
		NULL,
		m_hinstance,
		NULL);
	
	if (!m_hwnd)
	{
		return false;
	}
	GetClientRect(m_hwnd, &m_rtClient);

	g_hwnd = m_hwnd;
	g_rtClient = m_rtClient;
	ShowWindow(m_hwnd,SW_SHOW);
	return true;

}
LRESULT CALLBACK HWindow::JWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return -1;
}
bool  HWindow::init()
{
	return true;
}
bool HWindow::Render()
{
	return true;
}

bool HWindow::Release()
{
	return true;
}
bool HWindow::Frame()
{
	return true;
}