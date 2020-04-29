#include "Sample.h"
#include"JH_DxState.h"
#include"JH_Input.h"
#include "JH_ShapePlane.h"
#pragma warning( disable:4005 )



bool Sample::Init()
{
	m_pLightConstantBuffer[0].Attach(DX::MakeConstantBuffer(m_pd3dDevice,&m_cbLight,sizeof(LightConstantBuffer),1));



	m_Map.CreateHeightMap(m_pd3dDevice, m_pImmediateContext, L"../../data/map/heightMap513.bmp");


	m_Map.SetMapDesc(L"../../data/map/Tile20.jpg", L"LightShader.txt", m_Map.m_iColumNum, m_Map.m_iRowNum, 1, 5.0f);

	m_Map.Load(m_pd3dDevice, m_pImmediateContext);

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();

	LightInfo LInfo;
	LInfo.EyeDir = m_pMainCamera->m_vLookup;
	LInfo.EyePos = m_pMainCamera->m_vPos;
	LInfo.Attenuation = 30;
	LInfo.LightPos = D3DXVECTOR3(100, 20, 100);
	LInfo.At = D3DXVECTOR3(0, 0, 0);
	
	m_LightObjList[0].SetLightInfo(m_pd3dDevice, m_pImmediateContext,
		LInfo);

	LInfo.LightPos = D3DXVECTOR3(-100,20,-100);
	LInfo.At = D3DXVECTOR3(0, 0, 0);

	m_LightObjList[1].SetLightInfo(m_pd3dDevice, m_pImmediateContext,
		LInfo);


	for (int i = 0; i < g_iLightNum; i++)
	{
		
		m_LightObjList[i].m_Obj.Create(m_pd3dDevice, m_pImmediateContext, L"LightShader.txt", L"../../data/Resource/powerbattles_title.gif");

		m_cbLight.vAmbinentLightColor[i] = { 0.3,0.3,0.3,1 };
		m_cbLight.vDiffuseLightColor[i] = { 1,1,1,1 };
		m_cbLight.vSpecularLightColor[i] = { 1,1,1,1 };
		m_cbLight.vSpotLightColor[i] = { 1,1,1,1 };

		m_cbLight.vEyeDirection[i] = { m_LightObjList[i].m_Info.EyeDir,1.0f };
		m_cbLight.vEyePos[i] = { m_LightObjList[i].m_Info.EyePos,1.0f };

		m_cbLight.vLightDirection[i] = { m_LightObjList[i].m_Info.LightDir ,1.0f};
		m_cbLight.vLightPos[i] = { m_LightObjList[i].m_Info.LightPos ,1.0f };

		m_cbLight.vSpotLight[i].x = cosf(D3DX_PI/4.0);
		m_cbLight.vSpotLight[i].y = cosf(D3DX_PI / 3.0);
		m_cbLight.vSpotLight[i].z = 50;
		m_cbLight.vSpotLight[i].w = 100;
		
	}






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


	for (int i = 0; i < g_iLightNum; i++)
	{
		m_LightObjList[i].Update(m_pMainCamera->m_vPos, m_pMainCamera->m_vLookup);
		m_LightObjList[i].Frame();

		m_cbLight.vEyeDirection[i] = { m_LightObjList[i].m_Info.EyeDir,1.0f };;
		m_cbLight.vEyePos[i] = { m_LightObjList[i].m_Info.EyePos,1.0f };

		m_cbLight.vLightDirection[i] = { m_LightObjList[i].m_Info.LightDir,1.0f };;
		m_cbLight.vLightPos[i] = { m_LightObjList[i].m_Info.LightPos ,1.0f };;

	}

	
	


	
	//JH_DebugCamera* DebugCamera = (JH_DebugCamera*)m_pMainCamera;
	//DebugCamera->UpdateCameraHeight(m_Map.GetHeight(m_pMainCamera->m_vPos.x, m_pMainCamera->m_vPos.z) + 10);

	return true;
}
bool Sample::Render()
{
	m_Map.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	ID3D11Buffer*               pBuffers[3];
	pBuffers[0] = m_pLightConstantBuffer[0].Get();

	m_Map.UpdateConstantBuffer(m_pLightConstantBuffer[0].Get(), &m_cbLight);

	
	


	//m_pImmediateContext->UpdateSubresource(m_pLightConstantBuffer.Get(), 0, nullptr, &m_cbLight, 0, 0);

	
	m_Map.m_dxHelper.m_pContext->PSSetConstantBuffers(1, 1, pBuffers);
	//m_Map.m_dxHelper.m_pContext->PSSetConstantBuffers(2, 1, m_pLightConstantBuffer->GetAddressOf());

	for (int i = 0; i < g_iLightNum; i++)
	{
		m_LightObjList[i].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_LightObjList[i].Render();
	}
	
	

	m_Map.Render();


	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_DebugLine.Draw({ 0,0,0 }, { 1000,0,0 }, { 1,0,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,1000,0 }, { 0,1,0,1 });
	m_DebugLine.Draw({ 0,0,0 }, { 0,0,1000 }, { 0,0,1,1 });



	return true;
}
bool Sample::Release()
{
	
	for (int i = 0; i < g_iLightNum; i++)
	{
		
		m_LightObjList[i].Release();
	}
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
