#pragma once
#include "StreamBase.hpp"

class SLTOOL_CLASS ByteStream
{
public:
	ByteStream(const ByteStream& rhs);
	void operator=(const ByteStream& rhs);
	ByteStream(ByteStream&& rhs) noexcept;
	void operator=(ByteStream&& rhs) noexcept;
public:
	ByteStream();
	virtual ~ByteStream();
	void Initialize(char* buffer, uint64_t buffer_length, uint64_t access_offset);
	char* GetData();
	uint64_t GetBufferLength() const;
	uint64_t GetAccessOffset() const;
	void SetAccesOffset(uint64_t offset);
public:
	static std::string GetDebugString(const char* buffer, uint64_t length);
	static void StreamValidCheck(char* buffer, uint64_t buffer_length, uint64_t access_offset, uint64_t access_size);
protected:
	char* buffer_;
	uint64_t buffer_length_;
	uint64_t access_offset_;
};