#include "Sample.h"


bool 	Sample::Init()
{
	Create();
	m_cbData.matView.Identity();
	m_cbData.matProj.Identity();
	m_cbData.matProj.Identity();
	D3D11_BLEND_DESC bs;
	ZeroMemory(&bs, sizeof(D3D11_BLEND_DESC));


	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	m_pd3dDevice->CreateRasterizerState(&rd, &m_pSolid);

	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
	// Z 버퍼 비교 활성화
	dsd.DepthEnable = TRUE;
	// z값 버퍼에 저장
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	// 비교 연산
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	m_pd3dDevice->CreateDepthStencilState(&dsd, &m_pDSS);


	m_pImmediateContext->RSSetState(m_pSolid);
	m_pImmediateContext->OMSetDepthStencilState(m_pDSS,0);
	return true;

}
bool 	Sample::Frame()
{
	m_cbData.d.x = g_fProgramTime;
	float fAngle = cos(g_fProgramTime) * 0.5f + 0.5f;
	Matrix  matTrans;

	matTrans.Translation(cos(g_fProgramTime), 0, 0);
	matTrans.Transpose();
	m_cbData.matWorld = matTrans;

	
	D3D11_MAPPED_SUBRESOURCE mss;
	if (SUCCEEDED(m_pImmediateContext->Map(m_pConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &mss)))
	{
		CB_DATA* pData = (CB_DATA*)mss.pData;
		memcpy(pData, &m_cbData, sizeof(CB_DATA));
		m_pImmediateContext->Unmap(m_pConstantBuffer, 0);
	}
	return true;
}
bool 	Sample::Render()
{
	UINT stride = sizeof(PC_VERTEX);
	UINT offset = 0;

	m_pImmediateContext->IASetInputLayout(m_pVertexLayOut);
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_pImmediateContext->PSSetShader(m_pPs, NULL, 0);
	m_pImmediateContext->VSSetShader(m_pVs, NULL, 0);
	
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->DrawIndexed(6,0,0);
	return true;
}
bool 	Sample::Release()
{
	m_pVertexBuffer->Release();
	m_pVertexLayOut->Release();
	m_pVs->Release();
	m_pPs->Release();
	return true;
}
HRESULT	Sample::Create()
{
	HRESULT hr=S_OK;
	if (FAILED(CreateVertexBuffer()))
	{
		return hr;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		return hr;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return hr;
	}
	if (FAILED(LoadShaderAndInputLayout()))
	{
		return hr;
	}
	return hr;
}
HRESULT Sample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	
	m_VertexData.resize(4);
	m_VertexData[0].p = Vector3(-1.0f, 1.0f, 0.5f);
	m_VertexData[1].p = Vector3(1.0f, 1.0f, 0.5f);
	m_VertexData[2].p = Vector3(-1.0f, -1.0f, 0.5f);
	m_VertexData[3].p = Vector3(1.0f, -1.0f, 0.5f);
	m_VertexData[0].c = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexData[1].c = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexData[2].c = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexData[3].c = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(PC_VERTEX)*m_VertexData.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexData.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	return hr;
}
HRESULT Sample::CreateIndexBuffer() 
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
HRESULT Sample::CreateConstantBuffer() 
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
HRESULT Sample::LoadShaderAndInputLayout()
{
	HRESULT hr = S_OK;


	ID3DBlob*	pVertexCode;
	ID3DBlob*	pPixelCode;
	ID3DBlob*	pErrorMsg;

	if (FAILED(hr = D3DX11CompileFromFile(
		L"VertexShader.hlsl",
		NULL,
		NULL,
		"VS",
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

	hr = m_pd3dDevice->CreateVertexShader(pVertexCode->GetBufferPointer(), pVertexCode->GetBufferSize(),
		NULL, &m_pVs);

	if (FAILED(hr = D3DX11CompileFromFile(
		L"PixelShader.hlsl",
		NULL,
		NULL,
		"XXXX",
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

	hr = m_pd3dDevice->CreatePixelShader(pPixelCode->GetBufferPointer(), pPixelCode->GetBufferSize(),
		NULL, &m_pPs);

	const D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT iLayoutCount = sizeof(layout) / sizeof(layout[0]);

	m_pd3dDevice->CreateInputLayout(
		layout,
		iLayoutCount,
		pVertexCode->GetBufferPointer(),
		pVertexCode->GetBufferSize(),
		&m_pVertexLayOut
	);
	return hr;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,800,600 };
	if (!game.InitWindow(L"CreateIndexConstantBuffer", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}