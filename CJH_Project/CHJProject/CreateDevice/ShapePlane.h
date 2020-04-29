#pragma once
#include"JH_DXStd.h"
#include"Device.h"
#include"jMath.h"

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
class ShapePlane
{
public:
	Matrix	m_matWorld;
	Matrix	m_matView;
	Matrix	m_matProj;
public:
	ID3D11Device*	m_pd3dDevice;
	ID3D11DeviceContext*	m_pd3dDeviceContext;
public:
	std::vector<PCT_VERTEX> m_VertexData;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11Buffer*			m_pIndexBuffer;
	ID3D11Buffer*			m_pConstantBuffer;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVs;
	ID3D11ShaderResourceView*	m_pSRVa;
	ID3D11ShaderResourceView*	m_pSRVb;
	ID3D11PixelShader*		m_pPSBlend;
	ID3D11PixelShader*		m_pPs;
	std::vector<DWORD>		m_IndexData;
	CB_DATA			m_cbData;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool	Create(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,const TCHAR* pszFileName);
	HRESULT	CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture(const TCHAR* pszFileName);
	HRESULT LoadShaderInputLayout();
	bool SetMatrix(Matrix*matWorld,Matrix*matView,Matrix*matProj);
	
public:
	ShapePlane();
	virtual ~ShapePlane();
};

