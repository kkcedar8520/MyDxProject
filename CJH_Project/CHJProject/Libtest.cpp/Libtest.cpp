#pragma once
#include"JH_Std.h"
#include"HCore.h"
#include"JH_Input.h"
#include"JHTimer.h"
HWND g_hwnd;
extern float g_SecondPerFrame;
class Sample :public HCore
{
public:
	float m_iX;
	float m_iY;
	JH_Input m_Input;
	JHTimer m_Timer;
public:
	void  ClientPrint(DWORD key)
	{
		HDC hdc = GetDC(g_hwnd);
		RECT rt;
		GetClientRect(g_hwnd, &rt);
		SetBkColor(hdc, RGB(255, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, m_iX, m_iY,
			m_Timer.m_SzBuffer,
			_tcslen(m_Timer.m_SzBuffer));
		ReleaseDC(g_hwnd, hdc);

	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	~Sample();

private:

};
bool Sample::Init()
{
	m_iX = 400;
	m_iY = 300;
	return true;
}
bool  Sample::Frame()
{
	SHORT Move_Key = m_Input.KeyCheck('w');

	if (Move_Key==KEY_HOLD||KEY_PUSH)
	{
		m_iY -= 10 * g_SecondPerFrame;
	}
	
	Move_Key = m_Input.KeyCheck('s');
	if (Move_Key == KEY_HOLD || KEY_PUSH)
	{
		m_iY +=	10 * g_SecondPerFrame;
	}

	Move_Key = m_Input.KeyCheck('a');
	if (Move_Key == KEY_HOLD || KEY_PUSH)
	{
		m_iX -= 10 * g_SecondPerFrame;
	}

	Move_Key = m_Input.KeyCheck('d');
	if (Move_Key == KEY_HOLD || KEY_PUSH)
	{
		m_iX += 10 * g_SecondPerFrame;
	}

	ClientPrint(Move_Key);
	return true;
}
bool  Sample::Render()
{
	return true;
}
bool  Sample::Release()
{
	return true;
}
Sample::Sample()
{
}

Sample ::~Sample()
{
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample game;
	game.m_hinstance = hInstance;
	if (!game.initWindow())
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}