#include "Sample.h"


bool	Sample::Init()
{
	m_Player = make_shared<JH_Sprite>();
	m_Player->Create(m_pd3dDevice, m_pImmediateContext, 
		L"../../data/shader/DefaultShader.txt", L"../../data/bitmap/ROCKMAN2colorAlpha.bmp");
	
	m_map = make_shared<JH_ShapePlane>();
	m_map->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShader.txt", L"../../data/bitmap/Start.bmp");
	m_rtList.resize(10);
	m_rtList[0] = { 76,490,63,52 };
	m_rtList[1] = { 139,490,63,52 };
	m_rtList[2] = { 203,490,63,52 };
	m_rtList[3] = { 276,490,63,52 }; //RUN SHOT
	m_rtList[4] = { 343,490,63,52 };
	m_rtList[5] = { 404,490,63,52 };
	m_rtList[6] = { 462,490,63,52 };
	m_rtList[7] = { 521,490,63,52 };
	m_rtList[8] = { 583,490,63,52 };
	m_rtList[9] = { 651,490,63,52 };

	m_Player->SetArrayRect(m_rtList, 788, 1108, 1.0f);
	m_PlayerPos = D3DXVECTOR3(0.0, 0.0, 0.0f);

	ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	ApplySS(GetContext(), JH_DxState::g_pSamplerState);
	ApplyRS(GetContext(), JH_DxState::g_pRSSold);
	ApplyDSS(GetContext(), JH_DxState::g_pDSS);

	
	return true;
}
bool	Sample::Frame()
{
	
	if (G_Input.KeyCheck('A') != KEY_FREE)
	{
		m_PlayerPos = m_PlayerPos + D3DXVECTOR3(-50, 0.0f, 0.0f) * g_SecondPerFrame;

	}
	if (G_Input.KeyCheck('D') != KEY_FREE)
	{
		m_PlayerPos = m_PlayerPos + D3DXVECTOR3(50, 0.0f, 0.0f) * g_SecondPerFrame;

	}

	m_Player->Frame();
	/*m_pMainCamera->m_vPos.x = m_PlayerPos.x;
	m_pMainCamera->m_vAt.x = m_PlayerPos.x;*/
	return true;
}
bool	Sample::Render()
{
	
	

	m_Player->m_matWorld._11 = 1.0f;
	m_Player->m_matWorld._22 = 1.0f;
	m_Player->m_matWorld._41= m_PlayerPos.x;
	m_Player->m_matWorld._42 = m_PlayerPos.y;

	m_Player->SetMatrix(&m_Player->m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	m_Player->Render();
	/*m_map->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_map->Render();*/
	return true;
}
bool	Sample::Release()
{
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
	RECT rtClient = { 0,0,800,600 };
	if (!game.InitWindow(L"Refactoring", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}
