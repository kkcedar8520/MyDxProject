#include "AsyncSelect.h"

#define WM_AsynMsg (WM_USER+1)

bool AsyncSelect::Init()
{
	int iRet = WSAAsyncSelect(m_Socket, m_hwnd, WM_AsynMsg, FD_ACCEPT | FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if (iRet==SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
LRESULT AsyncSelect::MsgProc(HWND hwnd, UINT Msg, WPARAM wpram, LPARAM lparam)
{
	return 1;
}
AsyncSelect::AsyncSelect()
{
}


AsyncSelect::~AsyncSelect()
{
}
