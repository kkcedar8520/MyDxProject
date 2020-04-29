#pragma once
#include "player.h"

bool Player::Init()
{
	
	JHObject::Init();
	
	m_StrechDC = CreateCompatibleDC(g_hScreenDC);

	m_dRtList.resize(8);
	m_dRtList[LEFTSTAND].resize(1);
	m_dRtList[RIGHTSTAND].resize(1);
	m_dRtList[LEFTRUN].resize(10);
	m_dRtList[RIGHTRUN].resize(10);
	m_dRtList[JUMP].resize(9);
	m_dRtList[BE_ATTACKED].resize(4);
	m_dRtList[BE_ATTACKED2].resize(7);
	m_dRtList[DEAD].resize(4);

	m_dRtList[0][0] = { 10,490, 63, 52 };//left stand
	m_dRtList[1][0] = { 10,490, 63, 52 };// stand

	m_dRtList[2][0] = { 76,490,63,52 };
	m_dRtList[2][1] = { 139,490,63,52 };
	m_dRtList[2][2] = { 203,490,63,52 };
	m_dRtList[2][3] = { 276,490,63,52 }; //RUN SHOT
	m_dRtList[2][4] = { 343,490,63,52 };
	m_dRtList[2][5] = { 404,490,63,52 };
	m_dRtList[2][6] = { 462,490,63,52 };
	m_dRtList[2][7] = { 521,490,63,52 };
	m_dRtList[2][8] = { 583,490,63,52 };
	m_dRtList[2][9] = { 651,490,63,52 };

	m_dRtList[3][0] = { 76,490,63,52 };
	m_dRtList[3][1] = { 139,490,63,52 };
	m_dRtList[3][2] = { 203,490,63,52 };
	m_dRtList[3][3] = { 276,490,63,52 }; //RUN SHOT
	m_dRtList[3][4] = { 343,490,63,52 };
	m_dRtList[3][5] = { 404,490,63,52 };
	m_dRtList[3][6] = { 462,490,63,52 };
	m_dRtList[3][7] = { 521,490,63,52 };
	m_dRtList[3][8] = { 583,490,63,52 };
	m_dRtList[3][9] = { 651,490,63,52 };

	m_dRtList[4][0] = { 7,203,41,42 };
	m_dRtList[4][1] = { 55,204,41,42 };
	m_dRtList[4][2] = { 108,198,41,51 };
	m_dRtList[4][3] = { 168,195,41,51 };//JUMP  up
	m_dRtList[4][4] = { 12,314,53,56 }; //shot motion
	m_dRtList[4][5] = { 168,195,41,51 };
	m_dRtList[4][6] = { 310,726,47,54 }; //down
	m_dRtList[4][7] = { 360,728,40,46 };
	m_dRtList[4][8] = { 10,490, 63, 52 };

	m_dRtList[5][0] = { 15,607,57,45 };
	m_dRtList[5][1] = { 148,606,54,42 };
	m_dRtList[5][2] = { 80,609,54,42 }; //피격1
	m_dRtList[5][3] = { 213,604,54,42 };

	m_dRtList[6][0] = { 8,670,49,42 };
	m_dRtList[6][1] = { 67,669,49,42 };
	m_dRtList[6][2] = { 197,849,49,42 };
	m_dRtList[6][3] = { 264,847,49,42 }; //피격 2
	m_dRtList[6][4] = { 324,850,49,42 };
	m_dRtList[6][5] = { 130,667,63,42 };
	m_dRtList[6][6] = { 207,678,63,29 };

	m_dRtList[7][0] = { 132,52,46,25 };
	m_dRtList[7][1] = { 80,49,46,28 }; // 사망
	m_dRtList[7][2] = { 41,36,30,42 };
	m_dRtList[7][3] = { 10,12,30,69 };

	

	m_fPosX =30;
	m_fPosY = 448;

	
	return true;
}
bool Player::Frame()
{

	if (G_Input.KeyCheck(VK_MENU))
	{
		b_Jumping = 1;
	}
	
	if (m_dwPlayerSate=LEFTRUN)
	{
		m_rtList = m_dRtList[LEFTSTAND];
	}
	if (m_dwPlayerSate = RIGHTRUN)
	{
		m_rtList = m_dRtList[RIGHTSTAND];
	}
		m_rtSrc = m_rtList[0];

	
	//m_dwPlayerSate = STAND;
	//m_rtList = m_dRtList[m_dwPlayerSate];
	//m_rtSrc = m_rtList[0];

		if (KEY_PUSH == G_Input.KeyCheck(VK_MENU))
		{
			m_dwPlayerSate = JUMP;
			SetRTList(m_dRtList[m_dwPlayerSate]);

			
			Set(m_rtList, 1.0f, true);

			if (m_iSpriteIndex < 4)
			{
				m_fPosY -= 400 * g_SecondPerFrame;
				m_Jump += 400 * g_SecondPerFrame;
			}
			if (m_iSpriteIndex >= 5)
			{
				m_fPosY += m_Jump / 4.0f;
			}
		}

	
	if (G_Input.KeyCheck(VK_LEFT))
	{
		if (b_Jumping!=1)
		{
			m_dwPlayerSate = LEFTRUN;
			SetRTList(m_dRtList[m_dwPlayerSate]);
			Set(m_rtList, 1.0f, false);
		}
		
		m_fPosX -= 100 * g_SecondPerFrame;
		if ( m_fPosX< 0)
		{
			m_fPosX = 0;
		}

	}

		
	 
		
		if (G_Input.KeyCheck(VK_RIGHT))
		{
			if (b_Jumping!=1)
			{
				m_dwPlayerSate = RIGHTRUN;
				SetRTList(m_dRtList[m_dwPlayerSate]);

				Set(m_rtList, 1.0f, false);
			}
			m_fPosX += 100 * g_SecondPerFrame;
			if (m_fPosX + m_rtSrc.right > 780)
			{
				m_fPosX -= (m_fPosX + m_rtSrc.right - 780);
			}
		 }
	

			

			

		if (b_Jumping)
			{
				m_fTimer += g_SecondPerFrame;
				if (m_fTimer >= m_fOffestTime)
				{
					m_fTimer -= m_fOffestTime;
					m_iSpriteIndex++;
				}
				if (m_iSpriteIndex > m_rtList.size())
				{
					m_Jump = 0;
					m_iSpriteIndex = 0;
					b_Jumping = 0;
					m_fTimer = 0;
					return true;
				}
				
				
				m_rtSrc = m_dRtList[JUMP][m_iSpriteIndex];
			}
		else
		{

				m_fTimer += g_SecondPerFrame;
				if (m_fTimer >= m_fOffestTime)
				{
					m_fTimer -= m_fOffestTime;
					m_iSpriteIndex++;
				}
			if (m_iSpriteIndex > m_rtList.size())
			{
				m_iSpriteIndex = 0;
				m_fTimer = 0;

			}
			m_rtSrc = m_rtList[m_iSpriteIndex];
		}
	return true;
}
bool Player::Render()
{
	
		GdiTransparentBlt(g_hOffScreenDC,
			m_fPosX,
			m_fPosY,
			m_rtSrc.right,
			m_rtSrc.bottom,

			m_BitMap->m_TempScreenDC,
			m_rtSrc.left,
			m_rtSrc.top,
			m_rtSrc.right,
			m_rtSrc.bottom,
			RGB(116, 116, 116)); // 소스

	if (b_Left)
	{
		GdiTransparentBlt(m_StrechDC,
			m_fPosX,
			m_fPosY,
			m_rtSrc.right,
			m_rtSrc.bottom,

			m_BitMap->m_TempScreenDC,
			m_rtSrc.left,
			m_rtSrc.top,
			m_rtSrc.right,
			m_rtSrc.bottom,
			RGB(116, 116, 116));

		StretchBlt(g_hOffScreenDC,
			m_fPosX + m_rtSrc.right,
			m_fPosY,
			-m_rtSrc.right,
			m_rtSrc.bottom,

			m_StrechDC,
			m_rtSrc.left,
			m_rtSrc.top,
			m_rtSrc.right,
			m_rtSrc.bottom,
			SRCCOPY);
		b_Left=0;
	}
	return true;
}
bool  Player::Release()
{
	ReleaseDC(g_hwnd
,m_StrechDC);
	JHObject::Release();
	return true;
}