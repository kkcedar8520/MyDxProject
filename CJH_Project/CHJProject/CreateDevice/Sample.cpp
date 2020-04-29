#include "Sample.h"

void	Sample::SetViewProj()
{
	m_vPos=Vector3(0.0f, 0.0f, 5.0f);
	m_vTarget= Vector3(0.0f, 0.0f, 0.0f);
	m_vUp= Vector3(0.0f, 1.0f, 0.0f);
	m_matView.CreateViewLookAt(m_vPos, m_vTarget, m_vUp);
	
	float fnear = 1.0f;
	float fFar = 500.0f;
	float fFovY = X_PI * 0.5f;
	float fAspect = g_rtClient.right / g_rtClient.bottom;
	m_matProj.CreatePerspectiveFovLH(fnear, fFar, fFovY, fAspect);

}
bool Sample::Init() 
{
	HRESULT hr;
	D3D11_SAMPLER_DESC	descSample; //텍스쳐를 정규화시키기 위한 과정
	ZeroMemory(&descSample, sizeof(D3D11_SAMPLER_DESC));
	descSample.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSample.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	descSample.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	descSample.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	hr = m_pd3dDevice->CreateSamplerState(&descSample, &m_pSamplerState);

	D3D11_BLEND_DESC bs;
	ZeroMemory(&bs, sizeof(D3D11_BLEND_DESC));
	//bs.AlphaToCoverageEnable;
	bs.IndependentBlendEnable = TRUE;;
	bs.RenderTarget[0].BlendEnable = TRUE;
	// FINALE COLOR = SRCCOLOR* SRCALPHA + 
	//                DESKCOLOR* InvSRCALPHA; 
	bs.RenderTarget[0].SrcBlend =
		D3D11_BLEND_SRC_ALPHA;
	bs.RenderTarget[0].DestBlend =
		D3D11_BLEND_INV_SRC_ALPHA;
	bs.RenderTarget[0].BlendOp =
		D3D11_BLEND_OP_ADD;
	// FINALE ALPHA = SRCALPHA* 1 + 
	//                DESKALPHA* 0; 
	bs.RenderTarget[0].SrcBlendAlpha =
		D3D11_BLEND_ONE;
	bs.RenderTarget[0].DestBlendAlpha =
		D3D11_BLEND_ZERO;
	bs.RenderTarget[0].BlendOpAlpha =
		D3D11_BLEND_OP_ADD;

	bs.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_pd3dDevice->CreateBlendState(&bs,
		&m_pAlphaBlend);

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_FRONT;
	m_pd3dDevice->CreateRasterizerState(&rd, &m_pRSWireFrame);

	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
	// Z 버퍼 비교 활성화
	dsd.DepthEnable = TRUE;
	// z값 버퍼에 저장
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	// 비교 연산
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	m_pd3dDevice->CreateDepthStencilState(&dsd, &m_pDSS);


	m_PlaneObj.Create(m_pd3dDevice, m_pImmediateContext,L"../../data/bitmap/bitmap1.bmp");


	m_pImmediateContext->OMSetBlendState(m_pAlphaBlend, 0, -1);
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pImmediateContext->RSSetState(m_pRSSold);
	m_pImmediateContext->OMSetDepthStencilState(m_pDSS, 0);

	SetViewProj();
	return true;
}
bool Sample::Frame()
{
	if (G_Input.KeyCheck('w'))
	{
		m_vPos = m_vPos + Vector3(0, 0, 5.0f)*g_SecondPerFrame;

	}
	if (G_Input.KeyCheck('s'))
	{
		m_vPos = m_vPos + Vector3(0, 0, -5.0f)*g_SecondPerFrame;

	}
	if (G_Input.KeyCheck('a'))
	{
		m_vPos = m_vPos + Vector3(5.0f, 0,0)*g_SecondPerFrame;

	}
	if (G_Input.KeyCheck('d'))
	{
		m_vPos = m_vPos + Vector3(-5.0f, 0, 0)*g_SecondPerFrame;

	}
	m_PlaneObj.Frame();
	return true;
}
bool Sample::Render()
{
	m_pImmediateContext->RSSetState(m_pRSSold);//레스터라이저 스테이트 세팅
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_PlaneObj.m_pSRVa);//텍스트 리소스 세팅

	
	m_PlaneObj.SetMatrix(nullptr, &m_matView, &m_matProj);//매트릭스 갱신
	
	
	m_PlaneObj.Render();
	return true;
}
bool Sample::Release()
{
	m_PlaneObj.Release();
	m_pSamplerState->Release();
	return true;
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
	if (!game.InitWindow(L"ROCK_MAN", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}