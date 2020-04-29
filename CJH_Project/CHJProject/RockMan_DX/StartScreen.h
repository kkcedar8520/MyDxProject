#pragma once
#include"JH_Screen.h"


class StartScreen:public ScreenState
{
public:
	JH_ShapePlane m_Title;
	D3DXMATRIX	  m_matFinalWorld;
	bool bSet;


public:
	StartScreen(JH_Screen* Owner) :ScreenState(Owner)
	{
	

	}
	bool Init();
	bool Render();
	void Process(JH_Model* pUser);
	void MatrixSet(D3DXMATRIX& pMatview, D3DXMATRIX& pMatOrthoProj);
	virtual ~StartScreen();
};

