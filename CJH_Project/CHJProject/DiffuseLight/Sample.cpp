#include "Sample.h"
#include"JH_DxState.h"
#include"JH_Input.h"
#include "JH_ShapePlane.h"
#pragma warning( disable:4005 )



bool Sample::Init()
{

	m_Map.CreateHeightMap(m_pd3dDevice, m_pImmediateContext, L"../../data/map/WaterMap.jpg");


	m_Map.SetMapDesc(L"../../data/map/Tile26.jpg", L"LightShader.txt", m_Map.m_iColumNum, m_Map.m_iRowNum, 1, 10.0f);

	m_Map.Load(m_pd3dDevice, m_pImmediateContext);

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -400), D3DXVECTOR3(0, 0, 0));

	m_cbLight.vAmbinentLightColor = D3DXVECTOR4(0.3F, 0.3F, 0.3F, 1.0F);
	m_cbLight.vDiffuseLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_cbLight.vSpecularLightColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_cbLight.vEyeDirection.x = m_pMainCamera->m_vLookup.x;
	m_cbLight.vEyeDirection.y = m_pMainCamera->m_vLookup.y;
	m_cbLight.vEyeDirection.z = m_pMainCamera->m_vLookup.z;
	m_cbLight.vEyeDirection.w = 70.0f;
	m_cbLight.vEyePos.x = m_pMainCamera->m_vPos.x;
	m_cbLight.vEyePos.y = m_pMainCamera->m_vPos.y;
	m_cbLight.vEyePos.z = m_pMainCamera->m_vPos.z;
	m_cbLight.vEyePos.w = 1.0f;
	m_cbLight.vLightDirection = D3DXVECTOR4(0, -1.0, 0, 10.0f);
	m_cbLight.vLightPos = D3DXVECTOR4(0, 100, 0, 1.0F);
	
	m_pLightConstantBuffer.Attach(DX::MakeConstantBuffer(m_pd3dDevice, &m_cbLight, sizeof(m_cbLight), 1));





	m_DebugLine.Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShader.txt", nullptr, "VSLine", "PSLine");





	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);

	
	JDX::ApplySS(m_pImmediateContext, JDX::JH_DxState::g_pSamplerState);
	return true;
}
bool Sample::Frame()
{

	if (G_Input.KeyCheck(VK_F3) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext(), JDX::JH_DxState::g_pRSSold);
	}
	if (G_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext(), JDX::JH_DxState::g_pRSWireFrame);
	}
	m_Map.m_vEyePos = m_pMainCamera->m_vLookup;

	return true;
}
bool Sample::Render()
{
	m_Map.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_Map.UpdateConstantBuffer(m_pLightConstantBuffer.Get(), &m_cbLight);
	m_pImmediateContext->UpdateSubresource(m_pLightConstantBuffer.Get(), 0, nullptr,&m_cbLight, 0, 0);

	m_Map.m_dxHelper.m_pContext->VSSetConstantBuffers(1, 1, m_pLightConstantBuffer.GetAddressOf());
	m_Map.m_dxHelper.m_pContext->PSSetConstantBuffers(1, 1, m_pLightConstantBuffer.GetAddressOf());


	m_Map.Render();


	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_DebugLine.Draw({ 0,0,0 }, { 1000,0,0 }, { 1,0,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,1000,0 }, { 0,1,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,0,1000 }, { 0,0,1,1 });



	return true;
}
bool Sample::Release()
{

	return true;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}
RECT rtClient = { 0,0,1000,600 };

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	Sample game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ROCKMAN", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;
}
