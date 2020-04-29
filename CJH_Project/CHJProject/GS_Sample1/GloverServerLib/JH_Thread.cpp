#include "JH_Thread.h"

unsigned int WINAPI JH_Thread::RunHandle(LPVOID arg)
{
	JH_Thread* p_Thread = (JH_Thread*)arg;
	assert(p_Thread);
	p_Thread->Run();

	return 0;
}
void JH_Thread::CreateThread()
{
	m_ThreadHandle = _beginthreadex(NULL, 0, RunHandle, this, 0, &m_ID);
	bStart = true;
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
	CloseHandle(HANDLE(m_ThreadHandle));
}
