#include "xAseObj.h"
bool    xAseObj::AddVertex(int iObj, int iFace, int iVertex,Mesh& mesh)
{
	PNCT_VERTEX v;
	int index;
	int iSubMNum = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].SubMtrl;
	// p, n, c, t
	index = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].i[iVertex];
	v.p = m_Parser.m_ObjList[iObj]->m_VertexPosList[index];
	D3DXVec3TransformCoord(&v.p, &v.p, &mesh.m_matInverseWorld);

	v.n = m_Parser.m_ObjList[iObj]->m_FaceNoramlList[iFace].vn[iVertex];
	v.c = D3DXVECTOR4(1, 1, 1, 1);
	if (m_Parser.m_ObjList[iObj]->m_ColorVertexList.size() > 0)
	{
		index = m_Parser.m_ObjList[iObj]->m_ColorFaseList[iFace].i[iVertex];
		v.c.x = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].x;
		v.c.y = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].y;
		v.c.z = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].z;
		v.c.w = 1.0f;
	}
	index = m_Parser.m_ObjList[iObj]->m_UVFacesList[iFace].i[iVertex];
	v.t = m_Parser.m_ObjList[iObj]->m_UVList[index];
	//서브매쉬가 존재할 때의 조건
	if (mesh.subMesh.size() > 0)
	{
		if (iSubMNum >= 255) iSubMNum = 0;
		mesh.subMesh[iSubMNum].PNCTlist.push_back(v);
	}
	else
	{
		m_PNCTBuffer.push_back(v);
	}
	return true;
}
void	xAseObj::Convert()
{
	int iBaseOffset = 0;
	
	m_Scene = m_Parser.m_SCeneInfo;
	for (int iObj = 0; iObj < m_Parser.m_ObjList.size(); iObj++)
	{
		Mesh mesh;
		mesh.m_AnimTrackPos.assign(m_Parser.m_ObjList[iObj]->m_AnimTrackPos.begin(),
									m_Parser.m_ObjList[iObj]->m_AnimTrackPos.end());

		mesh.m_AnimTrackRotate.assign(m_Parser.m_ObjList[iObj]->m_AnimTrackRotate.begin(),
										m_Parser.m_ObjList[iObj]->m_AnimTrackRotate.end());
		mesh.m_AnimTrackScale.assign(m_Parser.m_ObjList[iObj]->m_AnimTrackScale.begin(),
										m_Parser.m_ObjList[iObj]->m_AnimTrackScale.end());



		int iRef = m_Parser.m_ObjList[iObj]->m_Ref;
		
		//레퍼런싱한 메테리얼이없을경우의 조건
		if (iRef >= 0)
		{
			if (m_Parser.m_MaterialList[iRef].submtl.size() > 0)
			{
				int iSubMtrl = m_Parser.m_MaterialList[iRef].submtl.size();
				mesh.subMesh.resize(iSubMtrl);
				for (int i = 0; i < iSubMtrl; i++)
				{
					mesh.subMesh[i].m_iTexIndex = I_Texture.Add(m_dxHelper.m_pd3dDevice,
						mtw(m_Parser.m_MaterialList[iRef].submtl[i].TextureName).c_str(),
						L"../../data/Obj/");

					mesh.subMesh[i].m_pTexture = I_Texture.GetPtr(mesh.subMesh[i].m_iTexIndex);
				}
			}
			else
			{
				mesh.m_iTexIndex = I_Texture.Add(m_dxHelper.m_pd3dDevice,
					mtw(m_Parser.m_MaterialList[iRef].TextureName).c_str(),
					L"../../data/Obj/");

				mesh.m_pTexture = I_Texture.GetPtr(mesh.m_iTexIndex);
				
			}
		}

		//파일에 있는 월드행렬의 역행렬로 오브젝트를 원위치로 돌려놓고 다시 월드행렬로 위치시킴
		D3DXMatrixIdentity(&mesh.m_matWorld);
		mesh.m_matWorld = m_Parser.m_ObjList[iObj]->m_matWorld;
		
	
		
		
		D3DXMatrixInverse(&mesh.m_matInverseWorld, NULL, &mesh.m_matWorld);

		PNCT_VERTEX v;
		int index;
		// 데이터 복사
		for (int iFace = 0; iFace < m_Parser.m_ObjList[iObj]->iNumFace; iFace++)
		{
			for (int iVertex = 0; iVertex < 3; iVertex++)
			{
				AddVertex(iObj, iFace, iVertex, mesh);
			}
		
		}

		if (mesh.subMesh.size()>0)
		{
			for (int i = 0; i < mesh.subMesh.size(); i++)
			{
				mesh.subMesh[i].m_iNumVertex = mesh.subMesh[i].PNCTlist.size();
				mesh.subMesh[i].m_iBaseVertex += iBaseOffset;
				iBaseOffset += mesh.subMesh[i].m_iNumVertex;

				// PNCT 버퍼에 한번에 몰아넣음
				std::copy(mesh.subMesh[i].PNCTlist.begin(),
					mesh.subMesh[i].PNCTlist.end(),
					back_inserter(m_PNCTBuffer));

			}

		}
		else
		{
			mesh.m_iNumVertex = m_Parser.m_ObjList[iObj]->iNumFace * 3;
			mesh.m_iBaseVertex += iBaseOffset;
			iBaseOffset += mesh.m_iNumVertex;

		}

		m_MeshList.push_back(mesh);

	}
	m_Parser.Release();

}
bool xAseObj::Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile)
{

	m_dxHelper.m_pd3dDevice = pdvice;
	m_dxHelper.m_pContext = pContext;

	m_Parser.LoadBuffer(LoadFile);
	int iType = -1;


	while ((iType = m_Parser.SearchTokenArray(AseSection)) >= 0)
	{
		switch (iType)
		{
		case SCENE:
			m_Parser.LoadScene();
			break;
		case MATERIAL_LIST:
			m_Parser.LoadMateRial();
			break;
		case HELPER_OBJECT:
		case GEOMOBJECT:
			m_Parser.LoadGeomObj();
			break;
		default:
			break;
		}
	}

	Convert();
	Create(pdvice, pContext, L"../../data/shader/ColorBlend.txt", L"../../data/Resource/Galloper.bmp");
	return true;
}

