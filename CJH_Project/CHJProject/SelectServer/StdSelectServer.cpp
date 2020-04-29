#include"NetworkServer.h"




int main(void)
{
	
	NetworkServer NetServer;

	NetServer.CreateServer("192.168.0.122", SOCK_STREAM,10000,1);

	while (1)
	{
		if (!NetServer.StdSelectRun())
		{
			break;
		}
	}
	
}