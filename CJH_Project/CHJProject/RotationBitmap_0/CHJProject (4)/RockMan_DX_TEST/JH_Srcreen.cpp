#pragma once

#include"StartScreen.h"
#include"CharacterSlectScreen.h"
//#include"GutsManScreen.h"


bool JH_Srcreen::Init()
{
	JH_Model::Init();
	
	m_dwScreenState= START_SCREEN;


	m_pScreenList[START_SCREEN] = make_shared<StartScreen>(this);
	m_pScreenList[START_SCREEN]->Init();
	/*m_pScreenList[CHARACTER_SLECT_SCREEN] = make_shared<CharacterSlectScreen>(this);
	m_pScreenList[CHARACTER_SLECT_SCREEN]->Init();*/
	//m_pScreenList[GUSTMAN_SCREEN] = make_shared<GutsManScreen>(this);

	
	m_pScreen = m_pScreenList[m_dwScreenState];
	return  true;
}

bool  JH_Srcreen::Frame()
{

	return true;
}
bool JH_Srcreen::Render()
{
	JH_ShapePlane::Render();
	m_pScreen->Render();
	return true;
}
void JH_Srcreen::Process(JH_Model*user)
{
	m_pScreen->Process(user);

}
void JH_Srcreen::SetTransition(DWORD dwEvent)
{
	m_dwScreenState = FSM.output(m_dwScreenState, dwEvent);
	m_pScreen = m_pScreenList[m_dwScreenState];

}

//bool JH_Srcreen::SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime)
//{
//
//
//
//	for (int i = 0; i < GCOUNT; i++)
//	{
//		m_iNumSpriteIndex = DrtList[i].size();
//		for (int rtN = 0; rtN < m_iNumSpriteIndex; rtN++)
//		{
//			JRECT rt;
//			ZeroMemory(&rt, sizeof(JRECT));
//			rt.uv[0].x = DrtList[i][rtN].left / (float)width;
//			rt.uv[0].y = DrtList[i][rtN].top / (float)height;
//			rt.uv[1].x = (DrtList[i][rtN].left + DrtList[i][rtN].right) / (float)width;
//			rt.uv[1].y = DrtList[i][rtN].top / (float)height;
//			rt.uv[2].x = DrtList[i][rtN].left / (float)width;
//			rt.uv[2].y = (DrtList[i][rtN].top + DrtList[i][rtN].bottom) / (float)height;
//			rt.uv[3].x = (float)rt.uv[1].x;
//			rt.uv[3].y = (float)rt.uv[2].y;
//
//
//			m_uvList[i].push_back(rt);
//		}
//		m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
//	}
//	return true;
//}
JH_Srcreen::JH_Srcreen()
{
	b_Waiting = true;
	m_dwScreenState=0;
	m_fTimer = 0;
	b_Left = false;;
	m_iSpriteindex = 0;
}


JH_Srcreen::~JH_Srcreen()
{
}
