#include "JH_Player.h"

bool JH_Player::Init()
{

	m_PlayerMotionList.resize(8);
	m_PlayerMotionList[LEFTSTAND].resize(1);
	m_PlayerMotionList[RIGHTSTAND].resize(1);
	m_PlayerMotionList[LEFTRUN].resize(10);
	m_PlayerMotionList[RIGHTRUN].resize(10);
	m_PlayerMotionList[JUMP].resize(9);
	m_PlayerMotionList[BE_ATTACKED].resize(4);
	m_PlayerMotionList[BE_ATTACKED2].resize(7);
	m_PlayerMotionList[DEAD].resize(4);

	m_PlayerMotionList[0][0] = { 10,490, 63, 52 };//left stand
	m_PlayerMotionList[1][0] = { 10,490, 63, 52 };// stand

	m_PlayerMotionList[2][0] = { 76,490,63,52 };
	m_PlayerMotionList[2][1] = { 139,490,63,52 };
	m_PlayerMotionList[2][2] = { 203,490,63,52 };
	m_PlayerMotionList[2][3] = { 276,490,63,52 }; //RUN SHOT
	m_PlayerMotionList[2][4] = { 343,490,63,52 };
	m_PlayerMotionList[2][5] = { 404,490,63,52 };
	m_PlayerMotionList[2][6] = { 462,490,63,52 };
	m_PlayerMotionList[2][7] = { 521,490,63,52 };
	m_PlayerMotionList[2][8] = { 583,490,63,52 };
	m_PlayerMotionList[2][9] = { 651,490,63,52 };

	m_PlayerMotionList[3][0] = { 76,490,63,52 };
	m_PlayerMotionList[3][1] = { 139,490,63,52 };
	m_PlayerMotionList[3][2] = { 203,490,63,52 };
	m_PlayerMotionList[3][3] = { 276,490,63,52 }; //RUN SHOT
	m_PlayerMotionList[3][4] = { 343,490,63,52 };
	m_PlayerMotionList[3][5] = { 404,490,63,52 };
	m_PlayerMotionList[3][6] = { 462,490,63,52 };
	m_PlayerMotionList[3][7] = { 521,490,63,52 };
	m_PlayerMotionList[3][8] = { 583,490,63,52 };
	m_PlayerMotionList[3][9] = { 651,490,63,52 };

	m_PlayerMotionList[4][0] = { 7,203,41,42 };
	m_PlayerMotionList[4][1] = { 55,204,41,42 };
	m_PlayerMotionList[4][2] = { 108,198,41,51 };
	m_PlayerMotionList[4][3] = { 168,195,41,51 };//JUMP  up
	m_PlayerMotionList[4][4] = { 12,314,53,56 }; //shot motion
	m_PlayerMotionList[4][5] = { 168,195,41,51 };
	m_PlayerMotionList[4][6] = { 310,726,47,54 }; //down
	m_PlayerMotionList[4][7] = { 360,728,40,46 };
	m_PlayerMotionList[4][8] = { 10,490, 63, 52 };

	m_PlayerMotionList[5][0] = { 15,607,57,45 };
	m_PlayerMotionList[5][1] = { 148,606,54,42 };
	m_PlayerMotionList[5][2] = { 80,609,54,42 }; //피격1
	m_PlayerMotionList[5][3] = { 213,604,54,42 };

	m_PlayerMotionList[6][0] = { 8,670,49,42 };
	m_PlayerMotionList[6][1] = { 67,669,49,42 };
	m_PlayerMotionList[6][2] = { 197,849,49,42 };
	m_PlayerMotionList[6][3] = { 264,847,49,42 }; //피격 2
	m_PlayerMotionList[6][4] = { 324,850,49,42 };
	m_PlayerMotionList[6][5] = { 130,667,63,42 };
	m_PlayerMotionList[6][6] = { 207,678,63,29 };

	m_PlayerMotionList[7][0] = { 132,52,46,25 };
	m_PlayerMotionList[7][1] = { 80,49,46,28 }; // 사망
	m_PlayerMotionList[7][2] = { 41,36,30,42 };
	m_PlayerMotionList[7][3] = { 10,12,30,69 };
	return true;
}

void JH_Player::SetArrayRect(vector<RECT>& rtList, int width, int height, float fAnimaTime)
{

	m_iNumSpriteIndex = rtList.size();


	for (int rtN = 0; rtN < m_iNumSpriteIndex; rtN++)
	{
		JRECT rt;

		rt.uv[0].x = rtList[rtN].left / (float)width;
		rt.uv[0].y = rtList[rtN].top / (float)height;
		rt.uv[1].x = (rtList[rtN].left + rtList[rtN].right) / (float)width;
		rt.uv[1].y = rtList[rtN].top / (float)height;
		rt.uv[2].x = rtList[rtN].left / (float)width;
		rt.uv[2].y = (rtList[rtN].top + rtList[rtN].bottom) / (float)height;
		rt.uv[3].x = (float)rt.uv[1].x;
		rt.uv[3].y = (float)rt.uv[2].y;

		m_PlayerMotionList[m_PlayerState].push_back(rt);
	}
	m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
}
JH_Player::JH_Player()
{
	m_PlayerState = STAND;
}


JH_Player::~JH_Player()
{
}
