#pragma once
#include "Sample.h"


bool Sample::Init()
{
	
	m_pMap = new JHMapObj;
	m_pPlayer = new JHPlayerObj;

	m_pMap->Init();
	m_pMap->Load(L"BitMap/map.bmp");
	m_pPlayer->Init();
	m_pPlayer->Load(L"BitMap/bitmap1Alpha.bmp");

	//m_Effect.Load(L"../../data/BitMap/bitmap1Alpha.bmp");
	for (int iObj = 0; iObj < 10; iObj++)
	{
		m_pNpc[iObj] = new JHNpcObj;
		m_pNpc[iObj]->Init();
		m_pNpc[iObj]->Load(
			L"BitMap/bitmap1.bmp",
			L"BitMap/bitmap1mask.bmp");
		RECT rtSNpc = { 46, 62, 68, 79 };
		m_pNpc[iObj]->m_rtSrc = rtSNpc;
	}

	RECT rtDMap = { 0,0,g_rtClient.right,m_rtClient.bottom };
	RECT rtSMap = { 0,0,m_pMap->m_BitMap->m_BMInfo.bmWidth,m_pMap->m_BitMap->m_BMInfo.bmHeight };
	m_pMap->m_BitMap->Set(rtDMap,rtSMap);

	/*RECT rtSEffect = { 0,0,m_Effect.m_BitMap.m_BMInfo.bmWidth,m_Effect.m_BitMap.m_BMInfo.bmHeight };
	m_Effect.m_rtSrc = rtSEffect;
*/
	RECT rtSPlayer = { 134,2,40,58 };
	m_pPlayer->SetPosition(400, 600);
	m_pPlayer->SetSrcRect(rtSPlayer);


	m_GameObjectList.push_back(m_pMap);
	m_GameObjectList.push_back(m_pPlayer);
	for (int iObj = 0; iObj < 10; iObj++)
	{
		m_GameObjectList.push_back(m_pNpc[iObj]);
	}

	
	return true;
}

bool Sample::Render()
{	
	for (auto pNode =m_GameObjectList.begin(); 
		pNode!=m_GameObjectList.end(); pNode++)
	{

			assert(*pNode);
		if (m_pPlayer == *pNode)
		{
			(*pNode)->DrawRotate();
		}
		else
		{
			(*pNode)->Render();
		}

	}
	//m_Effect.Render();
	return true;
}
bool Sample::Frame()
{
	for (auto pNode = m_GameObjectList.begin();
		pNode != m_GameObjectList.end(); pNode++)
	{

		assert(*pNode);
		
		(*pNode)->Frame();
	}
	return true;
}
bool Sample::Release()
{
	for (auto pNode = m_GameObjectList.begin();
		pNode != m_GameObjectList.end(); pNode++)
	{

		assert(*pNode);

		(*pNode)->Release();
	}
	m_GameObjectList.clear();
	return true;
}
Sample::Sample()
{

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