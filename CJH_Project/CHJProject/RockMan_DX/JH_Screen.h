#pragma once


#include"JH_FSM.h"


class JH_Screen;

class ScreenState
{
public:
	JH_Screen* m_pOwner;
	ID3D11Device* m_copyDevice;
	ID3D11DeviceContext* m_copyDevcieContext;
public:
	
	ScreenState(JH_Screen*owner) :m_pOwner(owner)
	{

	}
	virtual ~ScreenState() {}
public:
	virtual void Process(JH_Model*obj) = 0;
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }
	virtual void MatrixSet(D3DXMATRIX& matview ,D3DXMATRIX&matOrthoProj){ return; }
	

};
typedef std::vector<RECT> rtList;
class JH_Screen :public JH_ShapePlane
{
public:
	float		m_fTimer;
	bool		b_Left;
	DWORD	m_dwScreenState;
	std::shared_ptr<ScreenState> m_pScreen;
	std::shared_ptr<ScreenState> m_pScreenList[SCREEN_COUNT];
	int			m_iSpriteindex;
	bool		b_Waiting;
public:
	float		m_fAttackSize;
public:
	static void SetOtherClass() { const JH_ShapePlane& ShapePlane(); const JH_Model& Model(); };// 寇何按眉 积己
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual void Process(JH_Model*user);
	virtual void SetTransition(DWORD dwEvent);

	//virtual bool SetArrayRect(vector<rtList>& DrtList, int width, int height, float fAnimaTime);
public:
	JH_Screen();
	virtual ~JH_Screen();
};
