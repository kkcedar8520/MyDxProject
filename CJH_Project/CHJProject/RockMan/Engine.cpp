#pragma once
#include "Engine.h"


bool Engine::Init()
{
	FSM.Init();

	StageMgr = new Stage; //스테이지 관리 
	StageMgr->Init();

	m_Player.Init();
	m_Player.Load(L"bitmap/rockman2.bmp");

	return true;
}
bool Engine::Frame()
{

	StageMgr->Process(&m_UI);

	if (StageMgr->m_pMapSene!=StageMgr->m_pMapList[SENE_START])
	{
		m_Player.Frame();
	}
	
	
	return true;
}
bool Engine::Render()
{
	StageMgr->Render();
	if (StageMgr->m_pMapSene != StageMgr->m_pMapList[SENE_START])
	{
		m_Player.Render();
	}
	
	return true;
}
bool Engine::Release()
{
	StageMgr->Release();
	m_Player.Release();
	return true;
}

Engine::Engine()
{
}


Engine::~Engine()
{
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Engine game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,780,560 };
	if (!game.initWindow(L"ROCK_MAN",rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}