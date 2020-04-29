#include "Engine.h"


bool Engine::Init()
{
	

	m_Player = make_shared<JH_Player>();
	m_Player->Create(m_pd3dDevice,m_pImmediateContext,
		L"RockManShader.txt", L"../../data/Resource/ROCKMAN2colorAlpha.bmp");

	/*m_GutsMan = make_shared<GutsMan>();
	m_GutsMan->Create(m_pd3dDevice,m_pImmediateContext, L"RockManShader.txt", L"../../data/Resource/GUSTMANcolor.bmp");
*/
	m_Stage = make_shared<JH_Srcreen>();
	m_Stage->Create(m_pd3dDevice,m_pImmediateContext, L"RockManShader.txt",NULL);
	



	I_EffectMgr = make_shared < JH_EffectMgr>();
	I_EffectMgr->Create(Device::m_pd3dDevice, Device::m_pImmediateContext,
		L"RockManShader.txt", L"../../data/Resource/ROCKMAN2colorAlpha.bmp");



	
	ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	ApplySS(GetContext(), JH_DxState::g_pSamplerState);
	ApplyRS(GetContext(), JH_DxState::g_pRSSold);
	ApplyDSS(GetContext(), JH_DxState::g_pDSS);
	return true;
}
bool Engine::Frame()
{
	m_Stage->Process(m_Player.get());

	if (m_Stage->b_Waiting !=true)
	{
		m_Player->Frame();
		I_EffectMgr->Frame();
	/*	m_GutsMan->Process(m_Player.get());*/
	}
	

	//D3DXVECTOR3 Interval = D3DXVECTOR3(0, 0, 0);
	//if (m_Player->g_PlayerPos.x>400)
	//{
	//
	//	Interval.x=m_Player->g_PlayerPos.x - 400;

	//	m_pMainCamera->m_vPos.x += Interval.x;
	//	m_pMainCamera->m_vAt.x += Interval.x;
	//}
	//if (m_Player->g_PlayerPos.x < -400)
	//{
	//	Interval.x = m_Player->g_PlayerPos.x + 400;

	//	m_pMainCamera->m_vPos.x += Interval.x;
	//	m_pMainCamera->m_vAt.x += Interval.x;
	//}
	return true;
}
bool Engine::Render()
{
	
	m_Stage->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	m_Stage->m_pScreen->MatrixSet(m_pMainCamera->m_matView, m_pMainCamera->m_matOrthoProj);
	m_Stage->Render();

	if (m_Stage->b_Waiting != true)
	{
		m_Player->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
		m_Player->m_Shot->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
		I_EffectMgr->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
		m_Player->Render();
		
		I_EffectMgr->Render();
	}
	
	return true;
}
bool Engine::Release()
{
	m_Stage->Release();
	m_Player->Release();
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
	_In_ int       nCmdShow){
	Engine game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ROCKMAN", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;
}