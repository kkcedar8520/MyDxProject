#include "Sample.h"
#include"JH_Map.h"
bool Sample::Init()
{

	HRESULT hr=S_OK;
	D3D11_SAMPLER_DESC descSamp;
	ZeroMemory(&descSamp, sizeof(D3D11_SAMPLER_DESC));
	descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSamp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	descSamp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	descSamp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	hr = m_pd3dDevice->CreateSamplerState(
		&descSamp,
		&m_pSamplerState);

	D3D11_BLEND_DESC	bs;
	ZeroMemory(&bs, sizeof(D3D11_BLEND_DESC));
	//bs.AlphaToCoverageEnable = TRUE;
	bs.IndependentBlendEnable = TRUE;
	bs.RenderTarget[0].BlendEnable = TRUE;
	bs.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bs.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_pd3dDevice->CreateBlendState(&bs, &m_pAlphaBlend);
	m_pImmediateContext->OMSetBlendState(m_pAlphaBlend, 0, -1);

	m_PlaneObj.Create(m_pd3dDevice, m_pImmediateContext, L"../../data/bitmap/bitmap1.bmp");
	return true;
}

bool Sample::Frame()
{
	m_PlaneObj.Frame();
	return true;
}
bool Sample::Render()
{
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pImmediateContext->OMSetBlendState(m_pAlphaBlend, 0, -1);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_PlaneObj.m_pSRVa);
	m_pImmediateContext->PSSetShaderResources(1, 1, &m_PlaneObj.m_pSRVb);
	m_PlaneObj.Render();
	return true;
}
bool Sample::Release()
{
	m_pAlphaBlend->Release();
	m_pSamplerState->Release();
	m_PlaneObj.Release();
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