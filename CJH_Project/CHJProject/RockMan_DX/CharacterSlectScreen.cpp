#include "CharacterSlectScreen.h"
#include"JH_Input.h"

bool CharacterSlectScreen::Init()
{
	m_Characters.Create(m_pOwner->m_dxHelper.m_pd3dDevice, m_pOwner->m_dxHelper.m_pContext,
		L"RockManShader.txt", L"../../data/Resource/[크기변환]CharcterSelect.GIF");
	m_CSeletcbar.Create(m_pOwner->m_dxHelper.m_pd3dDevice, m_pOwner->m_dxHelper.m_pContext,
		L"RockManShader.txt", L"../../data/Resource/SelectCorsor.GIF");
	return true;
}
bool CharacterSlectScreen::Render()
{
	m_Characters.Render();
	m_CSeletcbar.Render();

	return true;
}

void CharacterSlectScreen::Process(JH_Model*User)
{
	


	if (G_Input.KeyCheck(VK_RIGHT))
	{
		if (m_CSeletcbar.m_Pos.x<325)
		{
			m_CSeletcbar.m_Pos.x + 50*g_SecondPerFrame;
		}

	}
	else
	{

	}

	if (G_Input.KeyCheck(VK_LEFT))
	{
		if (m_CSeletcbar.m_Pos.x  <-400)
		{
			m_CSeletcbar.m_Pos.x - 100 * g_SecondPerFrame;
		}
	}
	if (G_Input.KeyCheck('A'))
	{
		m_pOwner->SetTransition(EVENT_SELECT_CHARACTER);
		m_pOwner->b_Waiting = false;
	}
	

}

CharacterSlectScreen::~CharacterSlectScreen()
{
}
