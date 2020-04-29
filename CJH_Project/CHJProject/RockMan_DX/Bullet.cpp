#include "Bullet.h"
#include"JH_Input.h"
// 위치 값과 상태 값과 인덱스 시간초를 가지고있는  구조체를 큐로 만들어서 프레임을 돌리고 

bool JH_Bullet::Init()
{
	m_BulletRTList.resize(2);

	m_BulletRTList[SHOT].resize(4);
	m_BulletRTList[CHARGINGSHOT].resize(4);

	m_BulletRTList[SHOT][0] = { 355,266, 23, 18 };
	m_BulletRTList[SHOT][1] = { 393,269, 23, 13 };
	m_BulletRTList[SHOT][2] = { 430,269, 23, 13 };
	m_BulletRTList[SHOT][3] = { 467,266, 23, 22 };
	
	m_BulletRTList[CHARGINGSHOT][0] = { 515,312,61,24 };
	m_BulletRTList[CHARGINGSHOT][1] = { 589,313,57,24 };
	m_BulletRTList[CHARGINGSHOT][2] = { 658,313,56,22 };
	m_BulletRTList[CHARGINGSHOT][3] = { 731,312,41,26 };

	SetArrayRect(m_BulletRTList, 788, 1108, 1.0f, m_BulletRTList.size());

	return true;
}
	
void JH_Bullet::SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime, DWORD EffectNum)
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

			
			m_BulletUVList[i].push_back(rt);
		}
		m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
	}

}
	
bool JH_Bullet::Frame()
{
	Key_State = G_Input.KeyCheck('A');
	if (Key_State)
	{
		m_fRetentiontime += g_SecondPerFrame;
	
	}
	

	if (Key_State ==KEY_UP)
	{
		if (m_fRetentiontime > 1.0f)
		{
			BulletInform Bf(m_Direct,m_BulletPos);// AA위치 값과 상태 값과 인덱스 시간초를 가지고있는  클래스
			Bf.BulletState = CHARGINGSHOT;  
			m_vBulletList.push_back(Bf);

			PlayerEffectInform pInform;
			
				pInform.SetEffect(CHARGINGSHOT_SPECTRUM, m_BulletPos, 3,m_Direct);
				I_EffectMgr->m_EInformList.push_back(pInform);
		
		
			m_fRetentiontime = 0;
		}
		else
		{
			BulletInform Bf(m_Direct, m_BulletPos);
			Bf.BulletState = SHOT;
			m_vBulletList.push_back(Bf);
		
			PlayerEffectInform pInform;
			
			pInform.SetEffect(SHOT_SPECTRUM, m_BulletPos, 3,m_Direct);
			I_EffectMgr->m_EInformList.push_back(pInform);

			m_fRetentiontime = 0;

		}
	}


	for (int i = 0; i < m_vBulletList.size(); )
	{
		m_vBulletList[i].Frame();
		if (m_vBulletList[i].vBulletPos.x<-600|| m_vBulletList[i].vBulletPos.x > 600)
		{
			
			m_vBulletList.erase(m_vBulletList.begin() + i);
		}
		else
		{
			i++;
		}

	}

	
	return true;
}
bool JH_Bullet::PostRender()
{

		for (m_Count= 0; m_Count < m_vBulletList.size(); m_Count++)
		{
			m_VertexData[0].t = m_BulletUVList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].uv[0];
			m_VertexData[1].t = m_BulletUVList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].uv[1];
			m_VertexData[2].t = m_BulletUVList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].uv[2];
			m_VertexData[3].t = m_BulletUVList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].uv[3];

			m_VertexData[0].p.x = m_vBulletList[m_Count].vBulletPos.x - m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].right;
			m_VertexData[0].p.y = m_vBulletList[m_Count].vBulletPos.y + m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].bottom;
			m_VertexData[1].p.x = m_vBulletList[m_Count].vBulletPos.x + m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].right;
			m_VertexData[1].p.y = m_vBulletList[m_Count].vBulletPos.y + m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].bottom;
			m_VertexData[2].p.x = m_vBulletList[m_Count].vBulletPos.x - m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].right;
			m_VertexData[2].p.y = m_vBulletList[m_Count].vBulletPos.y - m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].bottom;
			m_VertexData[3].p.x = m_vBulletList[m_Count].vBulletPos.x + m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].right;
			m_VertexData[3].p.y = m_vBulletList[m_Count].vBulletPos.y - m_BulletRTList[m_vBulletList[m_Count].BulletState][m_vBulletList[m_Count].m_iIndex].bottom;

	

			if (m_vBulletList[m_Count].m_Direct)
			{
				D3DXVECTOR3 temp = D3DXVECTOR3(0, 0, 0);
				
				temp.x = m_VertexData[0].p.x;
				m_VertexData[0].p.x = m_VertexData[1].p.x;
				m_VertexData[1].p.x = temp.x;
				m_VertexData[2].p.x = m_VertexData[0].p.x;
				m_VertexData[3].p.x = m_VertexData[1].p.x;

				m_VertexData[0].p.x -= 110;
				m_VertexData[1].p.x -= 110;
				m_VertexData[2].p.x -= 110;
				m_VertexData[3].p.x -= 110;

				
			}
			m_dxHelper.m_pContext->UpdateSubresource(m_dxHelper.m_pVertexBuffer, 0, nullptr, &m_VertexData.at(0), 0, 0);
			m_dxHelper.PostRender();
		}
		

	
	return true;
}

//
//void    Bullet::SetMatrix(D3DXMATRIX* matWorld,
//	D3DXMATRIX* matView,
//	D3DXMATRIX* matProj)
//{
//
//	if (matWorld != nullptr)
//	{
//		m_matWorld = *matWorld;
//	}
//	if (matView != nullptr)
//	{
//		m_matView = *matView;
//	}
//	if (matProj != nullptr)
//	{
//		m_matProj = *matProj;
//	}
//
//	if (JH_Player::b_Left)
//	{
//		m_matWorld._11 *= -1;
//	}
//	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
//	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
//	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
//
//	D3DXMatrixIdentity(&m_matWorld);
//	m_cbData.d.x = cosf(g_fProgramTime) *0.5f + 0.5f;
//	D3D11_MAPPED_SUBRESOURCE mss;
//	if (SUCCEEDED(m_dxHelper.m_pContext->Map(
//		m_dxHelper.m_pConstantBuffer, 0,
//		D3D11_MAP_WRITE_DISCARD,
//		0, &mss)))
//	{
//		CB_DATA* pData = (CB_DATA*)mss.pData;
//		memcpy(pData, &m_cbData, sizeof(CB_DATA));
//		m_dxHelper.m_pContext->Unmap(m_dxHelper.m_pConstantBuffer, 0);
//	}
//
//}
JH_Bullet::JH_Bullet()
{
	m_fRetentiontime=0.0f;
	m_BulletUVList.resize(SHOTCOUNT);
	m_BulletCount = 0;
	Key_State = KEY_FREE;
	m_Count = 0;
	
	m_BulletState = 0;
	m_Direct = 0;
	m_BulletPos = D3DXVECTOR3(0.0, 0.0, 0.0);
}


JH_Bullet::~JH_Bullet()
{
}
