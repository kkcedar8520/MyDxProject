#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<tchar.h>
#include<sql.h>
#include<sqlext.h>


SQLHENV		S_EV;
SQLHDBC		S_DBC;
SQLHSTMT	S_STM;
void ReadRecord()
{

	TCHAR		ID[20] = { 0. };
	SQLLEN		IDLEN;
	TCHAR		PW[15] = { 0, };
	SQLLEN		PWLEN;

	

	SQLBindCol(S_STM, 1, SQL_UNICODE, ID, sizeof(ID), &IDLEN);
	SQLBindCol(S_STM, 2, SQL_UNICODE, PW, sizeof(PW), &PWLEN);


	SQLRETURN hr = SQLExecDirect(S_STM, (SQLTCHAR*)_T("select ID,PassWord from Account"), SQL_NTS);

	setlocale(LC_ALL, "korean");//한글 세팅
	while (SQLFetch(S_STM) != SQL_NO_DATA)
	{ 
		std::wcout << ID << "" << PW <<" "<< std::endl;
	}
	SQLCloseCursor(S_STM);
}
#include <sstream>
int main(void)
{

	
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &S_EV)!= SQL_SUCCESS)
	{
		return false;
	}


	if (SQLSetEnvAttr(S_EV, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}
	//if (SQLAllocHandle(SQL_HANDLE_ENV,
	//	SQL_NULL_HANDLE, &S_EV) != SQL_SUCCESS)
	//{
	//	return 0;
	//}
	//if (SQLSetEnvAttr(S_EV, SQL_ATTR_ODBC_VERSION,
	//	(SQLPOINTER)SQL_OV_ODBC3,
	//	SQL_IS_INTEGER) != SQL_SUCCESS)
	//{
	//	return 0;
	//}
	SQLAllocHandle(SQL_HANDLE_DBC,S_EV, &S_DBC);


	SQLWCHAR InCon[255];
	SQLWCHAR OutCon[255];
	SQLSMALLINT cbOutCon;

	TCHAR Dir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, Dir);

	wsprintf((TCHAR*)InCon,L"DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s\\UserDB.mdb;", Dir);

	/*SQLRETURN hr = SQLDriverConnect(S_DBC, NULL,InCon, _countof(InCon),OutCon, _countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);*/
	SQLRETURN hr = SQLConnect(S_DBC, (SQLTCHAR*)"GAMEUSER", SQL_NTS, (SQLTCHAR*)"sa", SQL_NTS,(SQLTCHAR*)"kgca!@#$", SQL_NTS);
	SQLINTEGER NativeError;
	SQLWCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;;
	int num_diag = 0;
	int i = 1;

	std::wstringstream ss;
	SQLGetDiagField(SQL_HANDLE_DBC, S_DBC, 0, SQL_DIAG_NUMBER, &num_diag, 0, &MsgLen);
	ss << "NumDiag[" << num_diag << "], ";
	while (true)
	{
		SQLRETURN Ret = SQLGetDiagRec(SQL_HANDLE_DBC, S_DBC, i++,
			SqlState,
			&NativeError,
			Msg, sizeof(Msg), &MsgLen);
		if (Ret == SQL_NO_DATA) {
			break;
		}
		ss << "SQLSTATE[" << SqlState << "], NativeError[" << NativeError << "] " << Msg;
	}
	std::wstring str = ss.str();

	
	SQLAllocHandle(SQL_HANDLE_STMT, S_DBC, &S_STM);

	ReadRecord();

	if (S_EV) SQLFreeHandle(SQL_HANDLE_STMT, S_STM);
	if (S_DBC) SQLFreeHandle(SQL_HANDLE_DBC, S_DBC);
	if (S_STM) SQLFreeHandle(SQL_HANDLE_ENV, S_EV);
}