#pragma once
#include"HCore.h"
#include"JH_Std.h"
#include"JHEffectObj.h"

class SprEffect:public JHEffectObj
{
public:
	vector<RECT> m_rtList;
	SprEffect();
	~SprEffect();

private:

};

SprEffect::SprEffect()
{
}

SprEffect::~SprEffect()
{
}