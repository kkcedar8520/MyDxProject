#include "Sample.h"
#include"JH_DxState.h"

bool	Sample::Init()
{
	m_tempMap.Create(
		m_pd3dDevice,
		m_pImmediateContext,
		L"../../data/shader/DefaultShader.txt",
		L"../../data/Resource/start.bmp",
			"VSLine",
			"PSLine");
	//ZeroMemory(&descSamp, sizeof(D3D11_SAMPLER_DESC));
	//descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//descSamp.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	//descSamp.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	//descSamp.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	//JDX::JH_DxState::SetSamplerState(GetDevice(),
	//	GetContext(), &descSamp);

	//ZeroMemory(&bs, sizeof(D3D11_BLEND_DESC));
	////bs.AlphaToCoverageEnable;
	//bs.IndependentBlendEnable = TRUE;;
	//bs.RenderTarget[0].BlendEnable = TRUE;
	//bs.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//bs.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//JDX::JH_DxState::SetBlendState(GetDevice(), GetContext(), &bs);

	////m_Box = make_shared< TAnimBox>();
	////m_Box->Create(
	////	m_pd3dDevice,
	////	m_pImmediateContext,
	////	L"ColorBlend.txt",
	////	L"../../data/effect/lot_wik00.dds");

	////std::vector<wstring> texList;
	////m_Box->m_srvList.resize(24);
	////for (int i = 0; i < 24; i++)
	////{
	////	TCHAR buffer[50] = { 0, };
	////	if (i <= 9)
	////	{
	////		_stprintf_s(buffer, L"lot_wik0%d.dds", i);
	////	}
	////	else
	////	{
	////		_stprintf_s(buffer, L"lot_wik%d.dds", i);
	////	}
	////	wstring path = L"../../data/effect/";
	////	path += buffer;
	////	texList.push_back(path);
	////	D3DX11CreateShaderResourceViewFromFile(
	////		m_pd3dDevice,
	////		path.c_str(),
	////		NULL,
	////		NULL,
	////		m_Box->m_srvList[i].GetAddressOf(),
	////		NULL);
	////}

	//JH_ShapePlane* pObj = new JH_ShapePlane;
	//m_planeObj.reset(pObj);
	//m_planeObj->Create(
	//	m_pd3dDevice,
	//	m_pImmediateContext,
	//	L"../../data/shader/DefaultShader.txt",
	//	L"../../data/circleDust.png");
	//m_map = make_shared< JH_ShapePlane>();
	//m_map->Create(
	//	m_pd3dDevice,
	//	m_pImmediateContext,
	//	L"../../data/shader/DefaultShader.txt",
	//	L"../../data/effect/skullhead.dds");

	//m_rtList.resize(10);
	//m_rtList[0] = { 76,490,63,52 };
	//m_rtList[1] = { 139,490,63,52 };
	//m_rtList[2] = { 203,490,63,52 };
	//m_rtList[3] = { 276,490,63,52 }; //RUN SHOT
	//m_rtList[4] = { 343,490,63,52 };
	//m_rtList[5] = { 404,490,63,52 };
	//m_rtList[6] = { 462,490,63,52 };
	//m_rtList[7] = { 521,490,63,52 };
	//m_rtList[8] = { 583,490,63,52 };
	//m_rtList[9] = { 651,490,63,52 };

	//m_hero->SetArrayRect(m_rtList, 788, 1108, 1.0f);
	//m_vPos = D3DXVECTOR3(0.0, 0.0, 40.0f);

	//m_hero = make_shared< JH_Sprite>();
	//m_hero->Create(
	//	m_pd3dDevice,
	//	m_pImmediateContext,
	//	L"../../data/shader/DefaultShader.txt",
	//	L"../../data/bitmap/ROCKMAN2colorAlpha");
	//m_Line = make_shared< JH_ShapeLine>();
	//m_Line->Create(
	//	m_pd3dDevice,
	//	m_pImmediateContext,
	//	L"../../data/shader/DefaultShader.txt",
	//	NULL,
	//	"VSLine",
	//	"PSLine");

	//ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	//ApplySS(GetContext(), JH_DxState::g_pSamplerState);
	//ApplyRS(GetContext(), JH_DxState::g_pRSSold);
	//ApplyDSS(GetContext(), JH_DxState::g_pDSS);


	//m_pMainCamera->SetViewProj(,,,,,);
	return true;
}
bool	Sample::Frame()
{
	//if (G_Input.KeyCheck(VK_F1) == KEY_PUSH)
	//{
	//	ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	//}
	//if (G_Input.KeyCheck(VK_F2) == KEY_PUSH)
	//{
	//	ApplyBS(GetContext(),
	//		JH_DxState::g_pAlpahBlendDisable);
	//}
	//if (G_Input.KeyCheck(VK_F3) == KEY_PUSH)
	//{
	//	ApplyRS(GetContext(), JH_DxState::g_pRSSold);
	//}
	//if (G_Input.KeyCheck(VK_F4) == KEY_PUSH)
	//{
	//	ApplyRS(GetContext(), JH_DxState::g_pRSWireFrame);
	//}
	//if (G_Input.KeyCheck('1') == KEY_PUSH)
	//{
	//	static int iAddress = 1;
	//	iAddress++;
	//	if (iAddress > 5) iAddress = 1;
	//	descSamp.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)iAddress;
	//	descSamp.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)iAddress;
	//	descSamp.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)iAddress;
	//	JDX::JH_DxState::SetSamplerState(GetDevice(), GetContext(), &descSamp);
	//}
	//if (G_Input.KeyCheck('2') == KEY_PUSH)
	//{
	//	static bool bAlpha = true;
	//	bAlpha = !bAlpha;
	//	if (bAlpha == false)
	//	{
	//		bs.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//		bs.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//		bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//	}
	//	else
	//	{
	//		bs.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//		bs.RenderTarget[0].DestBlend = D3D11_BLEND_SRC1_COLOR;
	//		bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//	}
	//	JDX::JH_DxState::SetBlendState(GetDevice(), GetContext(), &bs);
	//}
	//if (G_Input.KeyCheck('W') != KEY_FREE)
	//{
	//	m_pMainCamera->m_vPos.z = m_pMainCamera->m_vPos.z +
	//		50.0f * g_SecondPerFrame;
	//}
	//if (G_Input.KeyCheck('S') != KEY_FREE)
	//{
	//	m_pMainCamera->m_vPos.z = m_pMainCamera->m_vPos.z -
	//		50.0f * g_SecondPerFrame;
	//}
	//if (G_Input.KeyCheck('A') != KEY_FREE)
	//{
	//	m_vPos = m_vPos + D3DXVECTOR3(-50, 0.0f, 0.0f) * g_SecondPerFrame;
	//
	//}
	//if (G_Input.KeyCheck('D') != KEY_FREE)
	//{
	//	m_vPos = m_vPos + D3DXVECTOR3(50, 0.0f, 0.0f) * g_SecondPerFrame;
	//
	//}

	//m_Box->m_matWorld._41 = m_vPos.x;
	//m_Box->m_matWorld._42 = m_vPos.y;

	m_pMainCamera->m_vPos.x = m_vPos.x;
	m_pMainCamera->m_vAt.x = m_vPos.x;

	//m_planeObj->Frame();
	return true;
}
//The Pixel Shader unit expects a Sampler to be set at Slot 0,
bool	Sample::Render()
{
	m_tempMap.SetMatrix(nullptr, &m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);
	m_tempMap.Render();
	/*ApplyDSS(GetContext(), JH_DxState::g_pDSS);
	ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	ApplySS(GetContext(), JH_DxState::g_pSSEdit.Get());
	m_map->m_matWorld._11 = 1000.0f;
	m_map->m_matWorld._22 = 300.0f;
	m_map->m_matWorld._43 = 50.0f;
	m_map->m_cbData.d.y = 10;
	m_map->m_cbData.d.z = 5;
	m_map->SetMatrix(nullptr,
		&m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);
	m_map->Render();

	ApplyBS(GetContext(), JH_DxState::g_pBSEdit.Get());
	ApplySS(GetContext(), JH_DxState::g_pSamplerState);
	D3DXMATRIX matScale, matRotation, matWorld;
	D3DXMatrixScaling(&matScale, 10.0f, 10.0f, 10.0f);
	D3DXMatrixRotationY(&matRotation, 0);
	matWorld = matScale * matRotation;
	matWorld._41 = m_vPos.x;
	matWorld._42 = m_vPos.y;
	matWorld._43 = m_vPos.z;
	m_Box->SetMatrix(&matWorld, &m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);
	m_Box->Render();*/

	//m_planeObj->m_matWorld._11 = 400.0f;
	//m_planeObj->m_matWorld._22 = 300.0f;
	//m_planeObj->m_matWorld._43 = 1.0f;
	//m_planeObj->SetMatrix(nullptr, nullptr, 
	//	&m_pMainCamera->m_matOrthoProj);
	//m_planeObj->Render();

	/*ApplyBS(GetContext(), JH_DxState::g_pAlpahBlend);
	ApplyDSS(GetContext(), JH_DxState::g_pDSSDisable);
	D3DXMatrixRotationZ(&matWorld, 0);
	m_Line->SetMatrix(nullptr, &m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);
	D3DXVECTOR3 vS = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vE = D3DXVECTOR3(0, 1000, 0);
	D3DXVec3TransformCoord(&vE, &vE, &matWorld);
	m_Line->Draw(vS, vE, D3DXVECTOR4(1, 1, 0, 1));*/
	return true;
}
bool	Sample::Release()
{
	/*m_Box->Release();
	m_Line->Release();
	m_map->Release();
	m_hero->Release();
	m_planeObj->Release();*/

	return true;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}


