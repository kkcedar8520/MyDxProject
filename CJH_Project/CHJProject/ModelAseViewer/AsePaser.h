#pragma once
#include"JH_Model.h"
#include"TextureMgr.h"

static vector<string> AseSection = { "SCENE ","MATERIAL_LIST ","GEOMOBJECT "};
static vector<string> MaterialSection = { "NUMSUBMTLS ","MAP_NAME "};
enum MATERIALSECTION { NUMSUBMTLS=0, MAPNAME,};
static vector<string> TextureSection = { "MAP_SUBNO ","BITMAP ","GEOMOBJECT " };
enum TEXTURESECTION { SUBNO = 0, TEXTURE, GEOM_OBJECT};
static vector<string> GeomObjSection = { "NODE_NAME ","NODE_TM ","TM_ROW0 ","MESH ","MATERIAL_REF " };

class Mesh
{
public:
	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	D3DXMATRIX  m_matWorld;
	Texture*	m_pTexture;
	vector<Mesh> subMesh;
	std::vector<PNCT_VERTEX> PNCTlist;
	CB_DATA     m_cbData;

};
struct SCENEINFO
{
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TickSperFrmae;
	int iMaterialNum;
};
struct Mtrl
{
	int Subno;
	int m_iTextIndex;
	string TextureName;
	vector<Mtrl> submtl;


};
struct FaceNormal
{
	float fn[3];
	float vn[3][3];
};
struct aseVertex
{

};
struct aseINDEX
{
	UINT i0, i1, i2,SubMtrl;
	

};
struct GeomObj
{
	char szName[256] = { 0 };
	D3DXMATRIX m_matWorld;

	
	int iNumVertex;
	int iNumFace;
	int iNumTVertex;
	int iNumTFace;
	int iNumCVertex;
	int m_Ref;




	
	vector<D3DXVECTOR3> m_VertexPosList;
	vector<aseINDEX> m_FacesList;
	vector<aseINDEX> m_UVFacesList;
	vector<D3DXVECTOR2> m_UVList;
	vector< FaceNormal>m_FaceNoramlList;

	vector<D3DXVECTOR3>   m_ColorVertexList;
	vector<aseINDEX>      m_ColorFaseList;


	GeomObj()
	{
		D3DXMatrixIdentity(&m_matWorld);
		
	}

};
enum DATATYPES
{
	NULL_DATA = 0,
	INT_DATA,
	STRING_DATA,
	FLOAT_DATA,
	BOOL_DATA,
	VERTEX_DATA,
	VECTOR_DATA,
	UV_DATA,
	INDEX_DATA,
	FACE_DATA,
	MATRIX_DATA,
};
class AsePaser
{

public:
	vector<Mtrl>			m_MaterialList;
	HANDLE				m_Handle;
	string				m_MBTokcenData;
	int					m_iListindex;
	vector<C_STR>		m_DataList;
	CHAR*				m_pMashData;
	DWORD				m_LastIndex;
	SCENEINFO			m_SCeneInfo;
	vector<shared_ptr<GeomObj>>				m_ObjList;
public:

	bool LoadBuffer(const TCHAR* LoadFile);
	
	void BeginToken();
	template<typename OutputIterator>
	void Tokenize(C_STR text,C_STR token, OutputIterator DataList);
	int SearchTokenArray(vector<string>& secction);

	int FindString(string szFind);
	bool LoadScene();
	bool LoadMateRial();
	bool LoadMateRial(Mtrl* pMtrl);
	bool LoadGeomObj();
	bool LoadTexture(Mtrl* pMtrl);

	int GetNextLine();
	int GetData(string FindStr, void* pData = nullptr, int iType = 0);
	void GetUVData(int iLine, vector<D3DXVECTOR2>&UVList);
	void GetTFaceData(int iLine, vector<aseINDEX>&UVFacesList);

	void GetFaceNormal(int iLine, vector<FaceNormal>&FaceNormalList);

public:
	bool Release();

public:
	AsePaser();
	virtual ~AsePaser();
};

enum ASESECTION
{
	SCENE=0,
	MATERIAL_LIST,
	GEOMOBJECT,
};

enum GEOMOBJSECTION
{
	NODE_NAME=0, 
	NODE_TM,
	TM_ROW,
	MESH,
	MATERIAL_REF,
	
};

