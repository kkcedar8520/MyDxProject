#include "Sample.h"
#include"JH_DxState.h"
#include"JH_Input.h"
#include "JH_ShapePlane.h"
#pragma warning( disable:4005 )



bool Sample::Init()
{

	m_Map.CreateHeightMap(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/map/heightMap513.bmp");


	m_Map.SetMapDesc(L"../../data/map/Tile20.jpg", L"LightShader.txt", m_Map.m_iColumNum, m_Map.m_iRowNum, 2, 3.0f);

	m_Map.Load(m_pd3dDevice.Get(), m_pImmediateContext.Get());

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	m_LightObj.CreateLightObj(m_pd3dDevice.Get(), m_pImmediateContext.Get(), D3DXVECTOR3(200, 10, 0), D3DXVECTOR3(0, 0, 0), m_pMainCamera->m_vPos, m_pMainCamera->m_vLookup);





	m_DebugLine.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShader.txt", nullptr, "VSLine", "PSLine");





	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);


	JDX::ApplySS(m_pImmediateContext.Get(), JDX::JH_DxState::g_pSamplerState);
	return true;
}
bool Sample::Frame()
{

	if (G_Input.KeyCheck(VK_F3) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext().Get(), JDX::JH_DxState::g_pRSSold);
	}
	if (G_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		JDX::ApplyRS(GetContext().Get(), JDX::JH_DxState::g_pRSWireFrame);
	}


	m_LightObj.Update(m_pMainCamera->m_vPos, m_pMainCamera->m_vLookup);
	m_LightObj.Frame();
	m_LightObj.m_cbLight.vLightPos.y = m_Map.GetHeight(m_LightObj.m_cbLight.vLightPos.x, m_LightObj.m_cbLight.vLightPos.z);

	m_LightObj.m_Obj.m_matWorld._42 = m_Map.GetHeight(m_LightObj.m_Pos.x, m_LightObj.m_Pos.z) + 20;
	//JH_DebugCamera* DebugCamera = (JH_DebugCamera*)m_pMainCamera;
	//DebugCamera->UpdateCameraHeight(m_Map.GetHeight(m_pMainCamera->m_vPos.x, m_pMainCamera->m_vPos.z) + 10);

	return true;
}
bool Sample::Render()
{
	m_Map.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Map.UpdateConstantBuffer(m_LightObj.m_pLightConstantBuffer.Get(), &m_LightObj.m_cbLight);
	//m_pImmediateContext->UpdateSubresource(m_pLightConstantBuffer.Get(), 0, nullptr, &m_cbLight, 0, 0);

	m_Map.m_dxHelper.m_pContext->VSSetConstantBuffers(1, 1, m_LightObj.m_pLightConstantBuffer.GetAddressOf());
	m_Map.m_dxHelper.m_pContext->PSSetConstantBuffers(1, 1, m_LightObj.m_pLightConstantBuffer.GetAddressOf());

	m_LightObj.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_LightObj.Render();

	m_Map.Render();


	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_DebugLine.Draw({ 0,0,0 }, { 1000,0,0 }, { 1,0,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,1000,0 }, { 0,1,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,0,1000 }, { 0,0,1,1 });



	return true;
}
bool Sample::Release()
{
	m_LightObj.Release();
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
