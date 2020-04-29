#pragma once
#include"JH_Model.h"

struct SCENEINFO
{
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TickPerFrame;
	int iNumMesh;		// �޽�������Ʈ ����
	int iNumMaterial;   // ��Ʈ���͸��� ����
	int iMaxWeight;		// ���� �� ����ġ
	int iBindPose;		// ���ε� ���� ���ϸ��̼� ����
};

struct MapInfo
{
	int iSubNo;
	TCHAR szTextureName[256];

	MapInfo()
	{
		iSubNo = -1;
		ZeroMemory(&szTextureName, sizeof(TCHAR) * 256);
	}
};
struct Mtrl
{

	vector<MapInfo> m_MapList;
	vector<Mtrl> submtl;


};
class MaxObj :public JH_Model
{
public:
	vector<PNCT_VERTEX>	 m_PNCTBuffer;
	//vector<Mesh>		 m_MeshList;

public:
	TCHAR  m_pBuffer[256];
	TCHAR  m_pString[256];
	int    m_iTemp;
	SCENEINFO	 m_Scene;
	vector<Mtrl> m_ExpMtlList;
	float		 m_fElapseTick;
	FILE*		 m_pStream;
public:
	bool	Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile);
	void	Convert();
	bool	OpenStream(const TCHAR* FileName);
	bool	CloseStream();
	bool	Parsing(const TCHAR* FileName);
	//bool	AddVertex(int iObj, int iFace, int iVertex, Mesh& mesh);
public:
	//HRESULT CreateVertexData()override;
	//HRESULT CreateIndexData()override;
	//bool Init()override;
	//bool Frame()override;
	//bool Render()override;
	//bool Release()override;
public:
	MaxObj() {};
	virtual ~MaxObj() {};
};

