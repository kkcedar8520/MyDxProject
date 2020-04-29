#include "HCore.h"
#include "JH_Std.h"

HDC g_hScreenDC;
HDC g_hOffScreenDC;
bool HCore::Init()
{
	return true;
}
bool HCore::Render()
{
	return true;
}
bool HCore::Frame()
{
	return true;
}
bool HCore::Release()
{
	return true;
}
bool HCore::CoreInit()
{
	m_gamerun = true;
	m_Input.Init();
	m_GameTimer.Init();

	m_hScreenDC = GetDC(m_hwnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBM = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);

	SelectObject(m_hOffScreenDC, m_hOffScreenBM);

	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;


	return Init();
}
bool HCore::PreRender()
{
	PatBlt(g_hOffScreenDC, 0, 0,
		m_rtClient.right,
		m_rtClient.bottom,
		PATCOPY);
	return true;
}

bool HCore::CoreRender()
{
	PreRender();
	Render();

	m_Input.Render();
	//m_GameTimer.Render();

	PostRender();
	return true;
}

bool HCore::PostRender()
{
	BitBlt(g_hScreenDC, 0, 0,
		m_rtClient.right,
		m_rtClient.bottom, //  대상
		g_hOffScreenDC, 0, 0,
		SRCCOPY); // 소스
	return true;
}

bool HCore::CoreFrame()
{

	m_Input.Frame();
	m_GameTimer.Frame();
	return Frame();
}
bool HCore::CoreRelease()
{
	m_Input.Release();
	m_GameTimer.Release();

	DeleteObject(m_hOffScreenBM);
	ReleaseDC(m_hwnd, m_hOffScreenDC);
	ReleaseDC(m_hwnd, m_hScreenDC);
	ReleaseDC(g_hwnd, g_hOffScreenDC);
	ReleaseDC(g_hwnd, g_hScreenDC);
	return Release();
}
bool HCore::Run()
{
	if (CoreInit() == false)
	{
		return false;
	}
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (m_gamerun)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			if (CoreFrame()==false)
			{
				return false;
			}
			if (CoreRender()==false)
			{
				return false;
			}
		}
	}
	if (CoreRelease() == false)
	{
		return false;
	}
	return true;
}
HCore::HCore()
{
	m_gamerun = false;
}


HCore::~HCore()
{
}