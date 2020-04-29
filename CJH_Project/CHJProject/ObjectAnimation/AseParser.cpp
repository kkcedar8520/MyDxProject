#include "AseParser.h"
#include"TextureMgr.h"
template<typename OutputIterator>
void  AseParser::Tokenize(C_STR text, C_STR token, OutputIterator DataList)
{
	auto start = 0;
	auto stop = 0;
	auto TotalByte = text.length();

	for (start = text.find_first_not_of(token);
		0 <= start && start < TotalByte; start = text.find_first_not_of(token, stop + 1))
	{
		stop = text.find_first_of(token, start);
		if (stop<0 || stop>TotalByte)
		{
			stop = TotalByte;
		}
		*DataList++ = text.substr(start, stop - start);
	}
}
void  AseParser::BeginToken()
{
	C_STR DataBuffer = m_pMashData;
	Tokenize(DataBuffer, "*", back_inserter(m_DataList));

}
bool AseParser::LoadBuffer(const TCHAR* LoadFile)
{
	m_Handle = CreateFile(LoadFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LARGE_INTEGER FileSize;
	if (m_Handle != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(m_Handle, &FileSize);
		m_pMashData = new CHAR[FileSize.QuadPart];
		DWORD dataReadByte;
		if (!ReadFile(m_Handle, m_pMashData, FileSize.QuadPart, &dataReadByte, nullptr))
		{
			delete[]  m_pMashData;
			CloseHandle(m_Handle);
			return false;
		}
	}
	BeginToken();
	CloseHandle(m_Handle);
	delete[] m_pMashData;

	return true;
}
int AseParser::SearchTokenArray(vector<string>& secction)
{
	int iRet = -1;
	while (1)
	{
		
		if (GetNextLine() < 0)
		{
			return iRet;
		}
		for (int iType = 0; iType < secction.size(); iType++)
		{
			if (strstr(m_MBTokcenData.c_str(), secction[iType].c_str()) != nullptr)
			{
				iRet = iType;
				return iRet;
			}
		}

	}
	return iRet;
}
int AseParser::GetNextLine()
{
	m_iListindex++;
	if (m_iListindex >= m_DataList.size())
	{
		m_iListindex = m_DataList.size();
		return -1;
	}
	m_MBTokcenData = m_DataList[m_iListindex];
	return  m_iListindex;
}
int AseParser::GetData(string FindStr, void* pData, int iType,bool bLoop)
{
	int iLine = -1;
	char szTemp[255] = { 0, };
	if ((iLine = FindString(FindStr,bLoop)) > 0)
	{

		switch (iType)
		{
		case NULL_DATA:
		{}break;
		case INT_DATA:
		{
			sscanf_s(m_DataList[iLine].c_str(), "%s%d", szTemp, _countof(szTemp), pData);
			break;
		}
		case STRING_DATA:
		{

			string cToken = "\"";
			string name = m_DataList[iLine];
			size_t start = name.find_first_of(cToken) + 1;
			size_t end = name.find_last_of(cToken, name.length());
			strcpy((CHAR*)pData,
				name.substr(start, end - start).c_str());
			break;
		}
		case VECTOR_DATA:
		{
			sscanf_s(m_DataList[iLine].c_str(), "%s%f%f%f", szTemp, _countof(szTemp),
				&((D3DXVECTOR3*)pData)->x,
				&((D3DXVECTOR3*)pData)->z,
				&((D3DXVECTOR3*)pData)->y);
			break;
		}
		case VERTEX_DATA:
		{
			int iTemp = 0;

			sscanf_s(m_DataList[iLine].c_str(), "%s%d%f%f%f", szTemp, _countof(szTemp), &iTemp,
				&((D3DXVECTOR3*)pData)->x,
				&((D3DXVECTOR3*)pData)->z,
				&((D3DXVECTOR3*)pData)->y);
			break;
		}
		case INDEX_DATA:
		{

			sscanf_s(m_DataList[iLine].c_str(), "%s%s%s%d%s%d%s%d",
				szTemp, _countof(szTemp),
				szTemp, _countof(szTemp),
				szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[0],
				&szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[2],
				&szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[1]);
			break;
		}

		default:
			break;
		}
	}
	return iLine;
}
int	AseParser::GetLineData(void* pData, int iType)
{
	char szTemp[255] = { 0, };
	switch (iType)
	{
		case NULL_DATA:
		{}break;
		case INT_DATA:
		{
			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d", szTemp, _countof(szTemp), pData);
			break;
		}
		case STRING_DATA:
		{

			string cToken = "\"";
			string name = m_DataList[m_iListindex];
			size_t start = name.find_first_of(cToken) + 1;
			size_t end = name.find_last_of(cToken, name.length());
			strcpy((char*)pData,
				name.substr(start, end - start).c_str());
			break;
		}
		case VECTOR_DATA:
		{
			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%f%f%f", szTemp, _countof(szTemp),
				&((D3DXVECTOR3*)pData)->x,
				&((D3DXVECTOR3*)pData)->z,
				&((D3DXVECTOR3*)pData)->y);
			break;
		}
		case VERTEX_DATA:
		{
			int iTemp = 0;

			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d%f%f%f", szTemp, _countof(szTemp), &iTemp,
				&((D3DXVECTOR3*)pData)->x,
				&((D3DXVECTOR3*)pData)->z,
				&((D3DXVECTOR3*)pData)->y);
			break;
		}
		case INDEX_DATA:
		{

			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%s%s%d%s%d%s%d",
				szTemp, _countof(szTemp),
				szTemp, _countof(szTemp),
				szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[0],
				&szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[2],
				&szTemp, _countof(szTemp),
				&((aseINDEX*)pData)->i[1]);
			break;
		}

		default:
			break;
	}
	return 1;
}
int AseParser::FindString(string szFind,bool bLoop)
{

	m_LastIndex = m_iListindex;
	if (bLoop)
	{


		while (strstr(m_MBTokcenData.c_str(), szFind.c_str()) == nullptr)
		{

			if (GetNextLine() == -1)
			{
				return -1;
			}

		}
		return m_iListindex;
	}
	else
	{
		if (strstr(m_MBTokcenData.c_str(), szFind.c_str()) == nullptr)
		{
			return -1;
		}
		else
		{
			return m_iListindex;
		}
	}
	return -1;
}

