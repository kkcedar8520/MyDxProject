#pragma once
#include"JHShapeBox.h"

#define MAX_LIGHT_SIZE 5
#define CONSTANT_BUFFER_SIZE 3
const int g_iLightNum = 1;

struct LightInfoBuffer
{
	D3DXVECTOR4 vAmbinentLightColor;
	D3DXVECTOR4 vDiffuseLightColor;
	D3DXVECTOR4 vSpecularLightColor;
	D3DXVECTOR4 vSpotLightColor;
	D3DXVECTOR4 vLightDirection;//W :����
	D3DXVECTOR4 vLightPos;//W:Ÿ��
	D3DXVECTOR4 vSpotLight;// ����,�ܺ�,�ֵ� theta, phi, Fallofff
};


struct LightInfo
{
	D3DXVECTOR4 vAmbinentLightColor;
	D3DXVECTOR4 vDiffuseLightColor;
	D3DXVECTOR4 vSpecularLightColor;
	D3DXVECTOR4 vSpotLightColor;
	D3DXVECTOR4 vSpotLight;
	D3DXVECTOR3 LightDir;
	D3DXVECTOR3 LightPos;
	D3DXVECTOR3 At;
	float Radius;
	float Fallof;
	float Attenuation;
	int	  iType;

	

	LightInfo()
	{
		vAmbinentLightColor = { 1,1,1,1 };
		vDiffuseLightColor = { 1,1,1,1 };
		vSpecularLightColor = { 1,1,1,1 };
		vSpotLightColor = { 1,1,1,1 };
	};
};

class LightObj :public JH_Model
{
public:
	JHShapeBox m_Obj;

	
	LightInfoBuffer m_cbLight;

	D3DXMATRIX m_MatRotation;
	D3DXMATRIX m_MatScale;

	LightInfo m_Info;

public:
	void CreateLightObj(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LightInfo light);
	void Update(D3DXVECTOR3 m_EyePos, D3DXVECTOR3 m_EyeDirection);

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
	virtual void SetMatrix(D3DXMATRIX* matWorld,
		D3DXMATRIX* matView,
		D3DXMATRIX* matProj)override;
public:
	LightObj();
	virtual ~LightObj();
};

