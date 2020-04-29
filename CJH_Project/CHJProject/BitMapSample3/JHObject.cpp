#include "JHObject.h"


void JHObject::DrawRotateBlt()
{
	
}
bool JHObject::DrawRotate()
{

	HBITMAP hBitMap = GetRotateBitMap(m_BitMap->m_TempScreenDC, m_hRotationDC, m_fAngle,
		m_fRotateSize, m_fRotateSize);
	HBITMAP PrehBitMap = (HBITMAP)SelectObject(m_hMemDC, hBitMap);

	DrawRotateBlt();
	SelectObject(m_hMemDC, PrehBitMap);
	DeleteObject(hBitMap);
	return true;
}
HBITMAP JHObject::GetRotateBitMap(HDC m_hSrcDC, HDC hRotationDC,
	float Angle, float fSizeX, float fSizeY)// 회전된 비트맵 넘기기
{
	HBITMAP hRetBitMap = CreateCompatibleBitmap(g_hScreenDC, fSizeX, fSizeY);
	HBITMAP oldBitMap=(HBITMAP)SelectObject(hRotationDC, hRetBitMap);
	SelectObject(hRotationDC, m_bkBrush);

	PatBlt(hRotationDC, 0, 0, fSizeX, fSizeY, PATCOPY);

	int OldMode = SetGraphicsMode(hRotationDC, GM_ADVANCED);// 수직 좌표계로 변경 나중에 다시 변경해야되므로 저장

	float fRadian = DegreeToRadian(Angle);
	float fCosine = cos(fRadian);
	float fSine = sin(fRadian);

	XFORM xForm; //행렬 생성

	xForm.eM11 = fCosine;
	xForm.eM12 = fSine;
	xForm.eM21 = -fSine;
	xForm.eM22 = fCosine;
	xForm.eDx = fSizeX / 2;
	xForm.eDy = fSizeY / 2;

	SetWorldTransform(hRotationDC, &xForm);//형태변환

	BitBlt(hRotationDC,
		-m_rtSrc.right / 2,
		-m_rtSrc.bottom / 2,
		m_rtSrc.right, m_rtSrc.bottom,
		m_hSrcDC, m_rtSrc.left, m_rtSrc.top,
		SRCCOPY); //이미지 뿌려서 회전된 이미지 만들기
	xForm.eM11 = 1;	xForm.eM12 = 0;
	xForm.eM21 = 0;	xForm.eM22 = 1;
	xForm.eDx = 0;
	xForm.eDy = 0;
	SetWorldTransform(hRotationDC, &xForm);// 복원

	SetGraphicsMode(hRotationDC, OldMode);
	SelectObject(hRotationDC, oldBitMap);

	return hRetBitMap;
}
bool JHObject::Init()
{
	m_BlendFunction.AlphaFormat =
		AC_SRC_ALPHA;
	m_BlendFunction.BlendFlags =
		0;
	m_BlendFunction.BlendOp =
		AC_SRC_OVER;
	m_BlendFunction.SourceConstantAlpha =
		255;

	m_hMemDC = CreateCompatibleDC(g_hScreenDC);
	m_hRotationDC = CreateCompatibleDC(g_hScreenDC);
	COLORREF bkColor = RGB(255, 255, 255);
	m_bkBrush = CreateSolidBrush(bkColor);

	m_BitMap->Init();
	return true;
}
bool JHObject::Render()
{
	m_BitMap->Render();
	return true;
}
bool JHObject::Frame()
{
	m_BitMap->Frame();
	return true;
}
bool JHObject::Release()
{
	ReleaseDC(g_hwnd, m_hMemDC);
	ReleaseDC(g_hwnd, m_hRotationDC);
	DeleteObject(m_bkBrush);
	m_BitMap->Release();
	return true;
}
bool JHObject::Load(const TCHAR* pFileName, const TCHAR*pMaskFileName)
{
	assert(pFileName);
	m_BitMap=BM_MGR.Load(pFileName);
	if (pMaskFileName != nullptr)
	{
		m_MaskBitMap=BM_MGR.Load(pMaskFileName);
	}
	return true;

}
void JHObject:: SetPosition(float x, float y)
{
	m_fPosX = x;
	m_fPosY = y;
}
void JHObject::SetSrcRect(RECT rt)
{
	m_rtSrc = rt;
	float x = m_rtSrc.right;
	float y = m_rtSrc.bottom;
	m_fRotateSize = sqrt(x*x + y * y);
}
