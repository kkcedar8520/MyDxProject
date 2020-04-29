#pragma once
#include"JHBitMap.h"
#include"JH_Std.h"
#include"HCore.h"
#include<time.h>
#include<assert.h>
#include"JHObjList.h"
#include<vector>
#include<list>

using namespace std;
class Sample :public HCore
{
public:
	JHObject* m_pMap;
	JHObject* m_pNpc[10];
	JHObject* m_pPlayer;
	HCore game;
	std::list<JHObject*>m_GameObjectList;
	//JHEffectObj m_Effect;
public:
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
	Sample();
	~Sample();
};