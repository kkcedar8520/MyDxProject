#pragma once
#include"JH_SKinStd.h"
#define MAX_BONE_MATRIX 255

struct CBConstBonelWorld
{
	D3DMATRIX g_MatBoneWorld[MAX_BONE_MATRIX];
};

class SkinObj :public JH_Model
{
public:
	vector<PNCTIW_VERTEX>	 m_PNCTBuffer;
	vector<PNCTIW_VERTEX>	 m_VertexSkinData;
	vector<D3DXMATRIX>		 m_matBindPoseList;
	//vector<Mesh>		 m_MeshList;
	ComPtr<ID3D11Buffer> m_pBoneConstBuffer;
	CBConstBonelWorld	 m_CbBoneWorldData;
	D3DXMATRIX			 m_MatBoneWorld[255];

public:
	TCHAR  m_pBuffer[256];
	TCHAR  m_pString[256];
	int    m_iTemp;
	SCENEINFO	 m_Scene;
	vector<Mtrl> m_ExpMtlList;
	vector<HMeshSkin>	m_ExpObject;
	float		 m_fElapseTick;
	FILE*		 m_pStream;
public:
	bool	Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile);
	void	Convert();
	bool	OpenStream(const TCHAR* FileName);
	bool	CloseStream();
	bool	Parsing(const TCHAR* FileName);
	int		GetParentIndex(const TCHAR*	strName);
	void    GetVIData(HMeshSkin& mesh);
	bool	Draw(HMeshSkin& mesh);

	//bool	AddVertex(int iObj, int iFace, int iVertex, Mesh& mesh);
public:
	HRESULT CreateVertexData()override;
	HRESULT CreateVertexBuffer()override;
	HRESULT CreateIndexData()override;
	HRESULT CreateConstantBuffer()override;
	HRESULT CreateInputLayout()override;
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	SkinObj() {};
	virtual ~SkinObj() {};
};

