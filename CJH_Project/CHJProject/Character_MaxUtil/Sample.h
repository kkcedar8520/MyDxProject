#pragma once
#include"JHDXCore.h"
#include"BoneObj.h"
#include"SkinObj.h"
#include"JH_ShapeLine.h"
class Sample :public JHDXCore
{
public:
	vector<JH_Model*> m_ObjList;
	SkinObj	m_MaxSkin;
	BoneObj	m_MaxBone;
	JH_ShapeLine m_DebigLine;

public:

public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	Sample();
	virtual ~Sample();
};

