#include "ODBC.h"

bool ODBC::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return false;
	}


	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool ODBC::Frame()
{
	return true;
}
bool ODBC::Render()
{
	return true;
}
bool ODBC::Release()
{
	return true;
}
bool ODBC::Connect()
{
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDBC);


	SQLWCHAR InCon[255];
	SQLWCHAR OutCon[255];
	SQLSMALLINT cbOutCon;

	TCHAR Dir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, Dir);

	wsprintf((TCHAR*)InCon, L"DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s\\cigarette.mdb;", Dir);

	SQLRETURN hr = SQLDriverConnect(m_hDBC, NULL, InCon, _countof(InCon), OutCon, _countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

	hr= SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &m_hStmt);
	if (hr!=SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool ODBC::ConnectSQL(const WCHAR* dsn, const WCHAR* ID, const WCHAR* ps)
{
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDBC);


	SQLWCHAR InCon[255];


	wsprintf((TCHAR*)InCon, L"FileDsn=%s", dsn);

	SQLRETURN hr = SQLConnect(m_hDBC, (SQLWCHAR*)dsn, SQL_NTS, (SQLWCHAR*)ID, SQL_NTS, (SQLWCHAR*)ps, SQL_NTS);

	hr = SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &m_hStmt);
	if (hr != SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool ODBC::Prepare(SQLHSTMT& stmt, const TCHAR*sql, int iMaker)
{
	SQLRETURN hr;

	hr = SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &stmt);
	hr = SQLPrepare(stmt, (SQLTCHAR*)sql, SQL_NTS);

	if (iMaker>0)
	{
		hr = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,&m_Price,0,NULL);
		ZeroMemory(m_NameBuf, sizeof(m_NameBuf));

		m_iDataLength = sizeof(m_NameBuf);
		m_cbColumn = SQL_NTS;

		hr = SQLBindParameter(stmt, 2,
			SQL_PARAM_INPUT, SQL_UNICODE, SQL_VARCHAR,
			m_iDataLength, 0, m_NameBuf, m_iDataLength,
			&m_cbColumn);

	}


	return true;
}
bool ODBC::Exc(SQLHSTMT& stmt)
{
	SQLRETURN hr;
	hr = SQLExecute(stmt);
	if (hr!=SQL_SUCCESS)
	{
		return false;
	}
	while (hr = SQLMoreResults(m_hStmt) != SQL_NO_DATA)
	{
	}
	GetDesribeCol(stmt);
	GetRecordData(m_hStmt);
	return true;
}
bool  ODBC::ExcDirect(const WCHAR* sql)
{
	
	SQLRETURN hr;
	
	hr = SQLExecDirect(m_hStmt,(SQLWCHAR*)sql, SQL_NTS);
	if (hr!=SQL_SUCCESS)
	{
		return false;
	}
	while(hr=SQLMoreResults(m_hStmt)!=SQL_NO_DATA)
	GetDesribeCol(m_hStmt);
	GetRecordData(m_hStmt);
	return true;
}
bool ODBC::GetDesribeCol(SQLHSTMT& stmt)
{
	
	ColumnElement ColEle;

	ColEle.icol = 1;
	while (true)
	{
		SQLRETURN hr = SQLDescribeCol(stmt,
			ColEle.icol,
			ColEle.szColName,
			sizeof(ColEle.szColName),
			&ColEle.pcchColName,
			&ColEle.pfSqlType,
			&ColEle.pcbColDef,
			&ColEle.pibScale,
			&ColEle.pfNullable);

		if (hr!=SQL_SUCCESS)
		{
			break;
		}
		m_Columnlist.push_back(ColEle);
		ColEle.icol++;
	}
	return true;

}
bool	ODBC::GetRecordData(SQLHSTMT& stmt)
{
	
	SQLRETURN hr;
	for (int i = 0; i<m_Columnlist.size(); i++)
	{
		Record RetData;
		SQLLEN strLen;
		 hr = SQLGetData(stmt,
			m_Columnlist[i].icol, 
			SQL_WCHAR, m_Columnlist[i].BindData, 
			sizeof(m_Columnlist[i].BindData),NULL);
		if (hr!=SQL_SUCCESS)
		{
			return false;
		}
		RetData.push_back(m_Columnlist[i].BindData);
		m_Recordlist.push_back(RetData);
	}
	while (hr = SQLMoreResults(m_hStmt) != SQL_NO_DATA);
	SQLCloseCursor(m_hStmt);
	SQLFreeStmt(m_hStmt, SQL_CLOSE);
	return true;
}
void ODBC::Print()
{
	for  ( auto& Record:m_Recordlist)
	{
		for (auto& col:Record)
		{
			std::wcout << col << " ";
		}
		std::wcout << std::endl;
	}
}
ODBC::ODBC()
{
}


ODBC::~ODBC()
{
}
