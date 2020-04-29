#pragma once

#include"JH_ShapePlane.h"
struct MapDesc
{
	int iColumNum;
	int iRowNum;
	const TCHAR* TextureFileName;
	const TCHAR* ShaderFileName;
	float fSellDistance;
	float fScaleHeight;
	//텍스트파일
	//쉐이더 
	//셀 간격
	//행
	//열
	//정점 갯 수

};

class JH_Map :public JH_ShapePlane
{
public:
	D3DXVECTOR3 m_vEyePos;
	MapDesc m_MapDesc;
	int m_iColumNum;
	int m_iRowNum;
	int m_iVertices;
	int m_iCellCol;
	int m_iCellRow;
	const TCHAR* m_TextureFileName;
	const TCHAR* m_ShaderFileName;
	float m_fSellDistance;
	float m_fScaleHeight;
public:
	vector<float> m_vHeightList;
public:
	HRESULT Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext);
	HRESULT CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext, const TCHAR* TextureFileName);
	void SetMapDesc(const TCHAR* TextureFileName,
		const TCHAR* ShaderFileName,
		int ColumNum,
		int RowNum,
		float fSellDistance,
		float fScaleHeight);
	void    SetMatrix(D3DXMATRIX* matWorld,
		D3DXMATRIX* matView,
		D3DXMATRIX* matProj)override;
	void UpdateConstantBuffer(ID3D11Buffer* pConstantBuffer, void* Data);
public:

	HRESULT		CreateVertexData();
	HRESULT		CreateIndexData();

};
