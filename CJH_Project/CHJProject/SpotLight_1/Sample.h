
#pragma once
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"
#include"LightObj.h"

class Sample :public JHDXCore
{
public:
	JH_ShapeLine m_DebugLine;

	LightObj m_LightObjList[g_iLightNum];

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pLightConstantBuffer[CONSTANT_BUFFER_SIZE];
	LightConstantBuffer m_cbLight;


	
	JH_Map m_Map;
public:

public:

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

