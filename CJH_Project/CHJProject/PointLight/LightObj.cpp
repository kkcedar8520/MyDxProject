#include "LightObj.h"



LightObj::LightObj()
{
}

void    LightObj::SetMatrix(D3DXMATRIX* matWorld,
	D3DXMATRIX* matView,
	D3DXMATRIX* matProj)
{
	m_Obj.SetMatrix(matWorld, matView, matProj);
}

LightObj::~LightObj()
{
}
void LightObj::CreateLightObj(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, D3DXVECTOR3 Pos, D3DXVECTOR3 At, D3DXVECTOR3 EyePos, D3DXVECTOR3 EyeDir)
{

	m_dxHelper.m_pd3dDevice = pDevice;
	m_dxHelper.m_pContext = pContext;

	m_cbLight.vAmbinentLightColor = D3DXVECTOR4(0.0F, 0.0F, 0.0F, 1.0F);
	m_cbLight.vDiffuseLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_cbLight.vSpecularLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_cbLight.vEyeDirection.x = EyeDir.x;
	m_cbLight.vEyeDirection.y = EyeDir.y;
	m_cbLight.vEyeDirection.z = EyeDir.z;
	m_cbLight.vEyeDirection.w = 70.0f;
	m_cbLight.vEyePos.x = EyePos.x;
	m_cbLight.vEyePos.y = EyePos.y;
	m_cbLight.vEyePos.z = EyePos.z;
	m_cbLight.vEyePos.w = 1.0f;


	m_cbLight.vLightDirection.x = At.x - Pos.x;
	m_cbLight.vLightDirection.y = At.x - Pos.y;
	m_cbLight.vLightDirection.z = At.x - Pos.z;
	m_cbLight.vLightDirection.w = 1.0f;

	D3DXVec4Normalize(&m_cbLight.vLightDirection, &m_cbLight.vLightDirection);
	m_cbLight.vLightPos = D3DXVECTOR4(Pos, 400.0f);

	m_pLightConstantBuffer.Attach(DX::MakeConstantBuffer(m_dxHelper.m_pd3dDevice, &m_cbLight, sizeof(m_cbLight), 1));

	LightObj::Init();
}


bool LightObj::Init()
{
	m_Obj.Create(m_dxHelper.m_pd3dDevice, m_dxHelper.m_pContext, L"LightShader.txt", L"../../data/Resource/powerbattles_BG.gif");

	m_Obj.m_matWorld._41 = 0;//m_cbLight.vLightPos.x;
	m_Obj.m_matWorld._42 = 1; // m_cbLight.vLightPos.y;
	m_Obj.m_matWorld._43 = 0; //m_cbLight.vLightPos.z;

	D3DXMatrixScaling(&m_MatScale, 10, 10, 10);


	m_Obj.m_matWorld = m_Obj.m_matWorld*m_MatScale;
	return true;
}

void LightObj::Update(D3DXVECTOR3 m_EyePos, D3DXVECTOR3 m_EyeDirection, float Height)
{
	m_cbLight.vEyeDirection.x = m_EyeDirection.x;
	m_cbLight.vEyeDirection.y = m_EyeDirection.y;
	m_cbLight.vEyeDirection.z = m_EyeDirection.z;
	m_cbLight.vEyeDirection.w = 30;

	m_cbLight.vEyePos.x = m_EyePos.x;
	m_cbLight.vEyePos.y = m_EyePos.y;
	m_cbLight.vEyePos.z = m_EyePos.z;
}
bool LightObj::Frame()
{
	m_Obj.Frame();
	return true;
}
bool LightObj::Render()
{
	m_Obj.Render();

	return true;
}
bool LightObj::Release()
{
	return true;
}