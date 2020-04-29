#pragma once
#include "Sample.h"
#include"JH_DxState.h"
#include"JH_Input.h"
bool Sample::Init()
{

	m_MaxSkin.Load(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Character/man.skn");
	


	SkinObj* pObj = new SkinObj;
	pObj->Load(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Character/manpack.skn");

	//m_ObjList.push_back(pObj);
	//SkinObj* pObj2 = new SkinObj;
	//pObj2->Load(m_pd3dDevice, m_pImmediateContext, L"../../data/Character/Left.skn");
	//m_ObjList.push_back(pObj2);


	m_MaxBone.Load(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Character/man.act");

	m_DebigLine.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Shader/ColorBlend.txt", nullptr,"VSLine","PSLine");
	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -20.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);

	JDX::ApplySS(m_pImmediateContext.Get(), JDX::JH_DxState::g_pSamplerState);
	
	

	return true;
}
bool Sample::Frame()
{
	m_MaxBone.Frame();
	m_DebigLine.Frame();

	for ( int iObj = 0; iObj < m_MaxBone.m_ExpObject.size(); iObj++)
	{
		m_MaxSkin.m_MatBoneWorld[iObj]=m_MaxBone.m_ExpObject[iObj].m_matCalculation;
	}
	if (G_Input.KeyCheck(VK_UP)==KEY_PUSH)
	{
		m_MaxSkin.m_matWorld._43 -= g_SecondPerFrame * 10;

	}
	if (G_Input.KeyCheck(VK_DOWN) == KEY_PUSH)
	{
		m_MaxSkin.m_matWorld._43 += g_SecondPerFrame * 10;

	}
 	m_MaxSkin.Frame();
	for(auto& obj :m_ObjList)
	{
		SkinObj* sObj =(SkinObj*) obj;
		for (int iObj = 0; iObj < m_MaxBone.m_ExpObject.size(); iObj++)
		{

			sObj->m_MatBoneWorld[iObj] = m_MaxBone.m_ExpObject[iObj].m_matCalculation;
		}
		sObj->Frame();
	}


	return true;
}
bool Sample::Render()
{


	for(auto& obj:m_ObjList)
	{
		obj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		obj->Render();
	}
	m_MaxSkin.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_MaxSkin.Render();
/*	m_MaxBone.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_MaxBone.Render()*/;

	m_DebigLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_DebigLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 0, 0), D3DXVECTOR4(1,0 , 0, 1));
	m_DebigLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 100, 0), D3DXVECTOR4(0, 1, 0, 1));
	m_DebigLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 100), D3DXVECTOR4(0, 0, 1, 1));
	D3DXMatrixIdentity(&m_MaxSkin.m_matWorld);
	
	return true;
}
bool Sample::Release()
{
	for (int i = 0; i < m_ObjList.size(); i++)
	{
		delete	m_ObjList[i];
	}
	m_MaxSkin.Release();
	m_MaxBone.Release();
	return true;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}
RECT rtClient = { 0,0,1000,600 };

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	Sample game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ModelAseViewer", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;
}
