
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"
#include"QuadTree.h"
#include"RenderTarget.h"
#include"JHShapeBox.h"
#include"MaxObj.h"
#include"TextureMgr.h"
struct MAPDATA
{
	int iCol;
	int iRow;
	int iCellCount;
	int iCellSize;
	T_STR m_BaseTextureFile;
	T_STR m_NormalMapFile;
	T_STR m_ShaderFile;
	
	vector<T_STR> m_pSplattAlphaTextureFile;
	vector<float> m_fHegihtList;
	vector<T_STR> m_pSplattTextureFile;
	void Reset()
	{
		m_BaseTextureFile.clear();
		m_NormalMapFile.clear();
		m_ShaderFile.clear();
		m_pSplattAlphaTextureFile.clear();
		m_fHegihtList.clear();
		m_pSplattTextureFile.clear();
	}
	

};
struct BufType
{
	D3DXVECTOR3 vPickPos;
	float		fRadius;
	float		Alpha[4];
	int			iIndex;
	int			iCol;
	int			iRow;


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
	ComPtr<ID3D11Texture2D>	pReadTexture;

	ComPtr<ID3D11Buffer>				m_pStructureBF;
	ComPtr<ID3D11ShaderResourceView>	m_pBufSrv;
	ComPtr<ID3D11ShaderResourceView>	m_pReadSrv;
	ComPtr<ID3D11ShaderResourceView>	m_pCopySrv;


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
	const TCHAR*			m_pSPTAFile;
	JH_ShapePlane			m_SplattAlphaPlane;
	//Load
	TCHAR  m_pBuffer[256];
	TCHAR  m_pString[256];
	int    m_iTemp;
	MAPDATA m_sMapData;
	ComPtr<ID3D11ShaderResourceView> m_pLoadingSplSrv;

public:
	shared_ptr<JH_ShapeLine>m_DebugLine;
	shared_ptr<JH_Map>		m_Map;
	shared_ptr<HQuadTree>	m_QuadTree;
public:
	bool bAttach;
	bool bSplatting;
	bool bMapFlatting;
	int	CurrentObjIndex;
	float m_HeightVlaue;
	
public:
	bool CreateMap(int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName=nullptr);
	int CreateObj(const TCHAR* pFileName,D3DXMATRIX& m_matWorld);
	void MapUpDown(SPHERE Sphere);
	void MapFlatting(SPHERE Sphere);
	//

	HRESULT MapSplatting(SPHERE Sphere);
	HRESULT CreateCSTexture();
	HRESULT	CreateSplattingTexture();
	HRESULT	CreateSplattingTexture(HNode* pNode);
	void GetNearPoint();
	void RunComputeShaderSplatting(UINT nNumViews, ID3D11ShaderResourceView** pShaderResourceView,
		ID3D11UnorderedAccessView* pUnorderedAccessView, UINT X, UINT Y, UINT Z);
	//����
	TCHAR*	SaveFileDlg(TCHAR* szExt, TCHAR* szTitle);
	bool	SaveMapData();
	bool	SaveDataReset();

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

