#include "JHMapObj.h"


bool JHMapObj::Render()
{
	BitBlt(g_hOffScreenDC, 0, 0
		, g_rtClient.right, g_rtClient.bottom,
		m_BitMap->m_TempScreenDC, 0, 0,
		SRCCOPY);
	return true;
}
JHMapObj::JHMapObj()
{
}


JHMapObj::~JHMapObj()
{
}
