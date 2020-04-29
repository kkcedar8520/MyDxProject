#pragma once
#include "ShotEffect.h"

bool ShotEffect::Init()
{
	JHObject::Init();
	m_dRtList.resize(SHOT_COUNT);
	m_dRtList[SHOT_SPECTRUM].resize(4);
	m_dRtList[SHOT].resize(4);
	
	m_dRtList[0][0] = { 153,266, 23, 22 };
	m_dRtList[0][1] = { 191,266, 33, 22 };
	m_dRtList[0][2] = { 238,262, 38, 25 };
	m_dRtList[0][3] = { 293,261, 42, 28 };


	m_dRtList[1][0] = { 355,266, 23, 18 };
	m_dRtList[1][1] = { 393,269, 23, 13 };
	m_dRtList[1][2] = { 430,269, 23, 13 };
	m_dRtList[1][3] = { 467,266, 23, 22 };

	return true;
}
bool ShotEffect::Frame()
{

	m_fTimer += g_SecondPerFrame;
	if (m_fTimer > m_fOffsetTime)
	{
		m_fTimer -= m_fOffsetTime;
		m_SpriteIndex++;
	}
	if (true)
	{

	}
	if (G_Input.KeyCheck(VK_CONTROL));
	{
		SetRTList(m_dRtList[SHOT_SPECTRUM],m_dRtList[SHOT]);
		Set(m_rtList, 1.0f, true);
		m_rtSrc = m_rtList[m_SpriteIndex];
		m_rtEffectSrc = m_rtList_2[m_SpriteIndex];
	}
	return true;
}
bool ShotEffect::Render()
{
	AlphaBlend()
	return true;
}
bool ShotEffect::Release()
{
	return true;
}

ShotEffect::ShotEffect()
{
}


ShotEffect::~ShotEffect()
{
}
