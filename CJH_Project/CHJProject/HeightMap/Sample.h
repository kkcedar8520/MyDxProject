#pragma once
#include"JHDXCore.h"
#include"JH_ShapePlane.h"

struct MapDesc
{
	int iColumNum;
	int iRowNum;
	const TCHAR* TextureFileName;
	const TCHAR* ShaderFileName;
	const TCHAR* NormalMapFileName;
	float fSellDistance;
	float fScaleHeight;
	//텍스트파일
	//쉐이더 
	//셀 간격
	//행
	//열
	//정점 갯 수
	MapDesc()
	{
		NormalMapFileName = nullptr;
		ShaderFileName = nullptr;
		TextureFileName = nullptr;

	}
};

class JH_Map :public JH_ShapePlane
{
public:
	MapDesc m_MapDesc;
	int m_iColumNum;
	int m_iRowNum;
	int m_iVertices;
	int m_iCellCol;
	int m_iCellRow;
	const TCHAR* m_TextureFileName;
	const TCHAR* m_ShaderFileName;
	const TCHAR* NormalMapFileName;
	float m_fSellDistance;
	float m_fScaleHeight;
public:
	vector<float> m_vHeightList;
public:
	ComPtr<ID3D11ShaderResourceView> m_pNorm;
public:
	HRESULT Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext);
	HRESULT CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext, const TCHAR* TextureFileName);
	void SetMapDesc(const TCHAR* TextureFileName,
		const TCHAR* ShaderFileName,
		int ColumNum,
		int RowNum,
		float fSellDistance,
		float fScaleHeight,
		const TCHAR* NormalMapFileName=nullptr);
	
public:
	
	HRESULT		CreateVertexData();
	HRESULT		CreateIndexData();

};



class Sample :public JHDXCore
{
public:
	JH_Map m_Map;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

