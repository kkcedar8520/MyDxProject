#include "JHPlayerObj.h"



bool JHPlayerObj::Frame()
{

	if (m_Input.KeyCheck('W'))
	{
		m_fPosY -= 300 * g_SecondPerFrame;
		if (m_fPosY < 0)
		{
			m_fPosY = 0;
		}
	}
	if (m_Input.KeyCheck('S')) 
	{
		m_fPosY += 300 * g_SecondPerFrame;
		if (m_fPosY > 1142)
		{
			m_fPosY = 1142;
		}
	}
	if (m_Input.KeyCheck('A'))
	{
		m_fPosX -= 300 * g_SecondPerFrame;
		if (m_fPosX < 0)
		{
			m_fPosX = 0;
		}
	}
	if (m_Input.KeyCheck('D'))
	{
		m_fPosX += 300 * g_SecondPerFrame;
		if (m_fPosX > 760)
		{
			m_fPosX = 760;
		}
		return true;
	}
	if (m_Input.KeyCheck(VK_RIGHT))
	{
		m_fAngle += 100 * g_SecondPerFrame;
	}
	if (m_Input.KeyCheck(VK_LEFT))
	{
		m_fAngle -= 100 * g_SecondPerFrame;
	}
	/*static float fAlpha = 255;
	fAlpha -= g_SecondPerFrame * 0.2f * 255; ///상수알파 추가
	if (fAlpha < 0)
	{
		fAlpha = 255;
	}
	m_BlendFunction.SourceConstantAlpha
		= fAlpha;*/
	return true;
}
bool JHPlayerObj::Render()
{
	//BitBlt(g_hOffScreenDC,
	//	m_fPosX,
	//	m_fPosY,
	//	m_rtSrc.right,
	//	m_rtSrc.bottom, //  대상

	//	m_MaskBitMap.m_TempScreenDC,
	//	m_rtSrc.left,
	//	m_rtSrc.top,
	//	SRCAND); // 소스

	//BitBlt(g_hOffScreenDC,
	//	m_fPosX,
	//	m_fPosY,
	//	m_rtSrc.right,
	//	m_rtSrc.bottom, //  대상

	//	m_BitMap->m_TempScreenDC,
	//	m_rtSrc.left,
	//	m_rtSrc.top,
	//	SRCINVERT); // 소스

	//BitBlt(g_hOffScreenDC,
	//	m_fPosX,
	//	m_fPosY,
	//	m_rtSrc.right,
	//	m_rtSrc.bottom, //  대상

	//	m_MaskBitMap.m_TempScreenDC,
	//	m_rtSrc.left,
	//	m_rtSrc.top,
	//	SRCINVERT); // 소스
	AlphaBlend(g_hOffScreenDC,
		m_fPosX,
		m_fPosY,
		m_rtSrc.right,
		m_rtSrc.bottom,

		m_BitMap->m_TempScreenDC,
		m_rtSrc.left,
		m_rtSrc.top,
		m_rtSrc.right,
		m_rtSrc.bottom,
		m_BlendFunction); // 소스
	return true;
}
