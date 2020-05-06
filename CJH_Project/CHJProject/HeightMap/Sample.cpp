#include "Sample.h"
#include"JH_DxState.h"
#include "D3DX11.h"
#include"JH_Model.h"
#include "JH_ShapePlane.h"
#include"JH_Input.h"
#pragma warning( disable:4005 )

void JH_Map::SetMapDesc(
const TCHAR* TextureFileName,
const TCHAR* ShaderFileName,
int ColumNum,
int RowNum,
float fSellDistance,
float fScaleHeight,
const TCHAR* NormalMapFileName = nullptr)
{
	m_MapDesc.iColumNum= ColumNum;
	m_MapDesc.iRowNum= RowNum;
	m_MapDesc.TextureFileName= TextureFileName;
	m_MapDesc.ShaderFileName= ShaderFileName;
	m_MapDesc.fSellDistance= fSellDistance;
	m_MapDesc.fScaleHeight= fScaleHeight;
	m_MapDesc.NormalMapFileName = NormalMapFileName;
}

HRESULT JH_Map::CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext,const TCHAR* TextureFileName)
{
	D3DX11_IMAGE_INFO imageInfo;
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	LoadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	LoadInfo.Usage = D3D11_USAGE_STAGING;
	LoadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	LoadInfo.pSrcInfo = &imageInfo;
	LoadInfo.MipLevels = 1;

	ID3D11Resource* pResource = nullptr;

	HRESULT hr;
	hr = D3DX11CreateTextureFromFile(pD3D11Device, TextureFileName, &LoadInfo, NULL, &pResource, NULL);
	if (hr!=S_OK)
	{
		return false;
	}

	ID3D11Texture2D* pTexture = nullptr;
	if (FAILED(pResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture)))
	{
		return false;
	}	
	

	D3D11_TEXTURE2D_DESC desc;

	pTexture->GetDesc(&desc);
	m_iRowNum = desc.Height;
	m_iColumNum = desc.Width;
	m_vHeightList.resize(desc.Height*desc.Width);

	D3D11_MAPPED_SUBRESOURCE MapResrc;

	if (SUCCEEDED(pD3D11DeviceContext->Map((ID3D11Resource*)pTexture, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, NULL, &MapResrc)))
	{
		UCHAR* pTexcell = (UCHAR*)MapResrc.pData;
		for (int iRow = 0; iRow < desc.Height; iRow++)
		{
			int irowStart = MapResrc.RowPitch*iRow;
			for ( int iCol = 0;  iCol < desc.Width;  iCol++)
			{
				BYTE R = pTexcell[irowStart + iCol * 4];
				
				m_vHeightList[iRow*desc.Width + iCol] = R;
			}

		}
		pD3D11DeviceContext->Unmap((ID3D11Resource*)pTexture, D3D11CalcSubresource(0, 0, 1));
	}
	pResource->Release();

}
HRESULT  JH_Map::Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext)
{
	
	 m_iColumNum= m_MapDesc.iColumNum;
	 m_iRowNum= m_MapDesc.iRowNum;
	 m_iCellRow = m_MapDesc.iRowNum - 1;
	 m_iCellCol = m_MapDesc.iColumNum - 1;
	 m_iVertices = m_iColumNum * m_iRowNum;
	 m_TextureFileName= m_MapDesc.TextureFileName;
	 m_ShaderFileName= m_MapDesc.ShaderFileName;
	 m_TextureFileName
	 m_fSellDistance= m_MapDesc.fSellDistance;
	 m_fScaleHeight= m_MapDesc.fScaleHeight;

	 

	 if (m_MapDesc.NormalMapFileName!=nullptr)
	 {
		 
	 }
	 if (!Create(pD3D11Device, pD3D11DeviceContext, m_MapDesc.ShaderFileName, m_MapDesc.TextureFileName))
	 {
		 return  false;
	 }
	 return true;
}
HRESULT JH_Map::CreateVertexData()
{
	
	HRESULT hr = S_OK;
	m_dxHelper.m_iVertexSize = sizeof(PNCT_VERTEX);
	m_VertexData.resize(m_iVertices);

	float fHalfCols = m_iCellCol / 2.0f;
	float fHalfRows = m_iCellRow / 2.0f;
	float ftxOffsetU = 1.0f / m_iCellCol;
	float ftxOffsetV = 1.0f / m_iCellRow;

	for (int iRow = 0; iRow < m_iRowNum; iRow++)
	{
		for (int iCol = 0; iCol < m_iColumNum; iCol++)
		{
			int  iVertexIndex = iRow * m_iColumNum + iCol;
			m_VertexData[iVertexIndex].p.x = (iCol - fHalfCols) * m_fSellDistance;
			m_VertexData[iVertexIndex].p.z = -((iRow - fHalfRows) * m_fSellDistance);
			m_VertexData[iVertexIndex].p.y = m_vHeightList[iVertexIndex]/m_fScaleHeight;
			m_VertexData[iVertexIndex].n = D3DXVECTOR3(0, 1.0f, 0);
			m_VertexData[iVertexIndex].c = D3DXVECTOR4(1.0F, 1.0F, 1.0F, 1.0F);
			m_VertexData[iVertexIndex].t = D3DXVECTOR2(ftxOffsetU * iCol, ftxOffsetV * iRow);
		}
	}
	return true;
}

