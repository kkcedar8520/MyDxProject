#pragma once
#include <stdexcept>
#include <string>
#include <cstdint>

class StackTraceException : public std::exception
{
public:
	enum Type : int32_t
	{
		kNullPointer = 0x00000001,
		kOutOfRange = 0x00000002,
		kLogicError = 0x00000004,
		kConcurrency = 0x00000008,
		kFileOpenFail = 0x00000010,
		kInvalidArgument = 0x00000020,
		kOverflow = 0x00000040,
		kUnderflow = 0x00000080,
		kBadAlloc = 0x00000100,
		kSQLError = 0x00000200,
	};
	const char* TypeToString(StackTraceException::Type type) const;
public:
	StackTraceException(const StackTraceException& rhs);
	void operator=(const StackTraceException& rhs);

	StackTraceException(const char* except_type, const char* message);
	StackTraceException(Type except_type, const char* message);
	~StackTraceException();
	virtual char const* what() const override;
private:
	std::string message_;
};