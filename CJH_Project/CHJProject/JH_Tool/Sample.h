
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"
#include"QuadTree.h"
#include"RenderTarget.h"
#include"JHShapeBox.h"
#include"MaxObj.h"
#include"TextureMgr.h"
struct LoadMap
{
	T_STR m_BaseTextureFile;
	T_STR m_NormalMapFile;
	T_STR m_ShaderFile;
	T_STR m_pSplattAlphaTextureFile;

	T_STR m_pSplattTextureFile[4];

	//Splatt Texture

};
struct BufType
{
	D3DXVECTOR3 vPickPos;
	D3DXVECTOR3 vRect[4];
	float  fRadius;
	int    iIndex;
};
class Sample :public JHDXCore
{
public:
	//Texture Splatting
	ComPtr<ID3D11Texture2D> m_SplattingTex;
	ComPtr<ID3D11ShaderResourceView>	m_pDestSrv;
	ComPtr<ID3D11ShaderResourceView>	m_pSplSrv;
	Texture*							m_pTexture;
	ComPtr<ID3D11Texture2D> pDestTexture;
	ComPtr<ID3D11Texture2D> pSrcTexture;
	//ComputeShader Splatting
	ComPtr<ID3D11Texture2D> pUAVTexture;

	ComPtr<ID3D11Buffer>				m_pStructureBF;
	ComPtr<ID3D11ShaderResourceView>	m_pBufSrv;
	ComPtr<ID3D11ShaderResourceView>	m_pReadSrv;
	ComPtr<ID3D11UnorderedAccessView>	m_pUAV;
	ComPtr<ID3D11ComputeShader>			m_pCS;
	BufType								m_vBuf0[1];
	//Shadow
	vector<RenderTarget>				m_RTTextureList;
public:
	JH_ShapePlane			m_MiniMap;
	D3DXMATRIX				m_matTopView;
	D3DXMATRIX				m_matTopProj;
	D3DXVECTOR3				m_NearPoint;
	RenderTarget			m_RenderTarget;


	shared_ptr<JHShapeBox>	m_pBox;

	map<int,shared_ptr<MaxObj>> m_ObjList;
	shared_ptr<MaxObj>		m_CurrentObj;
	
	D3D11_VIEWPORT	m_vp;
	float m_fTimer;
	//Save
	const TCHAR*			m_pSplattTextureName;
	//Load
	TCHAR  m_pBuffer[256];
	TCHAR  m_pString[256];
	int    m_iTemp;
	LoadMap m_LoadMapData;
public:
	shared_ptr<JH_ShapeLine>m_DebugLine;
	shared_ptr<JH_Map>		m_Map;
	shared_ptr<HQuadTree>	m_QuadTree;
public:
	bool bAttach;
	bool bSplatting;
	int	CurrentObjIndex;
	
public:
	bool CreateMap(int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName=nullptr);
	int CreateObj(const TCHAR* pFileName,D3DXMATRIX& m_matWorld);
	void MapUpDown(SPHERE Sphere);
	//

	HRESULT MapSplatting(SPHERE Sphere);
	HRESULT CreateCSTexture();
	HRESULT	CreateSplattingTexture();
	HRESULT	CreateSplattingTexture(HNode* pNode);
	void GetNearPoint();
	void RunComputeShaderSplatting(UINT nNumViews, ID3D11ShaderResourceView** pShaderResourceView,
		ID3D11UnorderedAccessView* pUnorderedAccessView, UINT X, UINT Y, UINT Z);
	//¿˙¿Â
	TCHAR*	SaveFileDlg(TCHAR* szExt, TCHAR* szTitle);
	bool	SaveMapData();
	bool	SaveMapTexture();
	//Load
	bool   LoadMapData(const TCHAR* LoadFile);
	//OVERRIDE
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	virtual ~Sample();
};

