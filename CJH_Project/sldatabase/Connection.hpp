#pragma once
#include "base.hpp"


class PreparedStatement;

class SLDATABASE_DLL_CLASS Connection
{
public:
	virtual ~Connection();
	virtual void Connect(const string_t& addr, const string_t& id, const string_t& pw) = 0;
	virtual void SetSchema() = 0;
	virtual std::shared_ptr<PreparedStatement> GetPreparedStatement() = 0;
};

class SLDATABASE_DLL_CLASS ODBCConnection : public Connection
{
private:
	ODBCConnection(const ODBCConnection& rhs);
	void operator=(const ODBCConnection& rhs);
public:
	ODBCConnection(SQLHENV enviroment_handle);
	~ODBCConnection();
	virtual void Connect(const string_t& addr, const string_t& id, const string_t& pw) override;
	virtual void SetSchema() override;
	virtual std::shared_ptr<PreparedStatement> GetPreparedStatement() override;
private:
	SQLHDBC connect_handle_;
};