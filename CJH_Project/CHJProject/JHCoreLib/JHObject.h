#pragma once
#include"JHBitMap.h"
#include"JH_Std.h"
#include"JHBitmapManager.h"
extern RECT g_rtClient;




class JHObject
{

public:
	RECT m_rtDest;

protected:
	BLENDFUNCTION m_BlendFunction;
public:
	JHBitMap* m_BitMap;
	JHBitMap* m_MaskBitMap;
	float    m_fPosX;
	float    m_fPosY;
	float	 m_fDirX;
	float	 m_fDirY;
	float	 m_fAngle;
	RECT	 m_rtSrc;
	HDC		 m_hRotationDC;
	HDC		 m_hMemDC;
	HBRUSH   m_bkBrush;
	float	 m_fRotateSize;
public:
	virtual void DrawRotateBlt();
	bool DrawRotate();
	HBITMAP GetRotateBitMap(HDC m_hSrcDC, HDC hRotationDC,
		float Angle, float fSizeX, float fSizeY);// 회전된 비트맵 넘기기
	


	hPoint GetPositoin()
	{
		hPoint pos;
		pos.x = m_fPosX;
		pos.y = m_fPosY;
		return  pos;
	}

	virtual bool Init();
	virtual bool Render();
	virtual bool Frame();
	virtual bool Release();
	virtual bool Load(const TCHAR* pFileName, const TCHAR*pMaskFileName = nullptr);
	virtual void SetPosition(float x, float y);
	virtual void SetSrcRect(RECT rt);
public:
	JHObject()
	{
		m_fPosX = 0;
		m_fPosY = 0;
		m_fAngle = 0.0f;
	}
	~JHObject() 
	{

	}
};

