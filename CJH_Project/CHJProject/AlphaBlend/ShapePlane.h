#pragma once
#include"JH_DXStd.h"
#include"Device.h"

struct PC_VERTEX
{
	float x, y, z;
	float r, g, b, a;
};
struct PCTVERTEX
{
	float x;
	float y;
	float z;

	float r, g, b, a;

	float u, v;
};
class ShapePlane
{
public:
	ID3D11Device*	m_pd3dDevice;
	ID3D11DeviceContext*	m_pd3dDeviceContext;
public:
	std::vector<PCTVERTEX> m_VertexData;
	std::vector<DWORD>		m_IndexData;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11Buffer*			m_pIndexBuffer;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVs;
	ID3D11ShaderResourceView*	m_pSRVa;
	ID3D11ShaderResourceView*	m_pSRVb;
	ID3D11PixelShader*		m_pPs;
	ID3D11PixelShader*		m_PSBlend;

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
	HRESULT LoadTexture(const TCHAR* pszFileName);
	HRESULT LoadShaderInputLayout();
public:
	ShapePlane();
	virtual ~ShapePlane();
};

