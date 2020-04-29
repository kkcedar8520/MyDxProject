#include "ShapePlane.h"

bool ShapePlane::Init()
{
	
	return true;
}
bool ShapePlane::Frame()
{
	return true;
}

bool ShapePlane::Release()
{
	m_pVertexBuffer->Release();
	m_pVertexLayout->Release();
	m_pSRVa->Release();
	m_pSRVb->Release();
	m_pVs->Release();
	m_pPs->Release();
	return true;
}
HRESULT	ShapePlane::CreateVertexBuffer()//버텍스버퍼 생성
{
	HRESULT	hr = S_OK;

	m_VertexData.resize(4);

	m_VertexData[0].x = -1.0f; m_VertexData[0].y = 1.0f;
	m_VertexData[0].z = 0.0f;
	m_VertexData[0].r = 0.0f;
	m_VertexData[0].g = 1.0f;
	m_VertexData[0].b = 0.0f;
	m_VertexData[0].a = 1.0f;
	m_VertexData[0].u = 0.0f;
	m_VertexData[0].v = 0.0f;


	m_VertexData[1].x = 1.0f; m_VertexData[1].y = 1.0f;
	m_VertexData[1].z = 0.0f;
	m_VertexData[1].r = 0.0f;
	m_VertexData[1].g = 0.0f;
	m_VertexData[1].b = 0.0f;
	m_VertexData[1].a = 1.0f;
	m_VertexData[1].u = 1.0f;
	m_VertexData[1].v = 0.0f;

	m_VertexData[2].x = -1.0f; m_VertexData[2].y = -1.0f;
	m_VertexData[2].z = 0.0f;
	m_VertexData[2].r = 1.0f;
	m_VertexData[2].g = 0.0f;
	m_VertexData[2].b = 0.0f;
	m_VertexData[2].a = 1.0f;
	m_VertexData[2].u = 0.0f;
	m_VertexData[2].v = 1.0f;

	m_VertexData[3].x = 1.0f; m_VertexData[3].y = -1.0f;
	m_VertexData[3].z = 0.0f;
	m_VertexData[3].r = 0.0f;
	m_VertexData[3].g = 0.0f;
	m_VertexData[3].b = 1.0f;
	m_VertexData[3].a = 1.0f;
	m_VertexData[3].u = 1.0f;
	m_VertexData[3].v = 1.0f;

	D3D11_BUFFER_DESC bd;//버퍼속성
	D3D11_SUBRESOURCE_DATA sd;//실제데이터
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DEFAULT;//용법
	bd.ByteWidth = sizeof(PCTVERTEX)* m_VertexData.size();//데이터크기
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	sd.pSysMem = &m_VertexData.at(0);//데이터 등록

	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);//버퍼생성
	return	hr;
}
HRESULT ShapePlane::LoadShaderInputLayout()
{
	HRESULT hr=S_OK;
	
	ID3DBlob*	pVertexCode;
	ID3DBlob*	pPixelCode;
	  
		

	ID3DBlob*	pErrorMsg;
	if (FAILED(hr = D3DX11CompileFromFile(L"vertexshader.hlsl",
		NULL,
		NULL,
		"VS",// pEntrypoint,
		"vs_5_0",
		0,
		0,
		NULL,
		&pVertexCode,
		&pErrorMsg,
		NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsg->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
	m_pd3dDevice->CreateVertexShader(
		pVertexCode->GetBufferPointer(),
		pVertexCode->GetBufferSize(),
		NULL,
		&m_pVs
	);
	if (FAILED(hr = D3DX11CompileFromFile(L"PixelShader.hlsl",
		NULL,
		NULL,
		"PS",// pEntrypoint,
		"ps_5_0",
		0,
		0,
		NULL,
		&pPixelCode,
		&pErrorMsg,
		NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsg->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
	m_pd3dDevice->CreatePixelShader(
		pPixelCode->GetBufferPointer(),
		pPixelCode->GetBufferSize(),
		NULL,
		&m_pPs
	);
	if (FAILED(hr = D3DX11CompileFromFile(L"PixelShader.hlsl",
		NULL,
		NULL,
		"PS_Blend",// pEntrypoint,
		"ps_5_0",
		0,
		0,
		NULL,
		&pPixelCode,
		&pErrorMsg,
		NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsg->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
	m_pd3dDevice->CreatePixelShader(
		pPixelCode->GetBufferPointer(),
		pPixelCode->GetBufferSize(),
		NULL,
		&m_PSBlend
	);


	const D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEX",0,DXGI_FORMAT_R32G32_FLOAT,0,28,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT iLayoutCount = sizeof(layout) / sizeof(layout[0]);

	m_pd3dDevice->CreateInputLayout(
		layout,
		iLayoutCount,
		pVertexCode->GetBufferPointer(),
		pVertexCode->GetBufferSize(),
		&m_pVertexLayout
	);
	
	return hr;
}
bool ShapePlane::Render()
{
	UINT stride = sizeof(PCTVERTEX);
	UINT offset = 0;

	m_pd3dDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pd3dDeviceContext->VSSetShader(m_pVs, NULL, 0);
	m_pd3dDeviceContext->PSSetShader(m_pPs, NULL, 0);

	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->DrawIndexed(6, 0, 0);




	return true;
}

bool  ShapePlane::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,const TCHAR* pszFileName)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pContext;
	if (FAILED(CreateVertexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		return false;
	}
	if (FAILED(LoadShaderInputLayout()))
	{
		return false;
	}
	if (FAILED(LoadTexture(pszFileName)));
	{
		return false;
	}
	return true;
}
HRESULT ShapePlane::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	m_IndexData.resize(6);

	m_IndexData[0] = 0;
	m_IndexData[1] = 1;
	m_IndexData[2] = 2;
	m_IndexData[3] = 2;
	m_IndexData[4] = 1;
	m_IndexData[5] = 3;


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD)* m_IndexData.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_IndexData.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	return hr;
}
HRESULT ShapePlane::LoadTexture(const TCHAR* pszFileName)
{
	HRESULT hr = S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_pd3dDevice,
		pszFileName,
		NULL,
		NULL,
		&m_pSRVa,
		NULL);

	hr = D3DX11CreateShaderResourceViewFromFile(
		m_pd3dDevice,
		L"../../data/bitmap/bitmap1mask.bmp",
		NULL,
		NULL,
		&m_pSRVb,
		NULL);
	return hr;
}
ShapePlane::ShapePlane()
{
}


ShapePlane::~ShapePlane()
{
}
