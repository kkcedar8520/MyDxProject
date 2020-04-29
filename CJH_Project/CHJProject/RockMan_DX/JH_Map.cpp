#include "JH_Map.h"
#include"JH_Input.h"

HRESULT	JH_Map::LoadTexture(const TCHAR* pszTexFileName)
{
	HRESULT hr = S_OK;
	if (L"../../data/Resource/Start.bmp" == NULL) return S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_dxHelper.m_pd3dDevice,
		L"../../data/Resource/Start.bmp",
		NULL,
		NULL,
		&m_pSRV_Start,
		NULL);

	
	if (L"../../data/Resource/GUTSMAP.bmp" == NULL) return S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_dxHelper.m_pd3dDevice,
		L"../../data/Resource/GutsMap.bmp",
		NULL,
		NULL,
		&m_pSRV_Gust,
		NULL);

	if (L"../../data/Resource/CloudMap.bmp" == NULL) return S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_dxHelper.m_pd3dDevice,
		L"../../data/Resource/CloudMap.bmp",
		NULL,
		NULL,
		&m_pSRV_Cloud,
		NULL);
	
	if (L"../../data/Resource/103462.bmp" == NULL) return S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(
		m_dxHelper.m_pd3dDevice,
		L"../../data/Resource/103462.bmp",
		NULL,
		NULL,
		&m_pSRV_Boss,
		NULL);

	m_SrvList.resize(MAPCOUNT);
	m_SrvList[START] = m_pSRV_Start;
	m_SrvList[GUSTMAP] = m_pSRV_Gust;
	m_SrvList[CloudMap]= m_pSRV_Cloud;
	m_SrvList[BOSSMap] = m_pSRV_Boss;

	m_CorrentStage = START;
	return hr;
}
bool JH_Map::Frame()
{
	if (m_CorrentStage == START)
	{
		if (G_Input.KeyCheck(VK_RETURN))
		{
			m_CorrentStage=GUSTMAP;
			m_matWorld._11 = 600;
			m_matWorld._22 = 300;
		}
	}
	return true;
}
bool JH_Map::PostRender()
{
	m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &m_SrvList[m_CorrentStage]);
	m_dxHelper.PostRender();
	return true;
}
JH_Map::JH_Map()
{
}


JH_Map::~JH_Map()
{
}
