#pragma once
#include"HCore.h"
#include"JHSound.h"
class Sample:public HCore
{
public:
	JHSound m_Sound;
	int		m_iBackGroundMusic;
	int		m_iEffect;
	HCore game;
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
public:
	Sample();
	~Sample();
};

