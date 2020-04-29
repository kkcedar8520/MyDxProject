

#include"ODBC.h"


int main(void)
{
	ODBC odbc;
	odbc.Init();
	odbc.ConnectSQL(L"GAMEUSER", L"sa", L"kgca!@#$");
	
	odbc.Prepare(odbc.m_hAllSelectStmt, _T("{CALL AllSelectUser}"), SQL_NTS); 

	odbc.Exc(odbc.m_hAllSelectStmt);

	odbc.Print();
}