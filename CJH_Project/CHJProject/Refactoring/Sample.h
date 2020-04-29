#pragma once
#pragma warning( disable:4005 )
#include "JHDxCore.h"
#include "JHShapeBox.h"
#include "JH_ShapePlane.h"
#include "JH_ShapeLine.h"
#include"JH_Input.h"
#include"JH_Sprite.h"
#include"JH_Map.h"

class TAnimBox : public JHShapeBox
{
public:
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_srvList;
	int iIndex;
	float ftime;
public:
	void    SetMatrix(D3DXMATRIX* matWorld,
		D3DXMATRIX* matView,
		D3DXMATRIX* matProj)
	{
		if (matWorld != nullptr)
		{
			m_matWorld = *matWorld;
		}
		if (matView != nullptr)
		{
			m_matView = *matView;
		}
		if (matProj != nullptr)
		{
			m_matProj = *matProj;
		}

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
		D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
		D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);

		m_cbData.d.x = ftime * 10.0f;
		D3D11_MAPPED_SUBRESOURCE mss;
		if (SUCCEEDED(m_dxHelper.m_pContext->Map(
			m_dxHelper.m_pConstantBuffer, 0,
			D3D11_MAP_WRITE_DISCARD,
			0, &mss)))
		{
			CB_DATA* pData = (CB_DATA*)mss.pData;
			memcpy(pData, &m_cbData, sizeof(CB_DATA));
			m_dxHelper.m_pContext->Unmap(m_dxHelper.m_pConstantBuffer, 0);
		}
	}
	bool	PostRender()
	{
		ftime += g_SecondPerFrame;
		if (ftime > 0.1f)
		{
			iIndex++;
			ftime -= 0.1f;
			if (iIndex >= 23) iIndex = 0;
		}
		m_dxHelper.m_pContext->PSSetShaderResources(0, 1, m_srvList[iIndex].GetAddressOf());
		m_dxHelper.m_pContext->PSSetShaderResources(1, 1, m_srvList[iIndex + 1].GetAddressOf());
		m_dxHelper.PostRender();
		return true;
	}
public:
	TAnimBox()
	{
		iIndex = 0;
		ftime = 0.0f;
	};
	virtual ~TAnimBox() {}
};
class Sample : public JHDXCore
{
public:

	JH_Map m_tempMap;
	vector<RECT>	m_rtList;
	D3DXVECTOR3 m_vPos;
	D3D11_SAMPLER_DESC descSamp;
	D3D11_BLEND_DESC bs;
public:
	std::shared_ptr<TAnimBox>  m_Box;
	std::shared_ptr<JH_ShapePlane> m_planeObj;
	std::shared_ptr<JH_Sprite> m_hero;
	std::shared_ptr<JH_ShapePlane> m_map;
	std::shared_ptr<JH_ShapeLine>  m_Line;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	Sample();
	virtual ~Sample();
};


//#pragma once
//#include"JHDXCore.h"
//#include"JH_ShapePlane.h"
//#include"JH_DxState.h"
//#include"JH_Input.h"
//#include"JHShapeBox.h"
//
//class Sample:public JHDXCore
//{
//public:
//	D3DXVECTOR3	 m_vPos;
//public:
//	std::shared_ptr<JHShapeBox>	m_Box;
//public:
//	bool	Init();
//	bool	Frame();
//	bool	Render();
//	bool	Release();
//public:
//	Sample();
//	virtual ~Sample();
//};
//
