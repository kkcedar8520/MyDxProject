#pragma once
#include"Header.h"
#define CTL_CHARS		31
#define SINGLE_QUOTE	39 // ( ' )
#define ALMOST_ZERO 1.0e-4f

enum NODE_TYPE
{
	GEOM_MESH = 0,
	HELPER_DUMMY,
	HELPER_BONE,
	BYPED,
};


struct BipedVertex
{
	int   iNumWeight;
	vector<BYTE>   IDList;
	vector<float>  weightList;
};
struct PNCT_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	bool operator == (const PNCT_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t && n == v.n)
		{
			return true;
		}
		return false;
	}
	PNCT_VERTEX() {}
	PNCT_VERTEX(Point3 p, Point3 n, Point4 c, Point2 t)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
	}
};
struct PNCTIW_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float i[4];
	float w[4];
	bool operator == (const PNCTIW_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t && n == v.n)
		{
			return true;
		}
		return false;
	}
	PNCTIW_VERTEX() {
		this->i[0] = 0;
		this->i[1] = 0;
		this->i[2] = 0;
		this->i[3] = 0;
		this->w[0] = 0;
		this->w[1] = 0;
		this->w[2] = 0;
		this->w[3] = 0;
	}
	PNCTIW_VERTEX(Point3 p, Point3 n, Point4 c, Point2 t,
		Point4 i, Point4 w)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
		this->i[0] = i.x;
		this->i[1] = i.y;
		this->i[2] = i.z;
		this->i[3] = i.w;
		this->w[0] = w.x;
		this->w[1] = w.y;
		this->w[2] = w.z;
		this->w[3] = w.w;

	}
};
typedef struct _D3D_MATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
}D3D_MATRIX;

struct SCENEINFO
{
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TickPerFrame;
	int iNumMesh;		// 메쉬오브젝트 개수
	int iNumMaterial;   // 루트매터리얼 개수
	int iMaxWeight;		// 정점 당 가중치
	int iBindPose;		// 바인딩 포즈 에니메이션 여부
};
struct MapInfo
{
	int iSubNo;
	MSTR szTextureName;
};
struct Mtrl
{
	
	vector<MapInfo> m_MapList;
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
struct AnimTrack
{
	int iTick;
	Point3		p;
	Quat	q;
};
struct HTri
{
	PNCTIW_VERTEX	v[3];
	int			iSubIndex;
	HTri()
	{
		iSubIndex = -1;
	}
};
class HMesh
{
public:
	MSTR		m_szName;
	MSTR		m_szParentName;

	
	int			m_iRef;
	int			m_iTextIndex;

	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	UINT		m_iType;
	int			m_iParentIndex;

	vector<HTri> m_TriList;
	_D3D_MATRIX  m_matWorld;
	//_D3D_MATRIX	m_matInverseWorld;
	//_D3D_MATRIX  m_matCalculation;

	Point3		m_vAnimScale;
	Quat		m_qAnimScaleRotation;
	Quat		m_qAnimRotation;
	Point3		m_vAnimPos;


	//Texture*	m_pTexture;
	vector<HMesh> subMesh;


	vector<AnimTrack> m_AnimTrackPos;
	vector<AnimTrack> m_AnimTrackRotate;
	vector<AnimTrack> m_AnimTrackScale;


	//CB_DATA     m_cbData;


public:
	HMesh()
	{
		m_iRef = -1;
		m_iTextIndex = -1;
		m_iBaseVertex = 0;
		m_iNumVertex = 0;
		m_iParentIndex = -1;
	}
	~HMesh() {};
};
class GlobalExp
{
public:
	Interface* m_pMax;
	Interval m_Interval;
	INode * m_pRootNode;
	TCHAR		m_tmpBuffer[MAX_PATH];

	vector<INode*>		m_ObjList;
	vector<Mtl*>		m_MtlList;
	vector<Mtrl>		m_ExpMtlList;
	vector<HMesh>		m_ExpObject;
	vector<int>			m_SelNode;
	vector<BipedVertex> m_BipedList;

	SCENEINFO		m_Scene;

public:
	bool Init(Interface* MaxInterface);
	bool Release();
	void PreProcess(INode* pNode);
	void AddObject(INode* pNode);
	void AddMaterial(INode* pNode);


	bool Convert();

public:
	void			DumpPoint3(Point3& p1, Point3& p2);
	void			DumpQuat(Quat& p1, Quat& p2);
	void			TransDXMatrix(Matrix3& m, D3D_MATRIX& dm);
	TriObject*		GetTriObjectFromNode(INode* pNode, int Tick, BOOL& NeedDel);
	bool			GetMesh(INode* pNode, HMesh* hmesh);
	void			GetTexture(Mtl* pMtl, Mtrl& JMtrl);
	Point3			GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	void			GetSelectNode(INode* pNode);//모든 노드를 돌아 카운트에 맞는노드를 추가한다
	int				GetFindIndex(INode* node);

	bool CheckForAnimation(INode* pNode,BOOL& bPosAnim,BOOL& bRotAnim,BOOL& bSclAnim);
	void GetDecompAffine(INode* pNode, TimeValue t, AffineParts* ap);
	bool EqualPoint1(float p1,	float p2);
	bool EqualPoint2(Point2 p1, Point2 p2);
	bool EqualPoint3(Point3 p1, Point3 p2);
	bool EqualPoint4(Point4 p1, Point4 p2);
	void DumpPosSample(INode* pNode, HMesh* pMesh);
	void DumpRotSample(INode* pNode, HMesh* pMesh);
	void DumpSclSample(INode* pNode, HMesh* pMesh);
	bool TMNegParity(Matrix3 &m);//네거티브 스케일 판정 함수.,

	//
	void ExportPhysiqueData(INode* pNode, Modifier*Modifier);
	void ExportSkinData(INode* pNode, Modifier* Modifier);
	void InsertWeight(
		DWORD dwSrc, BYTE Bone, float fWeight);

	Modifier* FindModifier(INode *nodePtr, Class_ID classID);
	TCHAR* SaveFileDlg(TCHAR* szExt, TCHAR* szTitle);
	TCHAR* FixupName(MSTR name);

	//가중치정렬
	void  InsertWeight(
		BipedVertex& Bp, BYTE Bone, float fWeight);

	bool ExporterSkin();
	bool ExporterMatrix();
public:
	GlobalExp();
	virtual ~GlobalExp();
};

