#include "StartScreen.h"
#include"Device.h"
#include"JH_Input.h"

bool StartScreen::Init()
{
	
	D3DXMATRIX matScaleWorld;
	m_Title.Create(m_pOwner->m_dxHelper.m_pd3dDevice, m_pOwner->m_dxHelper.m_pContext,
		L"RockManShader.txt", L"../../data/Resource/start.bmp");


	m_Title.m_matWorld._11 = 1000;
	m_Title.m_matWorld._22 = 600;
	m_Title.m_matWorld._43 = 1.0f;
	//D3DXMatrixScaling(&matScaleWorld, 500, 300, 0);
	
	m_matFinalWorld = matScaleWorld;
	
	return true;
}
void StartScreen::Process(JH_Model* pUser)
{
		if (G_Input.KeyCheck(VK_RETURN))
		{
			m_pOwner->SetTransition(EVENT_PRESSKEY);
		}
}
void  StartScreen::MatrixSet(D3DXMATRIX& pMatview,D3DXMATRIX& pMatOrthoProj)
{
	m_Title.SetMatrix(&m_matFinalWorld, &pMatview, &pMatOrthoProj);
}
bool StartScreen::Render()
{
	bSet = false;
	m_Title.Render();
	return true;
}

StartScreen::~StartScreen()
{
}