bool  AseParser::LoadScene()
{

	if (GetData("SCENE ") > 0)
	{
		GetData("SCENE_FIRSTFRAME", &m_SCeneInfo.FirstFrame, INT_DATA);
		GetData("SCENE_LASTFRAME", &m_SCeneInfo.LastFrame, INT_DATA);
		GetData("SCENE_FRAMESPEED", &m_SCeneInfo.FrameSpeed, INT_DATA);
		GetData("SCENE_TICKSPERFRAME", &m_SCeneInfo.TickPerFrame, INT_DATA);
	}

	return true;
}
bool AseParser::LoadMateRial()
{
	if (GetData("MATERIAL_LIST"))
	{
		GetData("MATERIAL_COUNT", &m_SCeneInfo.iMaterialNum, INT_DATA);
		GetData("MATERIAL ", nullptr, NULL);
		for (int iMtrl = 0; iMtrl < m_SCeneInfo.iMaterialNum; iMtrl++)
		{
			Mtrl Material;
			
			if (LoadMateRial(&Material))
			{
				m_MaterialList.push_back(Material);
			}

		}

	}
	return true;
}
bool AseParser::LoadMateRial(Mtrl* pMtrl)
{
	int iType;



	while ((iType = SearchTokenArray(MaterialSection)) >= 0)
	{

		switch (iType)
		{
			case NEWMATERIAL:
			case SUBMATERIAL:
			{
				return true;
			}
			case GEOMOBJ:
			{
				return true;
			}
			case HELPEROBJ:
			{
				--m_iListindex;
				return true;
			}
		
			case NUMSUBMTLS:
			{
				int iSub;
				GetData("NUMSUBMTLS", &iSub, INT_DATA);
				for (int iSubMaterial = 0; iSubMaterial < iSub; iSubMaterial++)
				{
					Mtrl SubMtrl;
					GetNextLine();
					GetNextLine();
					if (LoadMateRial(&SubMtrl))
					{
						pMtrl->submtl.push_back(SubMtrl);
					}
				}
				return true;
			}
			case MAPNAME:
			{
				if (LoadTexture(pMtrl))
				{
					return true;
				}
				return false;
			}
			default:
			{
				break;
			}
		}
	}
	return false;
}
bool AseParser::LoadGeomObj()
{
	int iType = -1;
	int iObjNum = 0;

	while ((iType = SearchTokenArray(GeomObjSection)) >= 0)
	{
		switch (iType)
		{
		case NODE_NAME:
		{
			auto obj = make_shared<GeomObj>();

			m_ObjList.push_back(obj);
			iObjNum = m_ObjList.size() - 1;
			GetData("NODE_NAME ",&m_ObjList[iObjNum]->szName,STRING_DATA);
		}break;
		case NODE_PARENT_NAME:
		{
			GetData("NODE_PARENT ", &m_ObjList[iObjNum]->szParentName, STRING_DATA);
			
		}
		case NODE_TM:
		{
			GetData("NODE_TM ");
		}
		case TM_ROW:
		{
			GetData("TM_ROW0 ", m_ObjList[iObjNum]->m_matWorld.m[0], VECTOR_DATA);
			GetData("TM_ROW1 ", m_ObjList[iObjNum]->m_matWorld.m[2], VECTOR_DATA);
			GetData("TM_ROW2 ", m_ObjList[iObjNum]->m_matWorld.m[1], VECTOR_DATA);
			GetData("TM_ROW3 ", m_ObjList[iObjNum]->m_matWorld.m[3], VECTOR_DATA);
		}break;
		case MESH:
		{
			GetData("MESH_NUMVERTEX ", &m_ObjList[iObjNum]->iNumVertex, INT_DATA);
			GetData("MESH_NUMFACES ", &m_ObjList[iObjNum]->iNumFace, INT_DATA);
			m_ObjList[iObjNum]->m_VertexPosList.resize(m_ObjList[iObjNum]->iNumVertex);
			m_ObjList[iObjNum]->m_FacesList.resize(m_ObjList[iObjNum]->iNumFace);
			GetData("MESH_VERTEX_LIST ");
			GetNextLine();
			for (int iVertex = 0; iVertex < m_ObjList[iObjNum]->iNumVertex; iVertex++)
			{
				GetData("MESH_VERTEX ", &m_ObjList[iObjNum]->m_VertexPosList[iVertex], VERTEX_DATA);
				GetNextLine();
			}
			GetData("MESH_FACE_LIST ");
			GetNextLine();

			for (int iFace = 0; iFace < m_ObjList[iObjNum]->iNumFace; iFace++)
			{
				GetData("MESH_FACE ", &m_ObjList[iObjNum]->m_FacesList[iFace], INDEX_DATA);
				GetData("MESH_MTLID", &m_ObjList[iObjNum]->m_FacesList[iFace].SubMtrl, INT_DATA);
				GetNextLine();
			}
			GetData("MESH_NUMTVERTEX ", &m_ObjList[iObjNum]->iNumTVertex, INT_DATA);
			m_ObjList[iObjNum]->m_UVList.resize(m_ObjList[iObjNum]->iNumTVertex);

			GetData("MESH_TVERTLIST");
			GetNextLine();
			GetUVData(m_iListindex, m_ObjList[iObjNum]->m_UVList);

			GetData("MESH_NUMTVFACES", &m_ObjList[iObjNum]->iNumTFace, INT_DATA);
			m_ObjList[iObjNum]->m_UVFacesList.resize(m_ObjList[iObjNum]->iNumTFace);
			GetTFaceData(m_iListindex, m_ObjList[iObjNum]->m_UVFacesList);




			GetData("MESH_NUMCVERTEX", &m_ObjList[iObjNum]->iNumCVertex, INT_DATA);
			if (&m_ObjList[iObjNum]->iNumCVertex > 0)
			{
			}


			GetData("MESH_NORMALS");
			m_ObjList[iObjNum]->m_FaceNoramlList.resize(m_ObjList[iObjNum]->iNumFace);
			GetNextLine();
			GetFaceNormal(m_iListindex, m_ObjList[iObjNum]->m_FaceNoramlList);
		}break;
		case MATERIAL_REF:
		{
			GetData("MATERIAL_REF", &m_ObjList[iObjNum]->m_Ref, INT_DATA);
			break;
		}
		case TM_ANIMATION:
		{
 			GetAnimInfo();
		}

		}

	}
	return true;
}
void AseParser::GetUVData(int iLine, vector<D3DXVECTOR2>&UVList)
{
	char szTemp[256] = { 0 };

	for (int i = 0; i < UVList.size(); i++)
	{
		int iTemp = 0;

		sscanf_s(m_DataList[m_iListindex].c_str(), "%s %d %f%f", szTemp, _countof(szTemp), &iTemp,
			&UVList[i].x,
			&UVList[i].y);
		UVList[i].y = 1 - UVList[i].y;
		GetNextLine();
	}
}

