#pragma once
#include"JHDXCore.h"
#include"JH_DXStd.h"
#include"ShapePlane.h"
#include"JH_Input.h"
#pragma warning( disable:4005 )
class Sample:public JHDXCore
{
	Vector3 m_vPos;
	Vector3 m_vTarget;
	Vector3 m_vUp;
public:
	Matrix	m_matWorld;
	Matrix	m_matView;
	Matrix	m_matProj;
public:
	ID3D11BlendState*		m_pAlphaBlend;
	ID3D11RasterizerState* m_pRSWireFrame;
	ID3D11RasterizerState* m_pRSSold;
	ID3D11DepthStencilState* m_pDSS;

	ShapePlane	m_PlaneObj;
	ID3D11SamplerState*	m_pSamplerState;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void	SetViewProj();
public:

	Sample();
	virtual ~Sample();
};

