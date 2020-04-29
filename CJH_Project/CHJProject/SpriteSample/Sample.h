#pragma once
#include"JH_DXStd.h"
#include"JHDXCore.h"
#include"JH_Sprite.h"
#include"JH_Input.h"
class Sample: public JHDXCore
{
public:
	
	D3DXMATRIX	m_matWorld;
	D3DXVECTOR3 m_PlayerPos;
public:
	shared_ptr<JH_ShapePlane> m_map;
	shared_ptr<JH_Sprite> m_Player;
	vector<RECT>	m_rtList;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	Sample();
	virtual ~Sample();
};

