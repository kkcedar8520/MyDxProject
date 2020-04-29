#pragma once
#include"JH_ObjStd.h"
class MaxObj :public JH_Model
{
public:
	vector<PNCTIW_VERTEX>	 m_PNCTBuffer;
	vector<HTri>		 m_FaceBuffer;
	//vector<Mesh>		 m_MeshList;
public:
	TCHAR  m_pBuffer[256];
	TCHAR  m_pString[256];
	int    m_iTemp;
	SCENEINFO	 m_Scene;
	vector<Mtrl> m_ExpMtlList;
	
	vector<HMesh>	m_ExpObject;
	float		 m_fElapseTick;
	FILE*		 m_pStream;
public:
	bool	Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile);
	void	Convert();
	bool	OpenStream(const TCHAR* FileName);
	bool	CloseStream();
	bool	Parsing(const TCHAR* FileName);
	int		GetParentIndex(const TCHAR*	strName);
	void	GetVIData(HMesh& mesh);
	bool	Draw(HMesh& mesh);
	//bool	AddVertex(int iObj, int iFace, int iVertex, Mesh& mesh);
public:
	HRESULT CreateVertexData()override;
	HRESULT CreateIndexData()override;
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	MaxObj() {};
	virtual ~MaxObj() {};
};