void AseParser::GetTFaceData(int iLine, vector<aseINDEX>&UVFacesList)
{

	GetData("MESH_TFACELIST");
	GetNextLine();

	char szTemp[256] = { 0 };

	for (int i = 0; i < UVFacesList.size(); i++)
	{
		int iTemp = 0;

		sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d%d%d%d", szTemp, _countof(szTemp), &iTemp,
			&UVFacesList[i].i[0],
			&UVFacesList[i].i[2],
			&UVFacesList[i].i[1]);
		GetNextLine();
	}
}

void AseParser::GetFaceNormal(int iLine, vector<FaceNormal>&FaceNormalList)
{
	for (int i = 0; i < FaceNormalList.size(); i++)
	{
		int iTemp = 0;

		GetData("MESH_VERTEXNORMAL", &FaceNormalList[i].vn[0], VERTEX_DATA);
		GetNextLine();

		GetData("MESH_VERTEXNORMAL", &FaceNormalList[i].vn[2], VERTEX_DATA);
		GetNextLine();

		GetData("MESH_VERTEXNORMAL", &FaceNormalList[i].vn[1], VERTEX_DATA);
		GetNextLine();

	}
}
bool AseParser::LoadTexture(Mtrl* pMtrl)
{

	int iType;
	char TempBuffer[256] = { 0, };
	while ((iType = SearchTokenArray(TextureSection)) >= 0)
	{
		switch (iType)
		{
		case SUBNO:
		{
			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d", TempBuffer, _countof(TempBuffer), &pMtrl->Subno);
		}break;
		case TEXTURE:
		{
			GetData("BITMAP", TempBuffer, STRING_DATA);
			pMtrl->TextureName = TempBuffer;//텍스트 매니저 쓰도록


		}break;
		default:
		{
			--m_iListindex;
			return true;;
		}
		}
	}
	return false;
}

