#include "Collision.h"
float  Collision::GetDistance(
	hPoint pt1, hPoint pt2)
{
	float fDistance = sqrt(
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y));
	return fDistance;
}
float  Collision::GetDistance(
	float aX, float aY, 
	float bX, float bY)
{
	float fDistance = sqrt(
		(aX - bX)*(aX - bX) +
		(aY - bY)*(aY - bY));
	return fDistance;
}
bool   Collision::SphereInPt(Sphere rt, POINT pt)
{
	hPoint pos = { (float)pt.x, (float)pt.y };
	float fDistance = GetDistance(rt.pt, pos);
	if (fDistance < rt.radius)
	{
		return true;
	}
	return false;
}
bool   Collision::SphereInPt(Sphere rt, hPoint pt)
{
	float fDistance = GetDistance(rt.pt, pt);
	if (fDistance < rt.radius)
	{
		return true;
	}
	return false;
}
bool   Collision::SphereInSphere(
	RECT rt1,
	RECT rt2)
{
	Sphere sA, sB;
	sA.pt.x = (rt1.right + rt1.left) / 2.0f;
	sA.pt.y = (rt1.bottom + rt1.top) / 2.0f;
	sA.radius = 
		GetDistance(rt1.left, rt1.top,
				    rt1.right, rt1.bottom);
	sB.pt.x = (rt2.right + rt2.left) / 2.0f;
	sB.pt.y = (rt2.bottom + rt2.top) / 2.0f;
	sB.radius = GetDistance(rt2.left, rt2.top,
		rt2.right, rt2.bottom);
	
	float fCtoC = GetDistance(sA.pt, sB.pt);

	if (fCtoC < sA.radius + sB.radius)
	{
		return true;
	}
	return false;
}
bool   Collision::SphereInSphere(
	Sphere rt1,
	Sphere rt2)
{
	float fCtoC = GetDistance(rt1.pt, rt2.pt);
	if (fCtoC < rt1.radius + rt2.radius)
	{
		return true;
	}
	return false;
}
bool   Collision::RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && 
		rt.right >= pt.x)
	{
		if (rt.top <= pt.y &&
			rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
bool   Collision::RectInRect(RECT rt1, RECT rt2)
{
	POINT minPos, maxPos;
	minPos.x = rt1.left > rt2.left ? rt2.left: rt1.left;
	minPos.y = rt1.top > rt2.top ? rt2.top : rt1.top;
	maxPos.x = rt1.right < rt2.right ? rt2.right : rt1.right;
	maxPos.y = rt1.bottom < rt2.bottom ? rt2.bottom : rt1.bottom;

	int iDistanceX = maxPos.x - minPos.x;
	int iDistanceY = maxPos.y - minPos.y;

	if ( ((rt1.right-rt1.left) + (rt2.right - rt2.left))
		>= iDistanceX)
	{
		if (((rt1.bottom - rt1.top) + (rt2.bottom - rt2.top))
			>= iDistanceY)
		{
			return true;
		}
	}
	return false;
}
Collision::Collision()
{
}


Collision::~Collision()
{
}
