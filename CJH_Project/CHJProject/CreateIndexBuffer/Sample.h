#pragma once
#include"JHDXCore.h"
#include"jMath.h"
#pragma warning( disable:4005 )
struct P_VERTEX
{
	Vector3 p;
};
struct PC_VERTEX
{
	Vector3 p;
	Vector4 c;
};
struct PCT_VERTEX
{
	Vector3 p;
	Vector4 c;
	Vector2 t;

};
struct CB_DATA
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
	Vector4	d;
};
class Sample:public JHDXCore 
{
	Vector3 m_vPos;
	Vector3	m_vTarget;
	Vector3	m_vUp;
public:
	Matrix	m_matView;
	Matrix	m_matProj;
	Matrix	m_matOrthoProj;
public:
	ID3D11Buffer*	m_pVertexBuffer;
	ID3D11Buffer*	m_pIndexBuffer;
	ID3D11Buffer*	m_pConstantBuffer;
	ID3D11InputLayout*	m_pVertexLayOut;
	ID3D11VertexShader*	m_pVs;
	ID3D11PixelShader*	m_pPs;
	ID3D11SamplerState*	m_pSamplerState;
	ID3D11RasterizerState*m_pSolid;
	ID3D11DepthStencilState*	m_pDSS;
	ID3D11ShaderResourceView*	m_pSRVA;
	ID3D11ShaderResourceView*	m_pSRVB;
	std::vector<PC_VERTEX>	m_VertexData;
	std::vector<DWORD>		m_IndexData;
	CB_DATA			m_cbData;
public:
	HRESULT	Create();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadShaderAndInputLayout();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

