#pragma once
#include "SkinObj.h"
HRESULT SkinObj::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_dxHelper.m_iVertexSize = sizeof(PNCTIW_VERTEX);
	//m_VertexSkinData[22].w.w = 0.0f;
	return hr;

}
HRESULT SkinObj::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	if (m_VertexSkinData.size() <= 0) return E_FAIL;
	m_dxHelper.m_iNumVertex = m_VertexSkinData.size();
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = m_dxHelper.m_iVertexSize * m_VertexSkinData.size();
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_VertexSkinData.at(0);

	hr = m_dxHelper.m_pd3dDevice->CreateBuffer(&pDesc,
		&pInitialData,
		&m_dxHelper.m_pVertexBuffer);
	return hr;
}
HRESULT SkinObj::CreateIndexData()
{
	HRESULT hr = S_OK;
	return hr;
}
HRESULT SkinObj::CreateConstantBuffer()
{
	JH_Model::CreateConstantBuffer();
	HRESULT hr=S_OK;

	m_pBoneConstBuffer.Attach(DX::
		MakeConstantBuffer(
			m_dxHelper.m_pd3dDevice,
			nullptr, 
			sizeof(CBConstBonelWorld), 1,true));
	return hr;
}
HRESULT SkinObj::CreateInputLayout()
{
	HRESULT hr = S_OK;
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
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
void SkinObj::GetVIData(HMeshSkin& mesh)
{
	HRESULT hr = S_OK;
	vector<PNCTIW_VERTEX> Vertex;
	if (mesh.m_SkinTriList.size() <= 0)
	{
		return;
	}
	else
	{
		
		Vertex.resize(mesh.m_SkinTriList.size() * 3);
		for (int i = 0; i < mesh.m_SkinTriList.size(); i++)
		{
			for (int  iVertex = 0; iVertex < 3; iVertex++)
			{
				Vertex[i * 3 + iVertex] = mesh.m_SkinTriList[i].v[iVertex];

			}
		}
	}
	/*mesh.m_vbSkinList.reserve(mesh.m_SkinTriList.size()*3);
	for (int iFace = 0; iFace < mesh.m_SkinTriList.size(); iFace++)
	{
		for (int iVertex = 0; iVertex < 3; iVertex++)
		{

			int iPos = -1;
			for (int i = 0; i < mesh.m_vbSkinList.size(); i++)
			{
				if (mesh.m_vbSkinList[i] == mesh.m_SkinTriList[iFace].v[iVertex])
				{
					iPos = i;
					break;
				}
			}
			if (iPos < 0)
			{
				mesh.m_vbSkinList.push_back(mesh.m_SkinTriList[iFace].v[iVertex]);
				iPos = mesh.m_vbSkinList.size() - 1;
			}
			mesh.m_ibList.push_back(iPos);
		}
	}*/
	mesh.m_vbSkinList.reserve(Vertex.size());
	for (int iVertex = 0; iVertex < Vertex.size(); iVertex++)
	{
		int iPos = -1;
		for (int i = 0; i < mesh.m_vbSkinList.size(); i++)
		{
			if (mesh.m_vbSkinList[i] == Vertex[iVertex])
			{
				iPos = i;
				break;
			}

		}
		if (iPos < 0)
		{
			mesh.m_vbSkinList.push_back(Vertex[iVertex]);
			iPos = mesh.m_vbSkinList.size() - 1;
		}
		mesh.m_ibList.push_back(iPos);
	}
}
int SkinObj::GetParentIndex(const TCHAR*	strName)
{
	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
	{
		T_STR szName = m_ExpObject[iObj].m_szName;
		if (strName == szName)
		{
			return iObj;
		}
	}
	return -1;
}
bool	SkinObj::Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile)
{
	m_dxHelper.m_pd3dDevice = pdvice;
	m_dxHelper.m_pContext = pContext;
	Parsing(LoadFile);
	Convert();
	Create(pdvice, pContext, L"../../data/shader/SkinShader.txt",nullptr);
	return true;
}
void	SkinObj::Convert()
{
	int iBaseOffset = 0;
	int iBaseIndex = 0;



	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
	{
		HMeshSkin& mesh=m_ExpObject[iObj];
		//mesh.m_AnimTrackPos.assign(m_ExpObject[iObj].m_AnimTrackPos.begin(),
		//	m_ExpObject[iObj].m_AnimTrackPos.end());

		//mesh.m_AnimTrackRotate.assign(m_ExpObject[iObj].m_AnimTrackRotate.begin(),
		//	m_ExpObject[iObj]->m_AnimTrackRotate.end());
		//mesh.m_AnimTrackScale.assign(m_ExpObject[iObj]->m_AnimTrackScale.begin(),
		//	m_ExpObject[iObj]->m_AnimTrackScale.end());

	
		mesh.m_matWorld = m_ExpObject[iObj].m_matWorld;
		//mesh.m_szName = m_ExpObject[iObj].m_szName;
		//mesh.m_szParentName = m_ExpObject[iObj].m_szParentName;


		D3DXMATRIX matParentInverse, matDefaultAnim;
		D3DXMatrixIdentity(&matParentInverse);
		mesh.m_iParentIndex = GetParentIndex(m_ExpObject[iObj].m_szParentName);

		if (mesh.m_iParentIndex >= 0)
		{
			D3DXMatrixInverse(&matParentInverse, NULL, &m_ExpObject[mesh.m_iParentIndex].m_matWorld);
		}
		matDefaultAnim = mesh.m_matWorld*matParentInverse;

		D3DXVECTOR3 vPos, vScale;
		D3DXQUATERNION qR;
		D3DXMatrixDecompose(&vScale, &qR, &vPos, &matDefaultAnim);

		mesh.m_vAnimPos = vPos;
		mesh.m_vAnimScale = vScale;
		mesh.m_qAnimRotation = qR;
		D3DXQuaternionIdentity(&mesh.m_qAnimScaleRotation);





		int iRef = m_ExpObject[iObj].m_iRef;

		//레퍼런싱한 메테리얼이없을경우의 조건
		if (iRef >= 0)
		{
			if (m_ExpMtlList[iRef].submtl.size() > 0)
			{
				int iSubMtrl = m_ExpMtlList[iRef].submtl.size();
				mesh.subMesh.resize(iSubMtrl);
				for (int i = 0; i < iSubMtrl; i++)
				{
					if (m_ExpMtlList[iRef].submtl[i].m_MapList.size() > 0) {

						mesh.subMesh[i].m_iTextIndex = I_Texture.Add(m_dxHelper.m_pd3dDevice,
							m_ExpMtlList[iRef].submtl[i].m_MapList[0].szTextureName,
							L"../../data/Character/");

						
				
						mesh.subMesh[i].m_pTexture = I_Texture.GetPtr(mesh.subMesh[i].m_iTextIndex);
					}
				}
			}
			else
			{
				if (m_ExpMtlList[iRef].m_MapList.size() > 0) 
				{
					mesh.m_iTextIndex = I_Texture.Add(m_dxHelper.m_pd3dDevice,
						m_ExpMtlList[iRef].m_MapList[0].szTextureName,
						L"../../data/Character/");

				}
		
				
				mesh.m_pTexture = I_Texture.GetPtr(mesh.m_iTextIndex);

			}
		}

		//파일에 있는 월드행렬의 역행렬로 오브젝트를 원위치로 돌려놓고 다시 월드행렬로 위치시킴






		//D3DXMatrixInverse(&mesh.m_matInverseWorld, NULL, &mesh.m_matWorld);

		PNCT_VERTEX v;
		int index;
		// 데이터 복사
		/*for (int iFace = 0; iFace < m_ExpObject[iObj].m_TriList.size(); iFace++)
		{
			for (int iVertex = 0; iVertex < 3; iVertex++)
			{
				AddVertex(iObj, iFace, iVertex, mesh);
			}

		}*/

		if (mesh.subMesh.size() > 0)
		{
			for (int i = 0; i < mesh.subMesh.size(); i++)
			{

				GetVIData(mesh);
				mesh.subMesh[i].m_iNumFace = m_ExpObject[iObj].subMesh[i].m_SkinTriList.size();
				mesh.subMesh[i].m_iNumVertex = m_ExpObject[iObj].subMesh[i].m_vbSkinList.size();
				mesh.subMesh[i].m_iBaseVertex += iBaseOffset;
				
				mesh.subMesh[i].m_iNumIndex = m_ExpObject[iObj].subMesh[i].m_ibList.size();
				mesh.subMesh[i].m_iBaseIndex += iBaseIndex;
				iBaseOffset += mesh.subMesh[i].m_iNumVertex;
				iBaseIndex += mesh.subMesh[i].m_iNumIndex;
		

				// PNCT 버퍼에 한번에 몰아넣음
				std::copy(m_ExpObject[iObj].subMesh[i].m_vbSkinList.begin(),
					m_ExpObject[iObj].subMesh[i].m_vbSkinList.end(),
					back_inserter(m_VertexSkinData));

				std::copy(m_ExpObject[iObj].subMesh[i].m_ibList.begin(),
					m_ExpObject[iObj].subMesh[i].m_ibList.end(),
					back_inserter(m_IndexData));

			}

		}
		else
		{
			GetVIData(mesh);
			mesh.m_iNumFace = m_ExpObject[iObj].m_SkinTriList.size();
			mesh.m_iNumVertex = m_ExpObject[iObj].m_vbSkinList.size();
			mesh.m_iBaseVertex += iBaseOffset;
			mesh.m_iNumIndex = m_ExpObject[iObj].m_ibList.size();
			mesh.m_iBaseIndex += iBaseIndex;
			iBaseOffset += mesh.m_iNumVertex;
			iBaseIndex+= mesh.m_iNumIndex;


			// PNCT 버퍼에 한번에 몰아넣음
			std::copy(m_ExpObject[iObj].m_vbSkinList.begin(),
				m_ExpObject[iObj].m_vbSkinList.end(),
				back_inserter(m_VertexSkinData));

			std::copy(m_ExpObject[iObj].m_ibList.begin(),
				m_ExpObject[iObj].m_ibList.end(),
				back_inserter(m_IndexData));

		}


	}


}
bool	SkinObj::Parsing(const TCHAR* FileName)
{
	if (!OpenStream(FileName)) { return false; }

	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s %d %d %d %d %d %d \n"),m_pString,
		&m_Scene.FirstFrame,
		&m_Scene.LastFrame,
		&m_Scene.FrameSpeed,
		&m_Scene.TickPerFrame,
		&m_Scene.iNumMaterial,
		&m_Scene.iNumMesh);
	
	int iNumSubMtl=0;
	int iNumTex;
	m_ExpMtlList.resize(m_Scene.iNumMaterial);
	for (int iMtrl = 0; iMtrl < m_Scene.iNumMaterial; iMtrl++)
	{
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer,_T("%s %d %s %d"), m_pString,
			&m_iTemp, m_pString,
			&iNumSubMtl);
		m_ExpMtlList[iMtrl].submtl.resize(iNumSubMtl);
		if (iNumSubMtl > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < iNumSubMtl; iSubMtrl++)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s %d %s %d\n"),
					m_pString,
					&iSubMtrl,
					m_pString,
					&iNumTex);
			
				m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList.resize(iNumTex);
				for (int iTex = 0; iTex < iNumTex; iTex++)
				{
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
						m_pString,
						&m_iTemp,
						&m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].iSubNo,
						m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].szTextureName);

				}

			}
		}
		else
		{
			

			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s %d\n"), m_pString,
				&iNumTex);
			m_ExpMtlList[iMtrl].m_MapList.resize(iNumTex);
			for (int iTex = 0; iTex < iNumTex; iTex++)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
					m_pString,
					&m_iTemp,
					&m_ExpMtlList[iMtrl].m_MapList[iTex].iSubNo,
					m_ExpMtlList[iMtrl].m_MapList[iTex].szTextureName);

			}

		}

	}
	int iNumTri = 0;
	int iNumVertex = 0;
	int iNumFace = 0;
	int iSubIndex = -1;
	int LastSubIndex = -1;
	int iAniArray[4];
	m_ExpObject.resize(m_Scene.iNumMesh);
	
	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
	{


		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s %d %s %d %s %d %s %d %s %d %s %d \n"),
			m_pString, &m_iTemp,
			m_pString, &m_ExpObject[iObj].m_iRef,
			m_pString, &iAniArray[0],
			m_pString, &iAniArray[1],
			m_pString, &iAniArray[2],
			m_pString, &iAniArray[3]);

		m_ExpObject[iObj].m_AnimTrackPos.resize(iAniArray[0]);
		m_ExpObject[iObj].m_AnimTrackRotate.resize(iAniArray[1]);
		m_ExpObject[iObj].m_AnimTrackScale.resize(iAniArray[2]);
		m_ExpObject[iObj].subMesh.resize(iAniArray[3]);

		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s %s\n"),
			m_ExpObject[iObj].m_szName,
			m_ExpObject[iObj].m_szParentName);

		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("\t%s\n"), m_pString);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
			&m_ExpObject[iObj].m_matWorld._11, &m_ExpObject[iObj].m_matWorld._12, &m_ExpObject[iObj].m_matWorld._13, &m_ExpObject[iObj].m_matWorld._14);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
			&m_ExpObject[iObj].m_matWorld._21, &m_ExpObject[iObj].m_matWorld._22, &m_ExpObject[iObj].m_matWorld._23, &m_ExpObject[iObj].m_matWorld._24);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
			&m_ExpObject[iObj].m_matWorld._31, &m_ExpObject[iObj].m_matWorld._32, &m_ExpObject[iObj].m_matWorld._33, &m_ExpObject[iObj].m_matWorld._34);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
			&m_ExpObject[iObj].m_matWorld._41, &m_ExpObject[iObj].m_matWorld._42, &m_ExpObject[iObj].m_matWorld._43, &m_ExpObject[iObj].m_matWorld._44);


		if (m_ExpObject[iObj].subMesh.size() > 0)
		{

			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s\n"), m_pString);
			for (int iSubMesh = 0; iSubMesh <
				m_ExpObject[iObj].subMesh.size(); iSubMesh++)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%d %d\n"),
					&m_iTemp,
					&iNumFace);
				m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList.resize(iNumFace);
			}


			for (int iSubMesh = 0; iSubMesh <
				m_ExpObject[iObj].subMesh.size(); iSubMesh++)
			{

				if (m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList.size() > 0)
				{
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("%s %d\n"), m_pString,&m_iTemp);
				}
				for (int iFace = 0; iFace < m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList.size(); iFace++)
				{

					int iNumVertex = 3;
					for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
					{

						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].p.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].p.y,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].p.z
						);

						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].n.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].n.y,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].n.z
						);
						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].c.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].c.y,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].c.z,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].c.w
						);
						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].t.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].t.y
						);
						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].i.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].i.y,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].i.z,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].i.w
						);
						_fgetts(m_pBuffer, 256, m_pStream);
						_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].w.x,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].w.y,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].w.z,
							&m_ExpObject[iObj].subMesh[iSubMesh].m_SkinTriList[iFace].v[iVertex].w.w
						);

					}

				}
			}
		}
		else
		{

			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s %d\n"),
				m_pString,
				&iNumFace);
			 m_ExpObject[iObj].m_SkinTriList.resize(iNumFace);



			if (m_ExpObject[iObj].m_SkinTriList.size() > 0)
			{
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s %d\n"), m_pString,&m_ExpObject[iObj].m_iRef);
			}


			for (int iFace = 0; iFace < m_ExpObject[iObj].m_SkinTriList.size(); iFace++)
			{


				int iNumVertex = 3;
				for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
				{


					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].p.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].p.y,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].p.z
						);
			
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].n.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].n.y,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].n.z
					);
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].c.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].c.y,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].c.z,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].c.w
					);
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].t.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].t.y
					);
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].i.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].i.y,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].i.z,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].i.w
					);
					_fgetts(m_pBuffer, 256, m_pStream);
					_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].w.x,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].w.y,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].w.z,
						&m_ExpObject[iObj].m_SkinTriList[iFace].v[iVertex].w.w
					);
				}

			}
		}
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s \n"),m_pString);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackPos.size(); iTrack++)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("\t %d %f %f %f \n"),

				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].iTick,
				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.x,
				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.y,
				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.z);

		}
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackRotate.size(); iTrack++)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("\t %d %f %f %f %f \n"),

				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].iTick,
				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.x,
				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.y,
				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.z,
				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.w);

		}
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackScale.size(); iTrack++)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("\t %d %f %f %f %f %f %f %f\n"),

				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].iTick,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.x,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.y,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.z,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.x,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.y,
				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.z,
				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.w);

		}
	}
	int iNumObj = 0;
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s %d \n"), m_pString,&iNumObj);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	for (int ibone = 0; ibone < iNumObj; ibone++)
	{
		
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"),
			&mat._11,
			&mat._12,
			&mat._13,
			&mat._14,
			&mat._21,
			&mat._22,
			&mat._23,
			&mat._24,
			&mat._31,
			&mat._32,
			&mat._33,
			&mat._34,
			&mat._41,
			&mat._42,
			&mat._43,
			&mat._44);
		m_matBindPoseList.push_back(mat);
	}

}
bool SkinObj::Init()
{
	return true;
}
bool SkinObj::Frame()
{
	float fTime = 0;
	fTime = g_SecondPerFrame * m_Scene.FrameSpeed*m_Scene.TickPerFrame;

	if (fTime >= m_Scene.TickPerFrame)
	{
		fTime = m_Scene.TickPerFrame;
	}
	if (fTime >= m_Scene.TickPerFrame) fTime = m_Scene.TickPerFrame;

	m_fElapseTick += fTime;
	if (m_fElapseTick >= m_Scene.LastFrame*m_Scene.TickPerFrame)
	{
		m_fElapseTick = 0.0f;
	}

 	for (int i = 0; i < m_matBindPoseList.size(); i++)
	{
		D3DXMATRIX mat;
		mat = m_matBindPoseList[i] * m_MatBoneWorld[i];
		D3DXMatrixTranspose(&mat,&mat);
		m_CbBoneWorldData.g_MatBoneWorld[i] = mat;
	}
	
	D3D11_MAPPED_SUBRESOURCE mapResource;
	m_dxHelper.m_pContext->Map(m_pBoneConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	memcpy(mapResource.pData, &m_CbBoneWorldData, sizeof(CBConstBonelWorld));
	m_dxHelper.m_pContext->Unmap(m_pBoneConstBuffer.Get(), 0);
	return true;
}
bool SkinObj::Draw(HMeshSkin& mesh)
{

	if (mesh.m_iNumIndex <= 0) { return false; }

	if (mesh.m_pTexture != NULL)
	{
		m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &mesh.m_pTexture->m_pTextureRV);
	}

	m_dxHelper.m_pContext->DrawIndexed(
		mesh.m_iNumIndex,
		mesh.m_iBaseIndex,
		mesh.m_iBaseVertex);
	return true;
}
bool SkinObj::Render()
{
	m_dxHelper.m_pContext->VSSetConstantBuffers(1, 1, m_pBoneConstBuffer.GetAddressOf());
	m_dxHelper.PreRender();
	
	for (int iObj = 0; iObj < m_ExpObject.size() ;iObj++)
	{
		m_ExpObject[iObj].m_cbData = m_cbData;
		m_ExpObject[iObj].m_matCalculation *= m_matWorld;
	
	/*	D3DXMatrixTranspose(&m_ExpObject[iObj].m_cbData.matWorld,
			&m_ExpObject[iObj].m_matCalculation);*/
		D3DXMatrixTranspose(&m_ExpObject[iObj].m_cbData.matWorld,
			&m_ExpObject[iObj].m_matCalculation);

		m_dxHelper.m_pContext->UpdateSubresource(
			m_dxHelper.m_pConstantBuffer.Get(),
			0, NULL, &m_ExpObject[iObj].m_cbData, 0, 0);

		if (m_ExpObject[iObj].subMesh.size() > 0)
		{
			for (int iSub = 0; iSub < m_ExpObject[iObj].subMesh.size(); iSub++)
			{
				Draw(m_ExpObject[iObj].subMesh[iSub]);
			}
		}
		else
		{
				Draw(m_ExpObject[iObj]);
		}

	}
	return true;
}
bool SkinObj::Release()
{
	return true;
}

bool	SkinObj::OpenStream(const TCHAR* FileName)
{
	m_pStream = _tfopen(FileName, _T("rt"));
	if (m_pStream==nullptr)
	{ 
		return false;
	}
	return true;
}
bool	SkinObj::CloseStream() 
{
	fclose(m_pStream);
	return true;
}