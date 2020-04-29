#pragma once
#include"JH_Std.h"
#include"JHActor.h"
#include<Windows.h>
#include"JHMapObj.h"
#include"SpriteObj.h"

enum State
{
	LEFTSTAND,
	RIGHTSTAND,
	LEFTRUN,
	RIGHTRUN,
	JUMP,
	BE_ATTACKED,
	BE_ATTACKED2,
	DEAD,
	PCOUNT,
};

typedef std::vector<RECT> RTList;
class Player :public JHObject
{
public:
	HBITMAP m_StrechBitmap;
	HBITMAP m_StrechMaskBitmap;
	HDC m_StrechDC;
	HDC m_StrechMaskDC;
	JHMapObj m_GustStage;
	int m_JSpriteIndex;
	int m_RSpriteIndex;
	int m_LSpriteIndex;
	int m_iSpriteIndex;

	bool b_Left;
	bool b_Jumping;
	bool b_Right;
	
	float   m_fTimer;
	float	m_HoldFrame;
	bool    m_bFinish;
	float	m_fSpeed;
	float	m_aSpeed;
	float	m_bSpeed;
	float   m_fSecond;
	DWORD	m_dwPlayerSate;
	float	m_Jump;
public:
	DWORD &GetState()
	{
		return m_dwPlayerSate;
	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	Player()
	{
		m_fSecond = 0.0f;
		m_aSpeed = 150;
		m_fSpeed = 500.0f;
		m_HoldFrame=0.003;
		b_Left=0;
		b_Jumping=0;
		b_Right=0;
		m_iSpriteIndex=0;
		m_JSpriteIndex=0;
		m_fTimer = 0.0f;
		m_fOffsetTime = 1.0f;
		m_bFinish = true;
		m_Jump = 0;
	};
	virtual ~Player() {};
};

