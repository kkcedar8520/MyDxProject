#include "JH_Player.h"
D3DXVECTOR3 JH_Player::g_PlayerPos(0, 0, 0.5f);
bool JH_Player::b_Left=false;
DWORD	JH_Player::m_PlayerState=STAND;

	bool JH_Player::Init()
	{
		m_Shot = make_shared<JH_Bullet>();
		m_Shot->Create(m_dxHelper.m_pd3dDevice, m_dxHelper.m_pContext,
			L"RockManShader.txt", L"../../data/bitmap/ROCKMAN2colorAlpha.bmp");
		m_Shot->Init();

		m_VectorList.resize(PLAYERCOUNT);
		m_VectorList[STAND].resize(1);
		m_VectorList[RUN].resize(10);
		m_VectorList[JUMP].resize(5);
		m_VectorList[BE_ATTACKED].resize(4);
		m_VectorList[BE_ATTACKED2].resize(7);
		m_VectorList[DEAD].resize(4);

		m_VectorList[STAND][0] = { 10,490, 63, 52 };//left stand


		m_VectorList[RUN][0] = { 76,490,63,52 };
		m_VectorList[RUN][1] = { 139,490,63,52 };
		m_VectorList[RUN][2] = { 203,490,63,52 };
		m_VectorList[RUN][3] = { 276,490,63,52 }; //RUN SHOT
		m_VectorList[RUN][4] = { 343,490,63,52 };
		m_VectorList[RUN][5] = { 404,490,63,52 };
		m_VectorList[RUN][6] = { 462,490,63,52 };
		m_VectorList[RUN][7] = { 521,490,63,52 };
		m_VectorList[RUN][8] = { 583,490,63,52 };
		m_VectorList[RUN][9] = { 651,490,63,52 };


		m_VectorList[JUMP][0] = { 7,203,41,42 };
		m_VectorList[JUMP][1] = { 55,204,41,42 };
		m_VectorList[JUMP][2] = { 108,198,41,51 };
		m_VectorList[JUMP][3] = { 168,195,41,51 };//JUMP  up
		m_VectorList[JUMP][4] = { 12,314,53,56 }; //shot motion
		//m_VectorList[JUMP][5] = { 168,195,41,51 };
		//m_VectorList[JUMP][6] = { 310,726,47,54 }; //down  /// 점프 맨위 스프라이트에서 짜르고 올라간위치만큼 순차적으로 내려오기
		//m_VectorList[JUMP][7] = { 360,728,40,46 };
		//m_VectorList[JUMP][8] = { 10,490, 63, 52 };
		
		
		m_VectorList[BE_ATTACKED][0] = { 15,607,57,45 };
		m_VectorList[BE_ATTACKED][1] = { 148,606,54,42 };
		m_VectorList[BE_ATTACKED][2] = { 80,609,54,42 }; //피격1
		m_VectorList[BE_ATTACKED][3] = { 213,604,54,42 };

		m_VectorList[BE_ATTACKED2][0] = { 8,670,49,42 };
		m_VectorList[BE_ATTACKED2][1] = { 67,669,49,42 };
		m_VectorList[BE_ATTACKED2][2] = { 197,849,49,42 };
		m_VectorList[BE_ATTACKED2][3] = { 264,847,49,42 }; //피격 2
		m_VectorList[BE_ATTACKED2][4] = { 324,850,49,42 };
		m_VectorList[BE_ATTACKED2][5] = { 130,667,63,42 };
		m_VectorList[BE_ATTACKED2][6] = { 207,678,63,29 };

		m_VectorList[DEAD][0] = { 132,52,46,25 };
		m_VectorList[DEAD][1] = { 80,49,46,28 }; // 사망
		m_VectorList[DEAD][2] = { 41,36,30,42 };
		m_VectorList[DEAD][3] = { 10,12,30,69 };


		SetArrayRect(m_VectorList, 788, 1108, 0.3f);
		g_PlayerPos = D3DXVECTOR3(-400, -240, 0.5f);
		m_matWorld._43 = g_PlayerPos.z;
		//Effect생성

		return true;
	}
	bool  JH_Player::Frame()
	{

	 //키값 받는곳
		d_RightRUNState = G_Input.KeyCheck(VK_RIGHT);
		d_LeftRUNState = G_Input.KeyCheck(VK_LEFT);
		
		
	

		if (G_Input.KeyCheck('S'))
		{
			b_Jumping = true;

		}
		if (d_RightRUNState)
		{
			b_Right = true;


			if (b_Left)
			{
				b_Left = 0;
		
			}
			
		}
		if (d_LeftRUNState)
		{
			b_Left = true;

	
			if (b_Right)
			{
				b_Right = 0;
		
			}
			
		}

		// 키값 우선순위 스테이트 선정

		if (d_RightRUNState || d_LeftRUNState)
		{
			m_PlayerState = RUN;
		}
		else
		{
			m_PlayerState = STAND;
		}
		if (b_Jumping)
		{
			m_PlayerState = JUMP;

		}
		if (b_Attacked)
		{
			m_PlayerState = BE_ATTACKED;
			b_Jumping = 0;
		}
		if (b_Dead)
		{
			m_PlayerState = DEAD;
			b_Jumping = 0;
		
		}

		//스테이트 변화 확인
		d_CurrentState = m_PlayerState;
		if (d_CurrentState != d_PastState)
		{
			m_iIndex = 0;
			m_fTimer = 0;
			m_fSecond = 0;
			m_fSpeed = 1000;
		}
		d_PastState = d_CurrentState;


	
		// 상태에 따른 움직임

		if (b_Jumping)
		{
			

			if (m_iIndex < m_VectorList[m_PlayerState].size() - 1)
			{

				m_fTimer += g_SecondPerFrame;
				if (m_fTimer > 0.5f / m_VectorList[m_PlayerState].size())
				{
					m_fTimer -= 0.5f / m_VectorList[m_PlayerState].size();
					m_iIndex++;
				}

			}

			m_fSpeed = m_fSpeed - (200 *9.8)*g_SecondPerFrame;
			g_PlayerPos.y += g_SecondPerFrame * m_fSpeed - (200 * 9.8 / 2)*g_SecondPerFrame*g_SecondPerFrame;
			
			if (d_LeftRUNState)
			{
				g_PlayerPos = g_PlayerPos + D3DXVECTOR3(-300.0f, 0, 0)* g_SecondPerFrame;
				if (g_PlayerPos.x - 63 < -600)
				{
					g_PlayerPos.x -= g_PlayerPos.x - 63 + 600;

				}
			}
			if(d_RightRUNState)
			{
				g_PlayerPos = g_PlayerPos + D3DXVECTOR3(300.0f, 0, 0)* g_SecondPerFrame;
				if (g_PlayerPos.x + 63 > 600)
				{
					g_PlayerPos.x -= g_PlayerPos.x + (63) - 600;

				}
			}


			if (g_PlayerPos.y < -240.0f)
			{
				g_PlayerPos.y = -240.0f;
				m_iIndex = 0;
				m_fTimer = 0;
				b_Jumping = 0;
				m_fSecond = 0;
				m_fSpeed = 1000;
				
			}
		}
		if (m_PlayerState==RUN)
		{
		
			if (b_Left)
			{
				g_PlayerPos = g_PlayerPos + D3DXVECTOR3(-300.0f, 0, 0)* g_SecondPerFrame;
				if (g_PlayerPos.x - 63 < -600)
				{
					g_PlayerPos.x -= g_PlayerPos.x - 63 + 600;
					
				}
			}
			else
			{
				g_PlayerPos = g_PlayerPos + D3DXVECTOR3(300.0f, 0, 0)* g_SecondPerFrame;
				if (g_PlayerPos.x + 63 > 600)
				{
					g_PlayerPos.x -= g_PlayerPos.x + (63) - 600;
					
				}
			}
				m_fTimer += g_SecondPerFrame;
				if (m_fTimer > 0.5f / m_VectorList[m_PlayerState].size())
				{
					m_fTimer -= 0.5f / m_VectorList[m_PlayerState].size();
					m_iIndex++;
				}
				if (m_iIndex >= m_VectorList[m_PlayerState].size())
				{
					m_iIndex = 0;
					m_fTimer = 0;
	
	
				}
				
		}
		if (m_PlayerState==BE_ATTACKED)
		{
			m_iIndex = 0;
			m_fTimer += g_SecondPerFrame;
			if (m_fTimer > 0.5f / m_VectorList[m_PlayerState].size())
			{
				m_fTimer -= 0.5f / m_VectorList[m_PlayerState].size();
				m_iIndex++;
			}
			if (m_iIndex >= m_VectorList[m_PlayerState].size())
			{
				m_iIndex = 0;
				m_fTimer = 0;
				m_PlayerState = STAND;

			}
			
		}

		if (b_Attacked == false && b_Dead == false)
		{
			// 총알 현재위치 세팅
			D3DXVECTOR3 CurrnetBulletPos(0, 0, 0);
			if (m_PlayerState == JUMP)
			{

				if (b_Left)
				{
					CurrnetBulletPos.x = g_PlayerPos.x - m_VectorList[m_PlayerState][m_iIndex].right;
					CurrnetBulletPos.y = g_PlayerPos.y + 80;
				}
				else
				{
					CurrnetBulletPos.x = g_PlayerPos.x + m_VectorList[m_PlayerState][m_iIndex].right;
					CurrnetBulletPos.y = g_PlayerPos.y + 80;
				}
			}
			else
			{

				if (b_Left)
				{
					CurrnetBulletPos.x = g_PlayerPos.x - m_VectorList[m_PlayerState][m_iIndex].right;
					CurrnetBulletPos.y = g_PlayerPos.y + 60;
				}
				else
				{
					CurrnetBulletPos.x = g_PlayerPos.x + m_VectorList[m_PlayerState][m_iIndex].right;
					CurrnetBulletPos.y = g_PlayerPos.y + 60;
				}
			}
			// 총알정보 셋팅
			m_Shot->SetInform(b_Left, CurrnetBulletPos);

			m_Shot->Frame();
		}

		return true;

	}

	bool JH_Player::SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime)
	{



		for (int i = 0; i < PLAYERCOUNT; i++)
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


				m_PlayerMotionList[i].push_back(rt);
			}
			m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
		}
		return true;
	}
	bool JH_Player::PostRender()
	{

			m_VertexData[0].t = m_PlayerMotionList[m_PlayerState][m_iIndex].uv[0];
			m_VertexData[1].t = m_PlayerMotionList[m_PlayerState][m_iIndex].uv[1];
			m_VertexData[2].t = m_PlayerMotionList[m_PlayerState][m_iIndex].uv[2];
			m_VertexData[3].t = m_PlayerMotionList[m_PlayerState][m_iIndex].uv[3];

			m_VertexData[0].p.x = g_PlayerPos.x - m_VectorList[m_PlayerState][m_iIndex].right;
			m_VertexData[0].p.y = g_PlayerPos.y + m_VectorList[m_PlayerState][m_iIndex].bottom * 2;
			m_VertexData[1].p.x = g_PlayerPos.x + m_VectorList[m_PlayerState][m_iIndex].right;
			m_VertexData[1].p.y = g_PlayerPos.y + m_VectorList[m_PlayerState][m_iIndex].bottom * 2;
			m_VertexData[2].p.x = g_PlayerPos.x - m_VectorList[m_PlayerState][m_iIndex].right;
			m_VertexData[2].p.y = g_PlayerPos.y;
			m_VertexData[3].p.x = g_PlayerPos.x + m_VectorList[m_PlayerState][m_iIndex].right;
			m_VertexData[3].p.y = g_PlayerPos.y;

			
			if (b_Left)
			{
				D3DXVECTOR3 temp;
				temp.x = m_VertexData[0].p.x;
				m_VertexData[0].p.x = m_VertexData[1].p.x;
				m_VertexData[1].p.x = temp.x;
				m_VertexData[2].p.x = m_VertexData[0].p.x;
				m_VertexData[3].p.x = m_VertexData[1].p.x;
			}
		
			m_dxHelper.m_pContext->UpdateSubresource(m_dxHelper.m_pVertexBuffer, 0, nullptr, &m_VertexData.at(0), 0, 0);
		
	
		m_dxHelper.PostRender();
		m_Shot->Render();
		return true;
	}
	JH_Player::JH_Player()
	{
		m_PlayerMotionList.resize(PLAYERCOUNT);
		m_fSecond = 0;
		m_fSpeed = 1000;
		m_JSpriteIndex = 0;
		m_iIndex = 0;
		m_vInterval = D3DXVECTOR3(0.0, 0.0, 0.0);;
		b_Jumping = 0;
		b_Right = 0;
		b_Stand=0;
		b_Attacked=0;
		b_Dead=0;
		m_fTimer = 0;
		d_StandState=0;
		d_LeftRUNState=0;
		d_RightRUNState=0;
		d_CurrentState=0;
		d_PastState=0;
	}

	//void    JH_Player::SetMatrix(D3DXMATRIX* matWorld,
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
	JH_Player::~JH_Player()
	{
		m_Shot->Release();
	}
