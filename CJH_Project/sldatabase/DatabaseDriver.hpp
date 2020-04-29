#pragma once
#include "base.hpp"


class Connection;

class SLDATABASE_DLL_CLASS DatabaseDriver
{
public:
	virtual ~DatabaseDriver() = 0;
	virtual void Initialize() = 0;
	virtual std::shared_ptr<Connection> Connect(const string_t& addr, const string_t& id, const string_t& pw) = 0;
};

class SLDATABASE_DLL_CLASS ODBCDriver : public DatabaseDriver
{
private:
	ODBCDriver(const ODBCDriver& rhs);
	void operator=(const ODBCDriver& rhs);
public:
	ODBCDriver();
	~ODBCDriver();
	virtual void Initialize() override;
	virtual std::shared_ptr<Connection> Connect(const string_t& addr, const string_t& id, const string_t& pw) override;
private:
	SQLHENV environment_handle_;
};