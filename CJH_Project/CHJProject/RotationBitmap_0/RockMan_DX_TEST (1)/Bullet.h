#pragma once

#include"JH_EffectMgr.h"


typedef vector<RECT> rtList;

class BulletInform
{
public:
	float	 fTimer;
	int		m_iIndex;
	D3DXVECTOR3 vBulletPos;
	DWORD	BulletState;
	bool   m_Direct;
public:
	bool Frame()
	{
		if (m_Direct)
		{
			vBulletPos.x -= 1000 * g_SecondPerFrame;
		}
		else
		{
			vBulletPos.x += 1000* g_SecondPerFrame;
		}

		fTimer += g_SecondPerFrame;
		
		if (m_iIndex >= 3)return true;
		


		if (fTimer > 0.3f / 4)
		{
			fTimer -= 0.3f / 4;
			if (m_iIndex < 3)
			{
				m_iIndex++;
			}
		}
	
		return true;
	}
	BulletInform() 
	{
		BulletState = 0;
		fTimer=0.0f;
		m_iIndex =0;

	}
	BulletInform(bool Direct,D3DXVECTOR3 vPos)
	{
		m_Direct = Direct;
		vBulletPos = vPos;
		BulletState = 0;
		fTimer = 0.0f;
		m_iIndex = 0;

	}
	
	void SetInform(bool Direct,D3DXVECTOR3 vPos)
	{
		m_Direct = Direct;
		vBulletPos = vPos;
	}
	virtual ~BulletInform(){}
};
enum SHOT
{
	SHOT=0,
	CHARGINGSHOT,
	SHOTCOUNT,
};
class JH_Bullet :public JH_Sprite
{
public:
	bool	m_Direct;
	DWORD	Key_State;
	float	m_fRetentiontime;
	vector<JrtLits> m_BulletUVList;
	vector<rtList> m_BulletRTList;
	DWORD	m_BulletState;
	D3DXVECTOR3 m_BulletPos;
	int     m_BulletCount;
	vector<BulletInform> m_vBulletList;
	int					m_Count;

	//void  SetMatrix(D3DXMATRIX* matWorld,
	//	D3DXMATRIX* matView,
	//	D3DXMATRIX* matProj);

	void SetInform(bool Direct, D3DXVECTOR3 vPos)
	{
		m_Direct = Direct;
		m_BulletPos = vPos;
	}
public:
	bool Init();
	bool Frame();
	bool PostRender()override;
	void SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime, DWORD EffectNum);
public:
	JH_Bullet();
	virtual ~JH_Bullet();
};

