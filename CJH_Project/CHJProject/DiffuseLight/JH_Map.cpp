#include "JH_Map.h"


void  JH_Map::UpdateConstantBuffer(ID3D11Buffer* pConstantBuffer, void* Data)
{
	m_dxHelper.m_pContext->UpdateSubresource(pConstantBuffer, 0, nullptr,Data, 0, 0);
}
void    JH_Map::SetMatrix(D3DXMATRIX* matWorld,
	D3DXMATRIX* matView,
	D3DXMATRIX* matProj)
{
	if (matWorld != nullptr)
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


	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);


	m_cbData.d.x = cosf(g_fProgramTime) *0.5f + 0.5f;
	//D3DXVECTOR4 Norm = D3DXVECTOR4(cosf(g_fProgramTime) * 100, 100, sinf(g_fProgramTime) * 100, 1.0f);
	//D3DXVec4Normalize(&Norm, &Norm);


	//m_cbData.Light.x = m_vEyePos.x;
	//m_cbData.Light.y = m_vEyePos.y;
	//m_cbData.Light.z = m_vEyePos.z;

	//m_cbData.Light = -Norm;
	D3D11_MAPPED_SUBRESOURCE mss;
	if (SUCCEEDED(m_dxHelper.m_pContext->Map(
		m_dxHelper.m_pConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &mss)))
	{
		CB_DATA* pData = (CB_DATA*)mss.pData;
		memcpy(pData, &m_cbData, sizeof(CB_DATA));
		m_dxHelper.m_pContext->Unmap(m_dxHelper.m_pConstantBuffer, 0);
	}

}


void JH_Map::SetMapDesc(
	const TCHAR* TextureFileName,
	const TCHAR* ShaderFileName,
	int ColumNum,
	int RowNum,
	float fSellDistance,
	float fScaleHeight)
{
	m_MapDesc.iColumNum = ColumNum;
	m_MapDesc.iRowNum = RowNum;
	m_MapDesc.TextureFileName = TextureFileName;
	m_MapDesc.ShaderFileName = ShaderFileName;
	m_MapDesc.fSellDistance = fSellDistance;
	m_MapDesc.fScaleHeight = fScaleHeight;

}

HRESULT JH_Map::CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext, const TCHAR* TextureFileName)
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
	if (hr != S_OK)
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
			for (int iCol = 0; iCol < desc.Width; iCol++)
			{
				BYTE R = pTexcell[irowStart + iCol * 4];

				m_vHeightList[iRow*desc.Width + iCol] = R;
			}

		}
		pD3D11DeviceContext->Unmap((ID3D11Resource*)pTexture, D3D11CalcSubresource(0, 0, 1));
	}
	SAFE_DEL(MapResrc.pData);
	
	pResource->Release();
	pTexture->Release();

	m_iRowNum = desc.Height;
	m_iColumNum = desc.Width;

}
HRESULT  JH_Map::Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext)
{

	m_iColumNum = m_MapDesc.iColumNum;
	m_iRowNum = m_MapDesc.iRowNum;
	m_iCellRow = m_MapDesc.iRowNum - 1;
	m_iCellCol = m_MapDesc.iColumNum - 1;
	m_iVertices = m_iColumNum * m_iRowNum;
	m_TextureFileName = m_MapDesc.TextureFileName;
	m_ShaderFileName = m_MapDesc.ShaderFileName;
	m_fCellDistance = m_MapDesc.fSellDistance;
	m_fScaleHeight = m_MapDesc.fScaleHeight;




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
			m_VertexData[iVertexIndex].p.x = (iCol - fHalfCols) * m_fCellDistance;
			m_VertexData[iVertexIndex].p.z = -((iRow - fHalfRows) * m_fCellDistance);
			m_VertexData[iVertexIndex].p.y = m_vHeightList[iVertexIndex] / m_fScaleHeight;
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


			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_IndexData[iCurIndex + 0] = iRow * m_iColumNum + iCol;
			m_IndexData[iCurIndex + 1] = iRow * m_iColumNum + iNextCol;
			m_IndexData[iCurIndex + 2] = iNextRow * m_iColumNum + iCol;

			m_IndexData[iCurIndex + 3] = m_IndexData[iCurIndex + 2];
			m_IndexData[iCurIndex + 4] = m_IndexData[iCurIndex + 1];
			m_IndexData[iCurIndex + 5] = iNextRow * m_iColumNum + iNextCol;




			D3DXVECTOR3 vFaceNormal, E0, E1;
			int i = 0;

			E0 = m_VertexData[m_IndexData[iCurIndex + 1]].p - m_VertexData[m_IndexData[iCurIndex + 0]].p;
			E1 = m_VertexData[m_IndexData[iCurIndex + 2]].p - m_VertexData[m_IndexData[iCurIndex + 0]].p;

			D3DXVec3Cross(&vFaceNormal, &E0, &E1);


			m_VertexData[m_IndexData[iCurIndex + 0]].n += vFaceNormal;
			m_VertexData[m_IndexData[iCurIndex + 1]].n += vFaceNormal;
			m_VertexData[m_IndexData[iCurIndex + 2]].n += vFaceNormal;

			E0 = m_VertexData[m_IndexData[iCurIndex + 4]].p - m_VertexData[m_IndexData[iCurIndex + 3]].p;
			E1 = m_VertexData[m_IndexData[iCurIndex + 5]].p - m_VertexData[m_IndexData[iCurIndex + 3]].p;


			D3DXVec3Cross(&vFaceNormal, &E0, &E1);


			m_VertexData[m_IndexData[iCurIndex + 3]].n += vFaceNormal;
			m_VertexData[m_IndexData[iCurIndex + 4]].n += vFaceNormal;
			m_VertexData[m_IndexData[iCurIndex + 5]].n += vFaceNormal;


			iCurIndex += 6;
		}
	}

	D3DXVECTOR3 vLight(0, -1, 0);
	for (size_t i = 0; i < m_VertexData.size(); i++)
	{

		D3DXVec3Normalize(&m_VertexData[i].n, &m_VertexData[i].n);
	/*	float fDot = D3DXVec3Dot(&-vLight, &m_VertexData[i].n);


	
		m_VertexData[i].c.x = fDot;
		m_VertexData[i].c.y = fDot;
		m_VertexData[i].c.z = fDot;
		m_VertexData[i].c.w = 1.0f;*/
	}





	return true;
}