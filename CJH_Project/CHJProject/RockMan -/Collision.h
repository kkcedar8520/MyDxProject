#pragma once
#include "JH_Std.h"
struct Sphere
{
	hPoint pt;
	float radius;
};
class Collision
{
public:
	bool   RectInPt(RECT rt1, POINT pt);
	bool   RectInRect(RECT rt1, RECT rt2);
	bool   SphereInPt(Sphere rt, POINT pt);
	bool   SphereInPt(Sphere rt, hPoint pt);
	bool   SphereInSphere(Sphere rt1,
		Sphere rt2);
	bool   SphereInSphere(
		RECT rt1,
		RECT rt2);
	float  GetDistance(
		float aX, float aY,
		float bX, float bY);
	float  GetDistance(
		hPoint, hPoint);
public:
	static Collision& Get()
	{
		static Collision mgr;
		return mgr;
	}
public:
	Collision();
	virtual ~Collision();
};

#define Col Collision::Get()