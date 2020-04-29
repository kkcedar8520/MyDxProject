#pragma once
#include"JH_Model.h"
#include"TextureMgr.h"
#include"Mesh.h"

static vector<string> AseSection = { "MATERIAL ","MATERIAL_LIST ","GEOMOBJECT ","HELPEROBJECT "};
static vector<string> MaterialSection = { "MATERIAL ","SUBMATERIAL ","NUMSUBMTLS ","MAP_NAME ","GEOMOBJECT ","HELPEROBJECT " };
enum MATERIALSECTION { NEWMATERIAL=0, SUBMATERIAL, NUMSUBMTLS, MAPNAME,GEOMOBJ,HELPEROBJ, };
static vector<string> TextureSection = { "MAP_SUBNO ","BITMAP ","SUBMATERIAL","MATERIAL ","GEOMOBJECT ", "HELPEROBJECT " };
enum TEXTURESECTION { SUBNO = 0, TEXTURE, GEOM_OBJECT, HELPEROBJECT};
static vector<string> GeomObjSection = { "NODE_NAME ","NODE_PARENT ","NODE_TM ","TM_ROW0 ","MESH " ,"MATERIAL_REF ","TM_ANIMATION " };


struct SCENEINFO
{
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TickPerFrame;
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
	UINT i[3], SubMtrl;


};
struct GeomObj
{
	CHAR szName[256];
	CHAR szParentName[256];

	D3DXMATRIX m_matWorld;


	int iNumVertex;
	int iNumFace;
	int iNumTVertex;
	int iNumTFace;
	int iNumCVertex;
	int m_Ref;


	vector<AnimTrack> m_AnimTrackPos;
	vector<AnimTrack> m_AnimTrackRotate;
	vector<AnimTrack> m_AnimTrackScale;




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
		iNumVertex=0;
		iNumFace=0;
		iNumTVertex=0;
		iNumTFace=0;
		iNumCVertex=0;
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
class AseParser
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
	void Tokenize(C_STR text, C_STR token, OutputIterator DataList);
	int SearchTokenArray(vector<string>& secction);

	int FindString(string szFind,bool bLoop);
	bool LoadScene();
	bool LoadMateRial();
	bool LoadMateRial(Mtrl* pMtrl);
	bool LoadGeomObj();
	bool LoadTexture(Mtrl* pMtrl);

	int GetNextLine();
	int GetData(string FindStr, void* pData = nullptr, int iType = 0, bool bLoop=true);
	int	GetLineData(void* pData = nullptr, int iType=0 );
	int GetParentIndex(C_STR strName);
	void GetUVData(int iLine, vector<D3DXVECTOR2>&UVList);
	void GetTFaceData(int iLine, vector<aseINDEX>&UVFacesList);
	bool GetAnimInfo();
	void GetFaceNormal(int iLine, vector<FaceNormal>&FaceNormalList);

public:
	bool Release();

public:
	AseParser();
	virtual ~AseParser();
};

enum ASESECTION
{
	SCENE = 0,
	MATERIAL_LIST,
	GEOMOBJECT,
	HELPER_OBJECT
};

enum GEOMOBJSECTION
{
	NODE_NAME = 0,
	NODE_PARENT_NAME,
	NODE_TM,
	TM_ROW,
	MESH,
	MATERIAL_REF,
	TM_ANIMATION,
};

