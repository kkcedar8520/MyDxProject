#include "Sample.h"
#include"JH_Input.h"
bool	Sample::SetViewProj()
{
	m_vPos = Vector3(0, 0.0f, -5.0f);
	m_vAt = Vector3(0, 0.0f, 0);
	m_vUp = Vector3(0, 1.0f, 0);
	m_matView = Matrix::CreateViewLookAt(m_vPos, m_vAt, m_vUp);



	float fNear = 1.0f;
	float fFar = 1000.0f;
	float fFovY = D3DX_PI * 0.5f;
	float fAspect = (float)g_rtClient.right / (float)g_rtClient.bottom;
	m_matProj =
		Matrix::CreatePerspectiveFovLH(fNear, fFar, fFovY,
			fAspect);


	return true;
}
bool	Sample::Init()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC descSamp;
	ZeroMemory(&descSamp, sizeof(D3D11_SAMPLER_DESC));
	descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSamp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	descSamp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	descSamp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	hr = m_pd3dDevice->CreateSamplerState(
		&descSamp,
		&m_pSamplerState);

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
		&m_pAlpahBlend);

	bs.RenderTarget[0].BlendEnable = FALSE;
	hr = m_pd3dDevice->CreateBlendState(&bs,
		&m_pAlpahBlendDisable);

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	m_pd3dDevice->CreateRasterizerState(&rd, &m_pRSSold);
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
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
	dsd.DepthEnable = FALSE;
	m_pd3dDevice->CreateDepthStencilState(&dsd, &m_pDSSDisable);


	m_planeObj.Create(
		m_pd3dDevice,
		m_pImmediateContext,
		L"DefaultShader.txt",
		L"../../data/bitmap1.bmp");



	m_pImmediateContext->OMSetBlendState(m_pAlpahBlend, 0, -1);
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pImmediateContext->RSSetState(m_pRSSold);
	m_pImmediateContext->OMSetDepthStencilState(m_pDSS, 0);

	SetViewProj();
	return true;
}
bool	Sample::Frame()
{
	if (G_Input.KeyCheck(VK_F1) == KEY_PUSH)
	{
		m_pImmediateContext->OMSetBlendState(
			m_pAlpahBlend, 0, -1);
	}
	if (G_Input.KeyCheck(VK_F2) == KEY_PUSH)
	{
		m_pImmediateContext->OMSetBlendState(
			m_pAlpahBlendDisable, 0, -1);
	}
	if (G_Input.KeyCheck(VK_F3) == KEY_PUSH)
	{
		m_pImmediateContext->RSSetState(m_pRSSold);
	}
	if (G_Input.KeyCheck(VK_F4))
	{
		m_pImmediateContext->RSSetState(m_pRSWireFrame);
	}

	if (G_Input.KeyCheck('W') != KEY_FREE)
	{
		m_vPos = m_vPos + Vector3(0, 0.0f, 50.0f) * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('S') != KEY_FREE)
	{
		m_vPos = m_vPos - Vector3(0, 0.0f, 50.0f) * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('A') != KEY_FREE)
	{
		m_vPos = m_vPos + Vector3(50, 0.0f, 0.0f) * g_SecondPerFrame;
		m_vAt.x = m_vPos.x;
	}
	if (G_Input.KeyCheck('D') != KEY_FREE)
	{
		m_vPos = m_vPos - Vector3(50, 0.0f, 0.0f) * g_SecondPerFrame;
		m_vAt.x = m_vPos.x;
	}


	m_matView = Matrix::CreateViewLookAt(m_vPos, m_vAt, m_vUp);

	m_planeObj.Frame();
	return true;
}
//The Pixel Shader unit expects a Sampler to be set at Slot 0,
bool	Sample::Render()
{
	m_pImmediateContext->OMSetDepthStencilState(m_pDSS, 0);
	m_pImmediateContext->RSSetState(m_pRSSold);


	m_planeObj.m_matWorld._11 = 400.0f;
	m_planeObj.m_matWorld._22 = 300.0f;
	m_planeObj.m_matWorld._43 = 1.0f;
	m_planeObj.SetMatrix(nullptr, nullptr, &m_matProj);
	m_planeObj.Render();




	return true;
}
bool	Sample::Release()
{

	m_planeObj.Release();
	m_pDSS->Release();
	m_pSamplerState->Release();
	m_pAlpahBlend->Release();
	m_pAlpahBlendDisable->Release();
	m_pRSWireFrame->Release();
	m_pRSSold->Release();
	m_pDSSDisable->Release();
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
	if (!game.InitWindow(L"CreateIndexConstantBuffer", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}