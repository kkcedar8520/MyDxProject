#include "JHSound.h"

int JHSound::Load(const char* pszSoundFile, bool bPlay )
{
	m_pSystem->createSound(pszSoundFile, 
		FMOD_DEFAULT, nullptr,
		&m_pSound[++m_iSoundList]);
	if (bPlay)
	{
		m_pSystem->playSound(m_pSound[m_iSoundList],
			nullptr, false, 
			&m_pChannel[m_iSoundList]);
	}
	return m_iSoundList;
}
bool	JHSound::Init()
{
	System_Create(&m_pSystem);
	FMOD_RESULT ret = m_pSystem->init(g_iMaxSound,FMOD_INIT_NORMAL, 0);
	if (ret!=FMOD_OK)
	{
		return false;

	}
	
	return true;
}
bool	JHSound::Frame()
{
	m_pSystem->update();
	unsigned int total = 0;
	//m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);
	return true;
}
bool	JHSound::Render()
{

	return true;
}
bool	JHSound::Release()
{
	for (int iSound = 0; iSound < m_iSoundList; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
void    JHSound::Paused(int iChannel)
{
	bool paused;
	bool bPlaying;
	if (m_pChannel[iChannel] != nullptr)
	{
		m_pChannel[iChannel]->isPlaying(&bPlaying);
		if (bPlaying)
		{
			m_pChannel[iChannel]->getPaused(&paused);
			m_pChannel[iChannel]->setPaused(!paused);
		}
	}

}
void    JHSound::Play(int iChannel)
{
	bool bPlaying = false;
	if (m_pChannel[iChannel] != nullptr)
	{
		m_pChannel[iChannel]->isPlaying(&bPlaying);
	}
	if (bPlaying == false)
	{
		m_pSystem->playSound(m_pSound[iChannel],
			nullptr,
			false,
			&m_pChannel[iChannel]);
		m_pChannel[iChannel]->setVolume(0.5f);
	}

}
void    JHSound::Stop(int iChannel)
{
	if (IsPlaying(iChannel))
	{
		m_pChannel[iChannel]->stop();
	}

}
void    JHSound::PlayEffect(int iChannel)
{
	Channel* pChannel;
	m_pSystem->playSound(m_pSound[iChannel],
		nullptr,
		false,
		&pChannel);
	m_pChannel[iChannel] = pChannel;
	m_pChannel[iChannel]->setVolume(0.5f);
}
bool    JHSound::IsPlaying(int iChannel)
{

	bool bPlaying = false;
	if (m_pChannel[iChannel] != nullptr)
	{
		m_pChannel[iChannel]->isPlaying(&bPlaying);
	}
	return bPlaying;
}
void    JHSound::Volumn(int iChannel,
	float fVolumn,
	bool up)
{
	float fCurrentVolumn;
	if (m_pChannel[iChannel] == nullptr) return;

	m_pChannel[iChannel]->getVolume(&fCurrentVolumn);
	if (up == true)
	{
		fCurrentVolumn += fVolumn;
		fCurrentVolumn = min(1.0f, fCurrentVolumn);
	}
	else
	{
		fCurrentVolumn -= fVolumn;
		fCurrentVolumn = max(0.0f, fCurrentVolumn);
	}
	m_pChannel[iChannel]->setVolume(fCurrentVolumn);
}
JHSound::JHSound()
{
	m_iSoundList = -1;
}


JHSound::~JHSound()
{
}
