#pragma once
#include"JHBitMap.h"
#include"JH_Std.h"
#include"HCore.h"
#include<time.h>
class BMSample:public HCore
{
public:
	JHBitMap m_Map;
	JHBitMap m_Boom;
	JHBitMap m_Player;
	HCore game;
	float m_fX_POSI;
	float m_fY_POSI;
public:
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
	BMSample();
	~BMSample();
};