HRESULT JH_Map::CreateIndexData()
{
	m_IndexData.resize(m_iCellRow*m_iCellCol * 2 * 3);

	int iCurIndex = 0;
	for (int iRow = 0; iRow < m_iCellRow; iRow++)
	{
		for (int iCol = 0; iCol < m_iCellCol; iCol++)
		{
			//0	1    4   
			//2	   3 5
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_IndexData[iCurIndex + 0] = iRow * m_iRowNum + iCol;
			m_IndexData[iCurIndex + 1] = iRow * m_iRowNum + iNextCol;
			m_IndexData[iCurIndex + 2] = iNextRow * m_iRowNum + iCol;
			m_IndexData[iCurIndex + 3] = m_IndexData[iCurIndex + 2];
			m_IndexData[iCurIndex + 4] = m_IndexData[iCurIndex + 1];
			m_IndexData[iCurIndex + 5] = iNextRow * m_iRowNum + iNextCol;

			iCurIndex += 6;
		} 
	}


	return true;
}


bool Sample::Init()
{

	m_Map.CreateHeightMap(m_pd3dDevice,m_pImmediateContext,L"../../data/map/WaterMap.jpg");


	m_Map.SetMapDesc(L"../../data/map/Tile26.jpg",L"DefaultShader.txt",m_Map.m_iColumNum,m_Map.m_iRowNum,1,10.0f);
	
	m_Map.Load(m_pd3dDevice, m_pImmediateContext);

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0,200, -100.0), D3DXVECTOR3(0, 0, 0));

	//m_pMainCamera->CreateProjMatrix(0.1f,1000.0f,DXGI_PI);
	JDX::ApplySS(m_pImmediateContext, JDX::JH_DxState::g_pSamplerState);
	return true;
}
bool Sample::Frame()

{
	if (G_Input.KeyCheck('Q') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.x -= 50 * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('E') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.x += 50 * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('A') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.z -= 50 * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('D') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.z += 50 * g_SecondPerFrame;
	}

	if (G_Input.KeyCheck('W') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.y -= 50 * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck('S') == KEY_PUSH)
	{
		m_pMainCamera->m_vPos.y += 50 * g_SecondPerFrame;
	}
	if (G_Input.KeyCheck(VK_F3) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext(), JDX::JH_DxState::g_pRSSold);
	}
	if (G_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext(), JDX::JH_DxState::g_pRSWireFrame);
	}
	return true;
}
bool Sample::Render()
{
	m_Map.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Map.Render();

	return true;
}
bool Sample::Release()
{

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
	_In_ int       nCmdShow) {
	Sample game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ROCKMAN", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;
}
