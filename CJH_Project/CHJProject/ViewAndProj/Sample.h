#pragma once
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
class Sample : public JHDXCore
{
public:
	Matrix m_matView;
	Matrix m_matProj;
	Matrix m_matOrthoProj;
	Vector3 m_vPos;
	Vector3 m_vAt;
	Vector3 m_vUp;
public:
	JH_ShapePlane m_planeObj;


	ID3D11SamplerState*  m_pSamplerState;
	ID3D11BlendState* m_pAlpahBlend;
	ID3D11BlendState* m_pAlpahBlendDisable;
	ID3D11RasterizerState* m_pRSWireFrame;
	ID3D11RasterizerState* m_pRSSold;
	ID3D11DepthStencilState* m_pDSS;
	ID3D11DepthStencilState* m_pDSSDisable;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	SetViewProj();
public:
	Sample();
	virtual ~Sample();
};