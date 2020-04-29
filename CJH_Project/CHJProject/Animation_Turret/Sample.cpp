#include "Sample.h"
#include"JH_DxState.h"

bool Sample::Init()
{

	m_AseBox.Load(m_pd3dDevice, m_pImmediateContext, L"../../data/Obj/Turret.ASE");

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -20.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);

	JDX::ApplySS(m_pImmediateContext, JDX::JH_DxState::g_pSamplerState);



	return true;
}
bool Sample::Frame()
{
	m_AseBox.Frame();
	return true;
}
bool Sample::Render()
{
	m_AseBox.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_AseBox.Render();
	return true;
}
bool Sample::Release()
{
	m_AseBox.Release();
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
