#pragma once
#include"SpriteObj.h"
#include"JH_Input.h"
enum Shot
{
	SHOT_SPECTRUM,
	SHOT,
	SHOT_COUNT,
};
class ShotEffect:public SpriteObj
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	ShotEffect();
	virtual ~ShotEffect();
};

