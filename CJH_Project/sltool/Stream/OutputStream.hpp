#pragma once
#include "ByteStream.hpp"

class SLTOOL_CLASS OutputStream : public ByteStream
{
public:
	OutputStream(const OutputStream& rhs);
	void operator=(const OutputStream& rhs);
	OutputStream(OutputStream&& rhs) noexcept;
	void operator=(OutputStream&& rhs) noexcept;
public:
	OutputStream();
	~OutputStream() = default;

	OutputStream& operator<<(int8_t data);
	void WriteInt8(int8_t data);

	OutputStream& operator<<(int16_t data);
	void WriteInt16(int16_t data);

	OutputStream& operator<<(int32_t data);
	void WriteInt32(int32_t data);

	OutputStream& operator<<(int64_t data);
	void WriteInt64(int64_t data);

	OutputStream& operator<<(float data);
	void WriteFloat32(float data);

	OutputStream& operator<<(double data);
	void WriteFloat64(double data);

	OutputStream& operator<<(bool data);
	void WriteBool(bool data);
	void WriteBytes(const char* bytes, size_t length);

	OutputStream& operator<<(const std::string& str);
	void WriteString(const std::string& str);
	void WriteFromStringBytesArray(const std::string& string_bytes);
	void WriteZeroBytes(size_t size);
};