HRESULT xAseObj::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_dxHelper.m_iVertexSize = sizeof(PNCT_VERTEX);
	m_VertexData.resize(m_PNCTBuffer.size());

	for (int iVertex = 0; iVertex < m_PNCTBuffer.size(); iVertex++)
	{
		m_VertexData[iVertex] = m_PNCTBuffer[iVertex];
	}

	return hr;
}
HRESULT xAseObj::CreateIndexData()
{
	HRESULT hr = S_OK;

	return hr;
}

bool xAseObj::Init()
{
	return true;
}
bool xAseObj::Frame()
{
	float fTime = 0;
	fTime += g_SecondPerFrame * m_Scene.FrameSpeed*m_Scene.TickPerFrame;
	

	if (fTime >= m_Scene.TickPerFrame) fTime = m_Scene.TickPerFrame;

	m_fElapseTick += fTime;
	if (m_fElapseTick>=m_Scene.LastFrame*m_Scene.TickPerFrame)
	{
		m_fElapseTick = 0.0f;
	}
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vScale(1,1,1);
	D3DXMATRIX matRotation;
	D3DXMATRIX matScaleRotation;
	D3DXMATRIX matInverseScaleRotation;
	D3DXMATRIX matScale;

	D3DXQUATERNION Quat;

	

	D3DXQuaternionIdentity(&Quat);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScaleRotation);
	D3DXMatrixIdentity(&matScale);
	for (int iObj = 0; iObj <m_MeshList.size(); iObj++)
	{
	
		D3DXMatrixIdentity(&m_MeshList[iObj].m_Calculation);
		vPos.x = m_MeshList[iObj].m_matWorld._41;
		vPos.y = m_MeshList[iObj].m_matWorld._42;
		vPos.z = m_MeshList[iObj].m_matWorld._43;

		
		if (m_MeshList[iObj].m_AnimTrackPos.size()>0)
		{
			AnimTrack start, end;

			for (int i = 0; i < m_MeshList[iObj].m_AnimTrackPos.size(); i++)
			{
				if (m_MeshList[iObj].m_AnimTrackPos[i].iTick <= m_fElapseTick)
				{
					start = m_MeshList[iObj].m_AnimTrackPos[i];
				}
				else
				{
					end = m_MeshList[iObj].m_AnimTrackPos[i];
					break;
				}
			}

			float step = end.iTick-start.iTick ;

			float t = (m_fElapseTick - start.iTick) / step;
			D3DXVec3Lerp(&vPos, &start.p, &end.p, t);
		}
		if (m_MeshList[iObj].m_AnimTrackRotate.size() > 0)
		{
			AnimTrack start, end;

			start = m_MeshList[iObj].m_AnimTrackRotate[0];
			for (int i = 0; i < m_MeshList[iObj].m_AnimTrackRotate.size(); i++)
			{
				if (m_MeshList[iObj].m_AnimTrackRotate[i].iTick <= m_fElapseTick)
				{
					start = m_MeshList[iObj].m_AnimTrackRotate[i];
				}
				if (m_MeshList[iObj].m_AnimTrackRotate[i].iTick > m_fElapseTick)
				{	
					end = m_MeshList[iObj].m_AnimTrackRotate[i];
					break;
				}
			}

			float step = end.iTick- start.iTick ;

			float t = (m_fElapseTick - start.iTick) / step;
			D3DXQuaternionSlerp(&Quat, &start.q, &end.q, t);
			D3DXMatrixRotationQuaternion(&matRotation, &Quat);
	
		
		}
		if (m_MeshList[iObj].m_AnimTrackScale.size() > 0)
		{
			AnimTrack start, end;

			
			for (int i = 0; i < m_MeshList[iObj].m_AnimTrackScale.size(); i++)
			{
				if (m_MeshList[iObj].m_AnimTrackScale[i].iTick <= m_fElapseTick)
				{
					start = m_MeshList[iObj].m_AnimTrackScale[i];
				}
				if (m_MeshList[iObj].m_AnimTrackScale[i].iTick > m_fElapseTick)
				{
					end = m_MeshList[iObj].m_AnimTrackScale[i];
					break;
				}
			}

			float step = end.iTick - start.iTick;

			float t = (m_fElapseTick - start.iTick) / step;
			
			D3DXQuaternionSlerp(&Quat, &start.q, &end.q, t);
			D3DXMatrixRotationQuaternion(&matScaleRotation, &Quat);
			D3DXMatrixInverse(&matInverseScaleRotation, NULL, &matScaleRotation);

			D3DXVec3Lerp(&vPos, &start.p, &end.p, t);
			D3DXMatrixScaling(&matScale, start.p.x, start.p.y, start.p.z);
			
			matScale = matInverseScaleRotation * matScale*matScaleRotation;

		}


	
		m_MeshList[iObj].m_Calculation = matScale* matRotation;
		m_MeshList[iObj].m_Calculation._41 = vPos.x;
		m_MeshList[iObj].m_Calculation._42 = vPos.y;
		m_MeshList[iObj].m_Calculation._43 = vPos.z;
	}
	
	return true;
}
bool xAseObj::Render()
{
	m_dxHelper.PreRender();
	for (int iObj = 0; iObj < m_MeshList.size(); iObj++)
	{
		m_MeshList[iObj].m_cbData = m_cbData;
		m_MeshList[iObj].m_Calculation *= m_matWorld;
		D3DXMatrixTranspose(&m_MeshList[iObj].m_cbData.matWorld,
			&m_MeshList[iObj].m_Calculation);
		m_dxHelper.m_pContext->UpdateSubresource(
			m_dxHelper.m_pConstantBuffer.Get(),
			0, NULL, &m_MeshList[iObj].m_cbData, 0, 0);

		if (m_MeshList[iObj].subMesh.size() > 0)
		{
			for (int iSub = 0; iSub < m_MeshList[iObj].subMesh.size(); iSub++)
			{
				if (m_MeshList[iObj].subMesh[iSub].m_pTexture != NULL)
				{

					m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &m_MeshList[iObj].subMesh[iSub].m_pTexture->m_pTextureRV);
					m_dxHelper.m_pContext->Draw(m_MeshList[iObj].subMesh[iSub].m_iNumVertex,
						m_MeshList[iObj].subMesh[iSub].m_iBaseVertex);
				}
				else
				{
					m_dxHelper.m_pContext->Draw(m_MeshList[iObj].subMesh[iSub].m_iNumVertex,
						m_MeshList[iObj].subMesh[iSub].m_iBaseVertex);
				}
			
			}

		}
		else
		{
			if (m_MeshList[iObj].m_pTexture!=NULL)
			{
				m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &m_MeshList[iObj].m_pTexture->m_pTextureRV);
				m_dxHelper.m_pContext->Draw(m_MeshList[iObj].m_iNumVertex,
					m_MeshList[iObj].m_iBaseVertex);
			}
			else
			{
				m_dxHelper.m_pContext->Draw(m_MeshList[iObj].m_iNumVertex,
					m_MeshList[iObj].m_iBaseVertex);
			}

		}

	}
	return true;
}
bool xAseObj::Release()
{
	return true;
}
xAseObj::xAseObj()
{
}


xAseObj::~xAseObj()
{
}
