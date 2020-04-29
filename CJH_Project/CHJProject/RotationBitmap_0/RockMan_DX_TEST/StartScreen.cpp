#include "StartScreen.h"
#include"Device.h"
#include"JH_Input.h"

bool StartScreen::Init()
{
	D3DXMATRIX matScaleWorld,matTransWorld;
	m_Title.Create(Device::m_pd3dDevice, Device::m_pImmediateContext,
		L"RockManShader.txt", L"powerbattles_title");

	D3DXMatrixTranslation(&matTransWorld, 0,600, 0);
	D3DXMatrixScaling(&matScaleWorld, 238, 125, 0);
	
	m_matFinalWorld = matTransWorld * matScaleWorld;
	
	return true;
}
void StartScreen::Process(JH_Model* pUser)
{
	
	if (m_Title.m_Pos.y>=58)
	{
		
		m_Title.m_matWorld._42 -= 200 * g_SecondPerFrame;
	}
	else
	{
		bSet = true;
		m_Title.m_Pos.y = 58;
	}
	
	
	if (bSet==true)
	{
		if (G_Input.KeyCheck(VK_RETURN))
		{
			m_pOwner->SetTransition(EVENT_PRESSKEY);
		}
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
