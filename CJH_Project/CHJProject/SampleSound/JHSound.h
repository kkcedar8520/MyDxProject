#pragma once
#include"HWindow.h"
#include"fmod.h"
#include"fmod.hpp"
#pragma comment(lib,"fmod_vc.lib")
using namespace FMOD;
const int g_iMaxSound = 32;
class JHSound
{
public:
	System* m_pSystem;
	Sound*	m_pSound[g_iMaxSound];
	Channel* m_pChannel[g_iMaxSound];
	int m_iSoundList;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(const char* pszSoundFile, bool bPlay = false);
public:
	void    Paused(int iChannel);
	void    Play(int iChannel);
	void    Stop(int iChannel);
	void    PlayEffect(int iChannel);
	bool    IsPlaying(int iChannel);
	void    Volumn(int iChannel,
		float fVolumn,
		bool up = true);
public:
	JHSound();
	virtual ~JHSound();
};

