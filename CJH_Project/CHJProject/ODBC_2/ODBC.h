#pragma once
#include<Windows.h>
#include<vector>
#include<sql.h>
#include<sqlext.h>
#include<string>
#include<iostream>
#include<tchar.h>

typedef std::vector<std::wstring> Record;
class ODBC
{
public:
	SQLHENV		m_hEnv;
	SQLHDBC		m_hDBC;
	SQLHSTMT	m_hStmt;

	SQLHSTMT	m_hAllSelectStmt;
	
	int			m_Price;
	TCHAR		m_NameBuf[32];
	SQLINTEGER	m_iDataLength;
	SQLLEN		m_cbColumn;
	struct ColumnElement
	{
			
			SQLUSMALLINT        icol;
			SQLWCHAR			szColName[80];
			SQLSMALLINT         cchColNameMax;
			SQLSMALLINT        pcchColName;
			SQLSMALLINT       pfSqlType;
			SQLULEN            pcbColDef;
			SQLSMALLINT			pibScale;
			SQLSMALLINT        pfNullable;
			SQLWCHAR			BindData[100];
	};
	std::vector<ColumnElement> m_Columnlist;
	std::vector<Record> m_Recordlist;
public:
	void	Print();
	bool	GetDesribeCol(SQLHSTMT& stmt);
	bool	GetRecordData(SQLHSTMT& stmt);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Connect();
	bool ConnectSQL(const WCHAR* dsn,const WCHAR* ID,const WCHAR* ps);
	bool Prepare(SQLHSTMT& stmt,const TCHAR*sql,int iMaker=0);
	bool ExcDirect(const WCHAR* sql);
	bool Exc(SQLHSTMT& stmt);
public:
	ODBC();
	virtual ~ODBC();
};

