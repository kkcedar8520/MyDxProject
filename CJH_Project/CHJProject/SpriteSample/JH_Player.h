#pragma once
#include"JH_Sprite.h"
enum PlayerState
{
	STAND = 0,
	RIGHTRUN,
	LEFTRUN,
	JUMP,
	CHARGE,
	BE_ATTACKED,
	DEAD,
	COUNT,
};
class JH_Player:public JH_Sprite
{
public:
	DWORD	m_PlayerState;
	vector<JrtLits> m_PlayerMotionList;
public:
	void SetArrayRect(vector<RECT>& rtList, int width, int height, float fAnimaTime);
public:
	bool Init();
public:
	JH_Player();
	virtual ~JH_Player();
};

