#pragma once
#include "Sample.h"


bool Sample::Init()
{
	srand(time(NULL));
	m_Map.LoadBitMap(L"map.bmp");
	m_Boom.LoadBitMap(L"boom.bmp");
	m_Player.LoadBitMap(L"bitmap1.bmp");

	RECT rtDMap = { 0,0,g_rtClient.right,g_rtClient.bottom };
	RECT rtSMap = { 0,0,m_Map.m_BMInfo.bmWidth,m_Map.m_BMInfo.bmHeight };
	m_Map.Set(rtDMap, rtSMap);

	RECT rtDBoom = { rand() % 250,rand() % 250,64,64 };
	RECT rtSBoom = { 0,0,m_Boom.m_BMInfo.bmWidth,m_Boom.m_BMInfo.bmHeight };
	m_Boom.Set(rtDBoom, rtSBoom);

	RECT rtDPlayer = { m_fX_POSI,m_fY_POSI,40,58 };
	RECT rtSPlayer = { 134,2,m_Player.m_BMInfo.bmWidth,m_Player.m_BMInfo.bmHeight };
	m_Player.Set(rtDPlayer, rtSPlayer);

	return true;
}
bool Sample::Render()
{
	m_Map.Render();
	m_Boom.Render();
	m_Player.Render();




	return true;
}
bool Sample::Frame()
{
	return true;
}
bool Sample::Release()
{

	m_Map.Release();
	m_Boom.Release();
	return true;
}
Sample::Sample()
{
	m_fX_POSI = 250;
	m_fY_POSI = 250;
}


Sample::~Sample()
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