bool AseParser::GetAnimInfo()
{
		AnimTrack Track;
		
	char szTemp[256] = { 0 };
	int iObj = m_ObjList.size() - 1;
	GetNextLine();
	GetNextLine();
	if (GetData("CONTROL_POS_TRACK ",nullptr,NULL_DATA,false)>0)
	{


		while (1)
		{
			ZeroMemory(&Track, sizeof(AnimTrack));
			GetNextLine();

			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d%f%f%f", szTemp, _countof(szTemp),
				&Track.iTick,
				&Track.p.x,
				&Track.p.z,
				&Track.p.y);
			m_ObjList[iObj]->m_AnimTrackPos.push_back(Track);
			if (strstr(m_MBTokcenData.c_str(), "}"))
			{
				break;
			}

		}
	}

	if (GetData("CONTROL_ROT_TRACK ", nullptr, NULL_DATA, false)>0)
	{
		D3DXQUATERNION QBefore;
		D3DXQuaternionIdentity(&QBefore);
		while (1)
		{
			ZeroMemory(&Track, sizeof(AnimTrack));
			GetNextLine();
	
			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d%f%f%f%f", szTemp, _countof(szTemp),
				&Track.iTick,
				&Track.p.x,
				&Track.p.z,
				&Track.p.y,
				&Track.q.w);
			
			D3DXQuaternionRotationAxis(&Track.q, &Track.p, Track.q.w);
			//회전 데이터는 누적 된 값이 아니기 때문에 누적시켜야한다
			Track.q = Track.q*QBefore;
			QBefore = Track.q;
			m_ObjList[iObj]->m_AnimTrackRotate.push_back(Track);

			if (strstr(m_MBTokcenData.c_str(), "}"))
			{
				break;
			}

		}
	}
	if (GetData("CONTROL_SCALE_TRACK ", nullptr, NULL_DATA, false)>0)
	{
		
		D3DXVECTOR3 axis;
		while (1)
		{
			ZeroMemory(&Track, sizeof(AnimTrack));
			GetNextLine();

			sscanf_s(m_DataList[m_iListindex].c_str(), "%s%d%f%f%f%f%f%f%f", szTemp, _countof(szTemp),
				&Track.iTick,
				&Track.p.x,
				&Track.p.z,
				&Track.p.y,
				&axis.x,
				&axis.z,
				&axis.y,
				&Track.q.w);

			D3DXQuaternionRotationAxis(&Track.q, &axis, Track.q.w);

			m_ObjList[iObj]->m_AnimTrackScale.push_back(Track);

			if (strstr(m_MBTokcenData.c_str(), "}"))
			{
				break;
			}

		}
	}
	return true;
}
int AseParser::GetParentIndex(C_STR	strName)
{
	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		if (strName==m_ObjList[iObj]->szName)
		{
			return iObj;
		}
	}
	return -1;
}
bool AseParser::Release()
{
	m_DataList.clear();
	m_MaterialList.clear();
	m_ObjList.clear();	return true;
}

AseParser::AseParser()
{
	m_iListindex = 0;
	m_LastIndex = 0;
}

AseParser::~AseParser()
{
	Release();
}
