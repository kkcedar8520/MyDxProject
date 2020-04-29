#pragma once
#include"JH_Srcreen.h"


class StartScreen:public ScreenState
{
public:
	JH_ShapePlane m_Title;
	D3DXMATRIX	  m_matFinalWorld;
	bool bSet;


public:
	StartScreen(JH_Srcreen* Owner) :ScreenState(Owner)
	{
	

	}
	bool Init();
	bool Render();
	void Process(JH_Model* pUser);
	void MatrixSet(D3DXMATRIX& pMatview, D3DXMATRIX& pMatOrthoProj);
	virtual ~StartScreen();
};

