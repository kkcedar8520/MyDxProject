#include "JH_Thread.h"


unsigned int WINAPI JH_Thread::RunHandle(LPVOID arg)
{
	JH_Thread* p_Thread = (JH_Thread*)arg;
	while (!p_Thread->Run())
	{
		return false;
	}

	return true;
}
void JH_Thread::CreateThread()
{
	m_ThreadHandle = _beginthreadex(NULL, 0, RunHandle, this, 0, &m_ID);
}
bool JH_Thread::Run()
{
	return true;
}
JH_Thread::JH_Thread()
{
}


JH_Thread::~JH_Thread()
{
	CloseHandle((HANDLE)m_ThreadHandle);
}
