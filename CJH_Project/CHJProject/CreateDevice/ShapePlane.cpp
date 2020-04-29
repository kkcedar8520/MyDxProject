#include "ShapePlane.h"


bool ShapePlane::SetMatrix(Matrix*matWorld, Matrix*matView, Matrix*matProj)// 매트릭스 세팅
{
	if (matWorld!=nullptr)
	{
		m_matWorld = *matWorld;
	}
	if (matView != nullptr)
	{
		m_matView = *matView;
	}
	if (matProj != nullptr)
	{
		m_matProj = *matProj;
	}
	m_cbData.d.x = g_fProgramTime;
	Matrix  matTrans;

	m_matWorld.Transpose();
	m_matView.Transpose();
	m_matProj.Transpose();//전치

	m_cbData.matWorld = m_matWorld;
	m_cbData.matView = m_matView;
	m_cbData.matProj = m_matProj;

	D3D11_MAPPED_SUBRESOURCE mss;
	if (SUCCEEDED(m_pd3dDeviceContext->Map(m_pConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &mss)))
	{
		CB_DATA* pData = (CB_DATA*)mss.pData;
		memcpy(pData, &m_cbData, sizeof(CB_DATA));
		m_pd3dDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	return true;
}
bool ShapePlane::Init()
{
	
	return true;
}
bool ShapePlane::Frame()
{
	
	return true;
}

bool ShapePlane::Render()
{
	UINT stride = sizeof(PCT_VERTEX);
	UINT offset = 0;

	m_pd3dDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pd3dDeviceContext->VSSetShader(m_pVs, NULL, 0);
	m_pd3dDeviceContext->PSSetShader(m_pPSBlend, NULL, 0);

	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->DrawIndexed(6, 0,0);




	return true;
}
bool ShapePlane::Release()
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
	m_pConstantBuffer->Release();
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
	m_VertexData[0].p = Vector3(-1.0f, 1.0f, 0.5f);
	m_VertexData[1].p = Vector3(1.0f, 1.0f, 0.5f);
	m_VertexData[2].p = Vector3(-1.0f, -1.0f, 0.5f);
	m_VertexData[3].p = Vector3(1.0f, -1.0f, 0.5f);
	m_VertexData[0].c = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexData[1].c = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexData[2].c = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexData[3].c = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexData[0].t = Vector2(0.0f, 0.0f);
	m_VertexData[1].t = Vector2(1.0f, 0.0f);
	m_VertexData[2].t = Vector2(0.0f, 1.0f);
	m_VertexData[3].t = Vector2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;//버퍼속성
	D3D11_SUBRESOURCE_DATA sd;//실제데이터
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DEFAULT;//용법
	bd.ByteWidth = sizeof(PC_VERTEX)* m_VertexData.size();//데이터크기
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	sd.pSysMem = &m_VertexData.at(0);//데이터 등록

	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);//버퍼생성
	return	hr;
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
HRESULT ShapePlane::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	ZeroMemory(&m_cbData, sizeof(CB_DATA));
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(CB_DATA);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_cbData;
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer);
	return hr;
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


	if (FAILED(hr = D3DX11CompileFromFile(L"pixelshader.hlsl",
		NULL,
		NULL,
		"PSBlend",// pEntrypoint,
		"ps_5_0",
		0,
		0,
		NULL,
		&pPixelCode,
		&pErrorMsg, NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsg->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
	m_pd3dDevice->CreatePixelShader(
		pPixelCode->GetBufferPointer(),
		pPixelCode->GetBufferSize(),
		NULL,
		&m_pPSBlend);

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
	if (FAILED(CreateConstantBuffer()))
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

	//hr = D3DX11CreateShaderResourceViewFromFile(
	//	m_pd3dDevice,
	//	L"../../data/bitmap/start.bmp",
	//	NULL,
	//	NULL,
	//	&m_pSRVb,
	//	NULL);
	return hr;
}
ShapePlane::ShapePlane()
{
}


ShapePlane::~ShapePlane()
{
}
