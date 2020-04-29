#pragma once
#include"JH_DXStd.h"
#include"JHDXCore.h"
#include"ShapePlane.h"
class Sample:public JHDXCore
{
public:
	ID3D11SamplerState*	m_pSamplerState;
	ShapePlane	m_PlaneObj;
	ID3D11BlendState*		m_pAlphaBlend;
	ID3D11BlendState*		m_pSrcAlphaBlend;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	Sample();
	virtual ~Sample();
};

