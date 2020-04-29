#include "JHEffectObj.h"


bool JHEffectObj::Render()
{
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
		m_BlendFunction); // ¼Ò½º
	return true;
}
bool JHEffectObj::Frame()
{
	static float fAlpha = 255;
	fAlpha -= g_SecondPerFrame * 0.2f * 255;
	if (fAlpha < 0)
	{
		fAlpha = 255;
	}
	m_BlendFunction.SourceConstantAlpha
		= fAlpha;
	return true;
}

