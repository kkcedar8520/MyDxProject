
#pragma once
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"
#include"LightMgr.h"
class Sample :public JHDXCore
{
public:
	JH_ShapeLine m_DebugLine;



	JH_Map m_Map;
public:
	

public:

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

