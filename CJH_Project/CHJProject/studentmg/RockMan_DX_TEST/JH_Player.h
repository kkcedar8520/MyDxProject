#pragma once
#include"Bullet.h"

struct Sphere
{
	float radius;

};
	enum PlayerState
	{
		STAND = 0,
		RUN,
		JUMP,
		BE_ATTACKED,
		BE_ATTACKED2,
		DEAD,
		PLAYERCOUNT,
	};


	typedef vector<RECT> rtList;
	class JH_Player :public JH_Sprite
	{
	public:
		DWORD d_CurrentState;
		DWORD d_PastState;
		DWORD d_StandState;
		DWORD d_LeftRUNState;
		DWORD d_RightRUNState;
		float m_fSecond;
		float m_fSpeed;
		bool b_Jumping;
		bool b_Stand;
		bool b_Right;
		static bool b_Left;
		bool b_Attacked;
		bool b_Dead;
		float	m_fTimer;
		int	m_JSpriteIndex;
	public:
		D3DXMATRIX	m_matWorldLeft;
		static D3DXVECTOR3 g_PlayerPos;
		vector<rtList> m_VectorList;
		static DWORD	m_PlayerState;
		vector<JrtLits> m_PlayerMotionList;
		D3DXVECTOR3		m_vInterval;
		shared_ptr<JH_Bullet>			m_Shot;
		
	public:
		bool SetArrayRect(vector<rtList>& rtList, int width, int height, float fAnimaTime);

		//void   SetMatrix(D3DXMATRIX* matWorld,
		//	D3DXMATRIX* matView,
		//	D3DXMATRIX* matProj);
	public:
		bool Init();
		bool Frame();
		bool PostRender()override;
	public:
		JH_Player();
		virtual ~JH_Player();
	};

