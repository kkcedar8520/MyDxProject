#include "JH_EffectMgr.h"
#include"JH_Player.h"
bool JH_EffectMgr::Init()
{
	m_EffectRTList.resize(EFFECT_COUNT);
	m_EffectRTList[CHARGING].resize(6);
	m_EffectRTList[SHOT_SPECTRUM].resize(4);
	m_EffectRTList[CHARGINGSHOT_SPECTRUM].resize(6);

	
	m_EffectRTList[CHARGING][0] = { 169,900,77,64 };
	m_EffectRTList[CHARGING][1] = { 252,900,77,64 };
	m_EffectRTList[CHARGING][2] = { 343,900,77,64 };
	m_EffectRTList[CHARGING][3] = { 438,900,77,64 };
	m_EffectRTList[CHARGING][4] = { 528,898,77,68 };
	m_EffectRTList[CHARGING][5] = { 621,898,77,68 };

	m_EffectRTList[SHOT_SPECTRUM][0] = { 153,266,23,22 };
	m_EffectRTList[SHOT_SPECTRUM][1] = { 191,266,33,22 };
	m_EffectRTList[SHOT_SPECTRUM][2] = { 238,262,38,25 };
	m_EffectRTList[SHOT_SPECTRUM][3] = { 293,261,42,28 };


	m_EffectRTList[CHARGINGSHOT_SPECTRUM][0] = { 132,316,27,24 };
	m_EffectRTList[CHARGINGSHOT_SPECTRUM][1] = { 168,308,37,43 };
	m_EffectRTList[CHARGINGSHOT_SPECTRUM][2] = { 224,301,47,52, };
	m_EffectRTList[CHARGINGSHOT_SPECTRUM][3] = { 287,298,54,59 };
	m_EffectRTList[CHARGINGSHOT_SPECTRUM][4] = { 362,297,56,58 };
	m_EffectRTList[CHARGINGSHOT_SPECTRUM][5] = { 433,296,61,58 };

	SetArrayRect(m_EffectRTList, 788, 1108, 1.0F, EFFECT_COUNT);


	


	return true;
}
bool JH_EffectMgr::Frame()
{
	for (int i = 0; i < m_EInformList.size(); )
	{
		 m_EInformList[i].Frame();
		if (m_EInformList[i].m_iIndex== m_EInformList[i].m_MaxIndex)
		{
			
			m_EInformList.erase(m_EInformList.begin() + i);
		}
		else
		{
			i++;
		}
	}
	
	return true;
}
bool JH_EffectMgr::SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime, DWORD EffectNum)
{



	for (int i = 0; i < EffectNum; i++)
	{
		m_iNumSpriteIndex = DrtList[i].size();
		for (int rtN = 0; rtN < m_iNumSpriteIndex; rtN++)
		{
			JRECT rt;
			ZeroMemory(&rt, sizeof(JRECT));
			rt.uv[0].x = DrtList[i][rtN].left / (float)width;
			rt.uv[0].y = DrtList[i][rtN].top / (float)height;
			rt.uv[1].x = (DrtList[i][rtN].left + DrtList[i][rtN].right) / (float)width;
			rt.uv[1].y = DrtList[i][rtN].top / (float)height;
			rt.uv[2].x = DrtList[i][rtN].left / (float)width;
			rt.uv[2].y = (DrtList[i][rtN].top + DrtList[i][rtN].bottom) / (float)height;
			rt.uv[3].x = (float)rt.uv[1].x;
			rt.uv[3].y = (float)rt.uv[2].y;


			m_EffectUVList[i].push_back(rt);
		}
		m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
	}
	return true;
}
bool JH_EffectMgr::PostRender()
{

	for (int i = 0; i < m_EInformList.size(); i++)
	{


		m_VertexData[0].t = m_EffectUVList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].uv[0];
		m_VertexData[1].t = m_EffectUVList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].uv[1];
		m_VertexData[2].t = m_EffectUVList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].uv[2];
		m_VertexData[3].t = m_EffectUVList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].uv[3];

		m_VertexData[0].p.x = m_EInformList[i].m_EffectPos.x-m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].right;
		m_VertexData[0].p.y = m_EInformList[i].m_EffectPos.y+m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].bottom;
		m_VertexData[1].p.x = m_EInformList[i].m_EffectPos.x+m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].right;
		m_VertexData[1].p.y = m_EInformList[i].m_EffectPos.y+m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].bottom;
		m_VertexData[2].p.x = m_EInformList[i].m_EffectPos.x-m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].right;
		m_VertexData[2].p.y = m_EInformList[i].m_EffectPos.y-m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].bottom;
		m_VertexData[3].p.x = m_EInformList[i].m_EffectPos.x+m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].right;
		m_VertexData[3].p.y = m_EInformList[i].m_EffectPos.y-m_EffectRTList[m_EInformList[i].m_EffectState][m_EInformList[i].m_iIndex].bottom;
		if (JH_Player::b_Left)
		{
			D3DXVECTOR3 temp = D3DXVECTOR3(0, 0, 0);
			temp.x = m_VertexData[0].p.x;
			m_VertexData[0].p.x=m_VertexData[1].p.x;
			m_VertexData[1].p.x =temp.x;
			m_VertexData[2].p.x= m_VertexData[0].p.x;
			m_VertexData[3].p.x = m_VertexData[1].p.x;
		}

		m_dxHelper.m_pContext->UpdateSubresource(m_dxHelper.m_pVertexBuffer, 0, nullptr, &m_VertexData.at(0), 0, 0);
		m_dxHelper.PostRender();
	}
	

	return true;
}
bool JH_EffectMgr::Release()
{
	
	return true;
}
void  JH_EffectMgr::SetEffectState(DWORD &EffectState)
{
	m_EffectState = EffectState;
}
JH_EffectMgr::JH_EffectMgr()
{
	g_PlayerPos =D3DXVECTOR3(0,0,0.5f);
	m_iIndex = 0;
	b_Waiting = true;
	m_EffectState = CHARGING;
	m_EffectUVList.resize(EFFECT_COUNT);
}


JH_EffectMgr::~JH_EffectMgr()
{
}
