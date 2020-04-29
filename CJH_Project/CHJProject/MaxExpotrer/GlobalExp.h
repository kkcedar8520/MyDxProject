#pragma once
#include"Header.h"

#define ALMOST_ZERO 1.0e-4f
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
	PNCT_VERTEX	v[3];
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

	vector<INode*>	m_ObjList;
	vector<Mtl*>	m_MtlList;
	vector<Mtrl>	m_ExpMtlList;
	vector<HMesh>	m_ExpObject;

	SCENEINFO		m_Scene;

public:
	bool Init(Interface* MaxInterface);
	void PreProcess(INode* pNode);
	void AddObject(INode* pNode);
	void AddMaterial(INode* pNode);
	bool Exporter(const MCHAR *name);

	bool Convert();

public:
	void			DumpPoint3(Point3& p1, Point3& p2);
	void			DumpQuat(Quat& p1, Quat& p2);
	void			TransDXMatrix(Matrix3& m, D3D_MATRIX& dm);
	TriObject*		GetTriObjectFromNode(INode* pNode, int Tick, BOOL& NeedDel);
	bool			GetMesh(INode* pNode, HMesh* hmesh);
	void			GetTexture(Mtl* pMtl, Mtrl& JMtrl);
	Point3			GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);

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
public:
	GlobalExp();
	virtual ~GlobalExp();
};

