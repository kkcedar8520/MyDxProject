
#include"NetworkClient.h"
#include"EventSelect.h"

int main(void)
{

	NetworkClient NetClient;

	if (!NetClient.Connect("192.168.0.122",SOCK_STREAM,10000,1))
	{
		std::cout << "연결실패" << std::endl;
		return false;
	}

	NetClient.SetModel(std::make_shared<EventSelect>(NetClient.m_Socket));
	NetClient.CreateThread();
	while (1)
	{
		
		if (!NetClient.Frame())
		{
			return false;
		}
	}
}