
#include"Server.h"


int main(void)
{
	RuntimeClass*pRc = RUNTIME_CLASS(User);
	I_Session.Create(pRc);
	
	Server NetServer;
	NetServer.Init();
	
	while (1)
	{
		Sleep(1000);
	}
	return true;
}