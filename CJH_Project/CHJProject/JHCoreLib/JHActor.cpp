#include "JHActor.h"

//void JHActor::DrawRotateBlt()
//{
//	m_rtDest.left = m_fPosX - (m_fRotateSize / 2);
//	m_rtDest.top = m_fPosY - (m_fRotateSize / 2);
//	m_rtDest.right = m_fRotateSize;
//	m_rtDest.bottom = m_fRotateSize;
//
//	
//	AlphaBlend(g_hOffScreenDC,
//		m_rtDest.left,
//		m_rtDest.top,
//		m_rtDest.right,
//		m_rtDest.bottom,
//
//		m_hMemDC,
//		0, 0,
//		m_rtDest.right, m_rtDest.bottom,
//		m_BlendFunction); // ¼Ò½º
//	
//}
bool  JHActor::SetSRC(RECT rt)
{
	m_rtSrc = rt;
	m_rtDest.left = m_fPosX;
	m_rtDest.top = m_fPosY;
	m_rtDest.right = m_rtSrc.right;
	m_rtDest.bottom = m_rtSrc.bottom;

	float x = m_rtSrc.right;
	float y = m_rtSrc.bottom;
	m_fRotateSize = sqrt(x*x + y * y);
	return true;
}
	
void  JHActor::SetPosition(float x, float y)
{
	m_fPosX = x;
	m_fPosY = y;
	m_rtDest.left = m_fPosX - (m_rtSrc.right / 2);
	m_rtDest.top = m_fPosY - (m_rtSrc.bottom / 2);
	m_rtDest.right = m_rtSrc.right;
	m_rtDest.bottom = m_rtSrc.bottom;;
}
JHActor::JHActor()
{
}


JHActor::~JHActor()
{
}
