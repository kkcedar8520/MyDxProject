#include "JHNpcObj.h"


bool JHNpcObj::Init()
{

	JHObject::Init();
	m_fDirX = 1.0f;
	m_fDirY = 1.0f;
	m_fPosX = rand() % g_rtClient.right;
	m_fPosY = rand() % g_rtClient.bottom;
	SetPosition(m_fPosX, m_fPosY);
	m_fSpeed = 1 + rand() % 300;
	return true;
}
bool JHNpcObj::Render()
{
	BitBlt(g_hOffScreenDC,
		m_fPosX,
		m_fPosY,
		m_rtSrc.right,
		m_rtSrc.bottom, //  대상

		m_MaskBitMap->m_TempScreenDC,
		m_rtSrc.left,
		m_rtSrc.top,
		SRCCOPY); // 소스

	BitBlt(g_hOffScreenDC,
		m_fPosX,
		m_fPosY,
		m_rtSrc.right,
		m_rtSrc.bottom,

		m_BitMap->m_TempScreenDC,
		m_rtSrc.left,
		m_rtSrc.top,
		SRCCOPY);
	return true;
}
bool JHNpcObj::Frame()
{
	if (m_fPosX > g_rtClient.right)
	{
		m_fPosX = g_rtClient.right;
		m_fDirX *= -1.0f;
	}
	if (m_fPosX < 0)
	{
		m_fPosX = 0;
		m_fDirX *= -1.0f;
	}
	if (m_fPosY > g_rtClient.bottom)
	{
		m_fPosY = g_rtClient.bottom;
		m_fDirY *= -1.0f;
	}
	if (m_fPosY < 0)
	{
		m_fPosY = 0;
		m_fDirY *= -1.0f;
	}

	m_fPosX += m_fDirX * m_fSpeed * g_SecondPerFrame;
	m_fPosY += m_fDirY * m_fSpeed * g_SecondPerFrame;
	return true;

}