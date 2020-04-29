#include "Sample.h"


bool   Sample::Init()
{
	m_Sound.Init();

	m_iBackGroundMusic = m_Sound.Load("../../data/Sound/abel_leat.asf", false);
	m_iEffect = m_Sound.Load("../../data/Sound/GunShot.mp3");
	
	/*const char soundlist[][50] =
	{
		"../../data/sound/Gun2.wav",
		"../../data/sound/GunShot.mp3",
		"../../data/sound/MyLove.mp3",
		"../../data/sound/OnlyLove.mp3",
		"../../data/sound/romance.mid",
		"../../data/sound/PianoSound_00.mp3",
		"../../data/sound/PianoSound_04.mp3",
	};
	int iNumSouind = sizeof(soundlist) / sizeof(soundlist[0]); //전체저장 연속듣기
	for (int iSound = 0; iSound < iNumSouind; iSound++)
	{
		m_Sound.Load(soundlist[iSound], false);
	}

	m_Sound.Play(m_iBackGroundMusic);
	*/
	m_Sound.Play(m_iBackGroundMusic);
	
	return true;
}
bool   Sample::Frame()
{
	m_Sound.Frame();
	if (m_Input.KeyCheck(VK_F5) == KEY_PUSH)
	{
		m_Sound.Paused(m_iBackGroundMusic);
	}
	if (m_Input.KeyCheck(VK_F6) == KEY_PUSH)
	{
		m_Sound.PlayEffect(m_iEffect);
	}
	if (m_Input.KeyCheck(VK_F7) == KEY_HOLD)
	{
		m_Sound.Volumn(m_iBackGroundMusic,
			g_SecondPerFrame*0.3f);
	}
	if (m_Input.KeyCheck(VK_F8) == KEY_HOLD)
	{
		m_Sound.Volumn(m_iBackGroundMusic,
			g_SecondPerFrame*0.3f, false);
	}
	return true;
}
bool   Sample::Render()
{
	return m_Sound.Render();
}
bool   Sample::Release()
{
	return m_Sound.Release();
}
Sample::Sample()
{

}


Sample::~Sample()
{
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample game;
	game.m_hinstance= hInstance;
	if (!game.initWindow())
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;

}