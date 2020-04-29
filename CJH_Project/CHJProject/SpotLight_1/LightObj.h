#pragma once
#include"JHShapeBox.h"

#define MAX_LIGHT_SIZE 5
#define CONSTANT_BUFFER_SIZE 3
const int g_iLightNum=1;
struct LightConstantBuffer
{
	D3DXVECTOR4 vAmbinentLightColor[g_iLightNum];
	D3DXVECTOR4 vDiffuseLightColor[g_iLightNum];
	D3DXVECTOR4 vSpecularLightColor[g_iLightNum];	
	D3DXVECTOR4 vSpotLightColor[g_iLightNum];
	D3DXVECTOR4 vLightDirection[g_iLightNum];//W :감쇠
	D3DXVECTOR4 vLightPos[g_iLightNum];//W:반지름
	D3DXVECTOR4 vEyeDirection[g_iLightNum];//W:강도//Specular
	D3DXVECTOR4 vEyePos[g_iLightNum];//W:반지름//포인트 라이트
	D3DXVECTOR4 vSpotLight[g_iLightNum];// 내부,외부,휘도 theta, phi, Fallofff

};

struct LightInfo
{
	D3DXVECTOR4 vAmbinentLightColor;
	D3DXVECTOR4 vDiffuseLightColor;
	D3DXVECTOR4 vSpecularLightColor;
	D3DXVECTOR4 vSpotLightColor;
	D3DXVECTOR3 LightDir;
	D3DXVECTOR3 LightPos;
	D3DXVECTOR3 At;
	D3DXVECTOR3 EyePos;
	D3DXVECTOR3 EyeDir;
	int iType;
	float Attenuation;
	LightInfo()
	{
		vAmbinentLightColor = { 1,1,1,1 };
		vDiffuseLightColor = { 1,1,1,1 };
		vSpecularLightColor = { 1,1,1,1 };
		vSpotLightColor = { 1,1,1,1 };
	}
};

class LightObj :public JH_Model
{
public:
	JHShapeBox m_Obj;



	
	D3DXMATRIX m_MatRotation;
	D3DXMATRIX m_MatScale;

	LightInfo m_Info;

public:
	void SetLightInfo(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LightInfo light);
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

