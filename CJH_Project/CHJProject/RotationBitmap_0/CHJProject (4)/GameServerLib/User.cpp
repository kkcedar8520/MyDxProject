#include "User.h"



void User::DisConnect()
{
	closesocket(m_Sock);
}
User::User()
{
	
}


User::~User()
{
}
