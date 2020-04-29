#pragma once
#include"JH_Srcreen.h"

class CharacterSlectScreen:public ScreenState
{
public:
	void Process(JH_Model*User)override;
	JH_Sprite m_Characters;//1000 282
	JH_ShapePlane m_CSeletcbar;
	bool bRight;
	bool bLeft;
public:
	CharacterSlectScreen(JH_Srcreen* Owner) :ScreenState(Owner)
	{
	}
	virtual ~CharacterSlectScreen();
	bool Init();
	bool Render();
};

