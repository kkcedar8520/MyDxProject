#pragma once
#include"JHShapeBox.h"


struct LightInfo
{

};
struct LightConstantBuffer
{
	D3DXVECTOR4 vLightDirection;
	D3DXVECTOR4 vLightPos;
	D3DXVECTOR4 vEyeDirection;
	D3DXVECTOR4 vEyePos;
	D3DXVECTOR4 vAmbinentLightColor;
	D3DXVECTOR4 vDiffuseLightColor;
	D3DXVECTOR4 vSpecularLightColor;
	D3DXVECTOR4 vSpotLightColor;
	D3DXVECTOR4 vSpotLight;

};


class LightObj :public JH_Model
{
public:
	JHShapeBox m_Obj;
	D3DXVECTOR4 m_At;
	LightConstantBuffer m_cbLight;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pLightConstantBuffer;
	D3DXMATRIX m_MatRotation;
	D3DXMATRIX m_MatScale;


public:
	void CreateLightObj(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, D3DXVECTOR3 Pos, D3DXVECTOR3 At, D3DXVECTOR3 EyePos, D3DXVECTOR3 EyeDir);
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

