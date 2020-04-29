#include "xAseObj.h"

void	xAseObj::Convert()
{
	int iBaseOffset = 0;
	for (int iObj= 0; iObj < m_Parser.m_ObjList.size(); iObj++)
	{
		Mesh mesh;
		int iRef = m_Parser.m_ObjList[iObj]->m_Ref;

		if (m_Parser.m_MaterialList[iRef].submtl.size()>0)
		{
			int iSubMtrl = m_Parser.m_MaterialList[iRef].submtl.size();
			mesh.subMesh.resize(iSubMtrl);
			for ( int i = 0; i < iSubMtrl; i++)
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


		D3DXMatrixIdentity(&mesh.m_matWorld);
		mesh.m_matWorld = m_Parser.m_ObjList[iObj]->m_matWorld;
	
		D3DXMATRIX matInverse;
		D3DXMatrixInverse(&matInverse, NULL, &mesh.m_matWorld);

		PNCT_VERTEX v;
		int index;
		for (int iFace = 0; iFace < m_Parser.m_ObjList[iObj]->iNumFace; iFace++)
		{
			int iSubMNum = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].SubMtrl;
			// p, n, c, t
			index = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].i0;
			v.p = m_Parser.m_ObjList[iObj]->m_VertexPosList[index];
			D3DXVec3TransformCoord(&v.p, &v.p, &matInverse);

			v.n = m_Parser.m_ObjList[iObj]->m_FaceNoramlList[iFace].vn[0];
			v.c = D3DXVECTOR4(1, 1, 1, 1);
			if (m_Parser.m_ObjList[iObj]->m_ColorVertexList.size() > 0)
			{
				index = m_Parser.m_ObjList[iObj]->m_ColorFaseList[iFace].i0;
				v.c.x = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].x;
				v.c.y = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].y;
				v.c.z = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].z;
				v.c.w = 1.0f;
			}
			index = m_Parser.m_ObjList[iObj]->m_UVFacesList[iFace].i0;
			v.t = m_Parser.m_ObjList[iObj]->m_UVList[index];
			if (mesh.subMesh.size()>0)
			{
				mesh.subMesh[iSubMNum].PNCTlist.push_back(v);
			}
			else
			{
				m_PNCTBuffer.push_back(v);
			}
			


			// v1
			index = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].i1;
			v.p = m_Parser.m_ObjList[iObj]->m_VertexPosList[index];
			D3DXVec3TransformCoord(&v.p, &v.p, &matInverse);
			v.n = m_Parser.m_ObjList[iObj]->m_FaceNoramlList[iFace].vn[1];
			v.c = D3DXVECTOR4(1, 1, 1, 1);
			if (m_Parser.m_ObjList[iObj]->m_ColorVertexList.size() > 0)
			{
				index = m_Parser.m_ObjList[iObj]->m_ColorFaseList[iFace].i1;
				v.c.x = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].x;
				v.c.y = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].y;
				v.c.z = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].z;
				v.c.w = 1.0f;
			}
			index = m_Parser.m_ObjList[iObj]->m_UVFacesList[iFace].i1;
			v.t = m_Parser.m_ObjList[iObj]->m_UVList[index];
			if (mesh.subMesh.size() > 0)
			{
				mesh.subMesh[iSubMNum].PNCTlist.push_back(v);
			}
			else
			{
				m_PNCTBuffer.push_back(v);
			}

			index = m_Parser.m_ObjList[iObj]->m_FacesList[iFace].i2;
			v.p = m_Parser.m_ObjList[iObj]->m_VertexPosList[index];
			D3DXVec3TransformCoord(&v.p, &v.p, &matInverse);
			v.n = m_Parser.m_ObjList[iObj]->m_FaceNoramlList[iFace].vn[2];
			v.c = D3DXVECTOR4(1, 1, 1, 1);
			if (m_Parser.m_ObjList[iObj]->m_ColorVertexList.size() > 0)
			{
				index = m_Parser.m_ObjList[iObj]->m_ColorFaseList[iFace].i2;
				v.c.x = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].x;
				v.c.y = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].y;
				v.c.z = m_Parser.m_ObjList[iObj]->m_ColorVertexList[index].z;
				v.c.w = 1.0f;
			}
			index = m_Parser.m_ObjList[iObj]->m_UVFacesList[iFace].i2;
			v.t = m_Parser.m_ObjList[iObj]->m_UVList[index];
			if (mesh.subMesh.size() > 0)
			{
				mesh.subMesh[iSubMNum].PNCTlist.push_back(v);
			}
			else
			{
				m_PNCTBuffer.push_back(v);
			}
		}

		if (m_Parser.m_MaterialList[iRef].submtl.size() > 0)
		{
			for (int  i = 0; i < mesh.subMesh.size(); i++)
			{
				mesh.subMesh[i].m_iNumVertex = mesh.subMesh[i].PNCTlist.size();
				mesh.subMesh[i].m_iBaseVertex += iBaseOffset;
				iBaseOffset += mesh.subMesh[i].m_iNumVertex;

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


		 while ((iType = m_Parser.SearchTokenArray(AseSection))>=0)
		 {
			 switch (iType)
			 {
				case SCENE:
					m_Parser.LoadScene();
					break;
				case MATERIAL_LIST:
					m_Parser.LoadMateRial();
					break;
				case GEOMOBJECT:
					m_Parser.LoadGeomObj();
					break;
				default:
				 break;
			 }
		 }

		 Convert();
		 Create(pdvice, pContext, L"../../data/shader/ColorBlend.txt",L"../../data/Resource/Galloper.bmp");
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
	HRESULT hr=S_OK;

	return hr;
}

bool xAseObj::Init()
{
	return true;
}
bool xAseObj::Frame()
{
	return true;
}
bool xAseObj::Render()
{
	m_dxHelper.PreRender();
	for (int iObj = 0; iObj < m_MeshList.size(); iObj++)
	{
		m_MeshList[iObj].m_cbData = m_cbData;
		D3DXMatrixTranspose(&m_MeshList[iObj].m_cbData.matWorld,
			&m_MeshList[iObj].m_matWorld);
		m_dxHelper.m_pContext->UpdateSubresource(
			m_dxHelper.m_pConstantBuffer.Get(),
			0, NULL, &m_MeshList[iObj].m_cbData, 0, 0);

		if (m_MeshList[iObj].subMesh.size()>0)
		{
			for (int  iSub = 0; iSub < m_MeshList[iObj].subMesh.size(); iSub++)
			{
				m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &m_MeshList[iObj].subMesh[iSub].m_pTexture->m_pTextureRV);
				m_dxHelper.m_pContext->Draw(m_MeshList[iObj].subMesh[iSub].m_iNumVertex,
					m_MeshList[iObj].subMesh[iSub].m_iBaseVertex);
			}
		
		}
		else
		{
			m_dxHelper.m_pContext->PSSetShaderResources(0, 1, &m_MeshList[iObj].m_pTexture->m_pTextureRV);
			m_dxHelper.m_pContext->Draw(m_MeshList[iObj].m_iNumVertex,
				m_MeshList[iObj].m_iBaseVertex);
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