//#include "Sample.h"
//
//
//bool	Sample::Init()
//{
//	m_Box = make_shared<JHShapeBox>();
//	
//	m_Box->Create(m_pd3dDevice, m_pImmediateContext,
//		L"DefaultShader.txt",L"circleDust.png");
//	
//
//	ApplyBS(m_pImmediateContext, JH_DxState::g_pAlpahBlend);
//	ApplyRS(m_pImmediateContext, JH_DxState::g_pRSSold);
//	ApplyDSS(m_pImmediateContext, JH_DxState::g_pDSS);
//	ApplySS(m_pImmediateContext, JH_DxState::g_pSamplerState);
//
//	
//	return true;
//
//}
//bool	Sample::Frame()
//{
//	if (JH_DxState.KeyCheck('W'))
//	{
//		m_pMainCamera->m_vPos = m_pMainCamera->m_vPos + D3DXVECTOR3(0, 0, 50.0f);
//	}
//	if (JH_DxState.KeyCheck('S'))
//	{
//		m_pMainCamera->m_vPos = m_pMainCamera->m_vPos + D3DXVECTOR3(0, 0,-50.0f);
//	}
//	if (JH_DxState.KeyCheck('A'))
//	{
//		m_vPos=m_vPos+ m_vPos + D3DXVECTOR3(0, 0, -50.0f);
//	}
//	if (JH_DxState.KeyCheck('D'))
//	{
//		m_vPos = m_vPos + m_vPos + D3DXVECTOR3(0, 0, 50.0f);
//	}
//	
//	m_Box->m_matWorld._41 = m_vPos.x;
//	m_Box->m_matWorld._42 = m_vPos.y;
//
//	m_pMainCamera->m_vPos.x = m_vPos.x;
//	m_pMainCamera->m_vAt.x = m_vPos.x;
//
//	m_Box->Frame();
//	return true;
//}
//bool	Sample::Render()
//{
//
//
//	D3DXMATRIX matScale, matRotation, matWorld;
//	D3DXMatrixScaling(&matScale, 10.0f, 10.0f, 10.0f);
//	D3DXMatrixRotationY(&matRotation, 0);
//	matWorld = matScale * matRotation;
//	matWorld._41 = m_vPos.x;
//	matWorld._42 = m_vPos.y;
//	matWorld._43 = m_vPos.z;
//	m_Box->SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
//	
//	m_Box->Render();
//	return true;
//
//}
//bool	Sample::Release()
//{
//	m_Box->Release();
//	return true;
//
//}
//Sample::Sample()
//{
//}
//
//
//Sample::~Sample()
//{
//}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,800,600 };
	if (!game.InitWindow(L"Refactoring", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}