#pragma once
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"

struct LightInfrom
{
	D3DXVECTOR4 vLightDirection;
	D3DXVECTOR4 vLightPos;
	D3DXVECTOR4 vEyeDirection;
	D3DXVECTOR4 vEyePos;
	D3DXVECTOR4 vAmbinentLightColor;
	D3DXVECTOR4 vDiffuseLightColor;
};

class Sample :public JHDXCore
{
public:
	JH_ShapeLine m_DebugLine;
	ID3D11Buffer* m_pLightConstantBuffer;
	LightInfrom m_cbLight;
	JH_Map m_Map;
public:

public:
	ID3D11Buffer* MakeConstantBuffer(ID3D11Device* m_pDevice, void* Data,int iSize,int Num);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

