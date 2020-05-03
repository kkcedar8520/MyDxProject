#include "JH_Map.h"
//������ �Լ�
bool JH_Map::AddSplattTexture(const TCHAR* pFileName)
{

	int index=I_Texture.Add(m_dxHelper.m_pd3dDevice, pFileName);


	m_vTextureList.push_back(I_Texture.GetPtr(index));
	return true;
}
// Base Function
bool	JH_Map::UpdateBuffer()
{
	D3DXVECTOR3 vTangent, vBiNormal, vNormal;
	int iIndex = 0;
	int i0, i1, i2, i3, i4, i5;


	m_TangentList.resize(m_VertexData.size());
	for (int iIndex = 0; iIndex < m_dxHelper.m_iNumIndex; iIndex += 3)
	{
		i0 = m_IndexData[iIndex + 0];
		i1 = m_IndexData[iIndex + 1];
		i2 = m_IndexData[iIndex + 2];

		m_NormalMap.CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0]+= vTangent;

		i0 = m_IndexData[iIndex + 1];
		i1 = m_IndexData[iIndex + 2];
		i2 = m_IndexData[iIndex + 0];

		m_NormalMap.CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0] += vTangent;

		i0 = m_IndexData[iIndex + 2];
		i1 = m_IndexData[iIndex + 0];
		i2 = m_IndexData[iIndex + 1];

		m_NormalMap.CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0]+= vTangent;

	}
	for (int i = 0; i < m_iRowNum*m_iColumNum; i++)
	{
		D3DXVec3Normalize(&m_TangentList[i0], &m_TangentList[i0]);
	}


	m_pTangentVB.Attach(DX::CreateVertexBuffer(m_dxHelper.m_pd3dDevice, &m_TangentList.at(0), m_TangentList.size(), sizeof(D3DXVECTOR3)));
		

	return true;
}
float JH_Map::GetHeight(float fX, float fZ)
{
	float fCellX = (float)(m_iCellCol*m_fCellDistance / 2.0f + fX);
	float fCellZ = (float)(m_iCellRow*m_fCellDistance / 2.0f - fZ);

	float Height = 0.0F;
	fCellX = (float)fCellX / m_fCellDistance;
	fCellZ = (float)fCellZ / m_fCellDistance;

	float fVertexCol = ::floorf(fCellX);
	float fVertexRow = ::floorf(fCellZ);


	if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
	if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
	if ((float)(m_iColumNum - 2) < fVertexCol)	fVertexCol = (float)(m_iColumNum - 2);
	if ((float)(m_iRowNum - 2) < fVertexRow)	fVertexRow = (float)(m_iRowNum - 2);

	float A = GetHeightMap((int)fVertexRow, (int)fVertexCol);
	float B = GetHeightMap((int)fVertexRow, (int)fVertexCol + 1);
	float C = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol + 1);

	if (fVertexCol + fVertexRow < 1.0f)
	{
		float u = fCellX - fVertexCol;
		float v = fCellZ - fVertexRow;

		return Height = (float)(A - u * (B - A) + v * (C - A));
	}
	else
	{
		float u = (1.0f - (fCellX - fVertexCol));
		float v = (1.0f - (fCellZ - fVertexRow));

		return Height = (float)(D - u * (C - D) + v * (B - D));
	}
	return Height;
	//// fPosX/fPosZ�� ��ġ�� �ش��ϴ� ���̸ʼ��� ã�´�.
	//// m_iNumCols��m_iNumRows�� ����/������ ���� ũ�Ⱚ��.
	//float fCellX = (float)(m_iCellCol*m_fCellDistance / 2.0f + fX);
	//float fCellZ = (float)(m_iCellRow*m_fCellDistance / 2.0f - fZ);

	//// ���� ũ��� ������ 0~1 ������ ������ �ٲپ� ���̸� �迭�� �����Ѵ�.
	//fCellX /= (float)m_fCellDistance;
	//fCellZ /= (float)m_fCellDistance;

	//// fCellX, fCellZ ������ �۰ų� ���� �ִ� ����( �Ҽ��κ��� �߶󳽴�.)
	//float fVertexCol = ::floorf(fCellX);
	//float fVertexRow = ::floorf(fCellZ);

	//// ���̸� ������ ����� ������ �ʱ�ȭ �Ѵ�.
	//if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
	//if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
	//if ((float)(m_iColumNum - 2) < fVertexCol)	fVertexCol = (float)(m_iColumNum - 2);
	//if ((float)(m_iRowNum - 2) < fVertexRow)	fVertexRow = (float)(m_iRowNum - 2);

	//// ���� ���� �÷��� �����ϴ� 4�� ������ ���̰��� ã�´�. 
	////  A   B
	////  *---*
	////  | / |
	////  *---*  
	////  C   D
	//float A = GetHeightMap((int)fVertexRow, (int)fVertexCol);
	//float B = GetHeightMap((int)fVertexRow, (int)fVertexCol + 1);
	//float C = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol);
	//float D = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol + 1);

	//// A������ ��ġ���� ������ ��(������)�� ����Ѵ�. 0 ~ 1.0f
	//float fDeltaX = fCellX - fVertexCol;
	//float fDeltaZ = fCellZ - fVertexRow;
	//// �����۾��� ���� ���� ���ս��� ã�´�. 
	//float fHeight = 0.0f;
	//// �����̽��� �������� �����Ѵ�.
	//// fDeltaZ + fDeltaX < 1.0f
	//if (fDeltaZ < (1.0f - fDeltaX))  //ABC
	//{
	//	float uy = B - A; // A->B
	//	float vy = C - A; // A->C	
	//					  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸX�� ���� ���� �������� ã�´�.		
	//	fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	//}
	//// �Ʒ����̽��� �������� �����Ѵ�.
	//else // DCB
	//{
	//	float uy = C - D; // D->C
	//	float vy = B - D; // D->B
	//					  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸZ�� ���� ���� �������� ã�´�.		
	//	fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	//}
	//return fHeight;
}

