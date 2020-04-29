#pragma once
#include "Engine.h"


bool Engine::Init()
{
	FSM.Init();

	StageMgr = new Stage; //스테이지 관리 
	StageMgr->Init();
	StageMgr->Load(L"bitmap/start.bmp");

	m_Player.Init();
	m_Player.Load(L"bitmap/rockman2.bmp", L"bitmap/ROCKMAN2colorAlpha.bmp");

	m_GustMan = new Enemy;
	m_GustMan->Init();
	m_GustMan->Load(L"bitmap/GUSTMAN.bmp");



	return true;
}
bool Engine::Frame()
{

	StageMgr->Process(&m_UI);

	if (StageMgr->m_pMapSene!=StageMgr->m_pMapList[SENE_START])
	{
		m_Player.Frame();
		m_GustMan->Process(&m_Player);
		
	}
	
	
	return true;
}
bool Engine::Render()
{
	
		StageMgr->Render();

	if (StageMgr->m_pMapSene != StageMgr->m_pMapList[SENE_START])
	{
		m_Player.Render();
		m_GustMan->Render();
	}
	
	return true;
}
bool Engine::Release()
{
	StageMgr->Release();
	m_Player.Release();
	m_GustMan->Release();
	FSM.Release();
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