#pragma once
#include"JH_Sprite.h"
#include"JH_DXStd.h"


typedef vector<RECT> rtList;
enum PlayerEffect
{
	CHARGING=0,
	SHOT_BE_ATTACKED,
	HITING,
	SHOT_SPECTRUM,
	CHARGINGSHOT_SPECTRUM,
	EFFECT_COUNT,
};
class  PlayerEffectInform
{
public:
	D3DXVECTOR3	m_EffectPos;
	DWORD m_EffectState;
	float		m_fTimer;
	int			m_iIndex;
	float		m_fOffsetTime;
	bool		m_Direct;
	int			m_MaxIndex;
public:
	void SetEffect(DWORD EffectState, D3DXVECTOR3	EffectPos,int MaxIndex,bool Direct)
	{
		m_EffectState = EffectState;
		m_EffectPos = EffectPos;
		m_MaxIndex = MaxIndex;
		m_Direct = Direct;
	
	}
	bool Frame()
	{
		
		
		if (m_iIndex >= m_MaxIndex)return true;
			m_fTimer += g_SecondPerFrame;

			



			if (m_fTimer > 0.15f / m_MaxIndex)
			{
				m_fTimer -= 0.15f / m_MaxIndex;
				if (m_iIndex < m_MaxIndex)
				{
					m_iIndex++;
				}
			}



		return true;
	}
	PlayerEffectInform()
	{
		m_EffectPos= D3DXVECTOR3(0,0,0);
		m_EffectState= 0;
		m_fTimer=0.0f;
		m_iIndex=0;
		m_MaxIndex = 0;
		m_fOffsetTime=0.0f;
	}
	~PlayerEffectInform()
	{
	}

};

 
class JH_EffectMgr :public JH_Sprite
{
public:
	bool b_Waiting;

	D3DXVECTOR3 g_PlayerPos;
	vector<JrtLits> m_EffectUVList;
	vector<rtList> m_EffectRTList;
	vector< PlayerEffectInform> m_EInformList;
	DWORD		m_EffectState;
public:
	bool SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime,DWORD EffectNum);
	void SetEffectState(DWORD &EffectState);
	static shared_ptr<JH_EffectMgr>&Get()
	{
		static shared_ptr<JH_EffectMgr> mgr;
		return mgr;
	}
	bool Init();
	bool Frame();
	bool PostRender();
	bool Release();
	JH_EffectMgr();
	virtual ~JH_EffectMgr();
};

#define I_EffectMgr JH_EffectMgr::Get()