float JH_Map::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart*fTangent) + (fEnd*fTangent);
}
float JH_Map::GetHeightMap(int iRow, int iCol)
{
	return	m_vHeightList[iRow*m_iRowNum + iCol];
}

void  JH_Map::UpdateConstantBuffer(ID3D11Buffer* pConstantBuffer, void* Data)
{
	m_dxHelper.m_pContext->UpdateSubresource(pConstantBuffer, 0, nullptr, Data, 0, 0);
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

	D3DXMatrixInverse(&m_matNormal, 0, &m_matWorld);
	


	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
	D3DXMatrixTranspose(&m_cbData.matNormal, &m_matNormal);


	m_cbData.d.x = cosf(g_fProgramTime) *0.5f + 0.5f;
	m_dxHelper.m_pContext->UpdateSubresource(
		m_dxHelper.m_pConstantBuffer.Get(),
		0, NULL, &m_cbData, 0, 0);


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
	pTexture->Release();
	
	pResource->Release();

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

			if (m_vHeightList.size())
			{
				m_VertexData[iVertexIndex].p.y = m_vHeightList[iVertexIndex] / m_MapDesc.fScaleHeight;
			}
			else
			{
				m_VertexData[iVertexIndex].p.y = 0.0f;
			}
			m_VertexData[iVertexIndex].p.x = (iCol - fHalfCols) * m_fCellDistance;
			m_VertexData[iVertexIndex].p.z = -((iRow - fHalfRows) * m_fCellDistance);
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
HRESULT JH_Map::CreateInputLayout()
{
	HRESULT hr = S_OK;
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		// ����ġ �ε��� 
		/*{ "TEX",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64,  D3D11_INPUT_PER_VERTEX_DATA, 0 },*/
	};
	UINT iElementCount = sizeof(layout) /
		sizeof(layout[0]);
	m_dxHelper.m_pd3dDevice->CreateInputLayout(
		layout,
		iElementCount,
		m_dxHelper.m_pVertexCode->GetBufferPointer(),
		m_dxHelper.m_pVertexCode->GetBufferSize(),
		&m_dxHelper.m_pVertexLayout);
	return hr;
}
HRESULT	JH_Map::LoadTexture(const TCHAR* pszTexFileName)
{
	HRESULT hr = S_OK;
	if (m_dxHelper.m_pSRV = DX::CreateShaderResourceViewFromFile(m_dxHelper.m_pd3dDevice, pszTexFileName))
	
	m_iTexNum=I_Texture.Add(m_dxHelper.m_pd3dDevice, m_pNormMapFileName);
	m_pTexture = I_Texture.GetPtr(m_iTexNum);

	return hr;
}

bool JH_Map::Frame()
{

	
	return true;
}
bool JH_Map::Release()
{
	m_vHeightList.clear();
	return true;
}
JH_Map::JH_Map()
{
	m_iTexNum = -1;
	m_bMapEdit = false;
}
JH_Map::~JH_Map()
{
	Release();
}