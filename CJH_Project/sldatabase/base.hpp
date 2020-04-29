#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <sstream>
#include <concurrent_queue.h>

#include <WinSock2.h>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>

#ifdef SLDATABASE_EXPORTS
#define SLDATABASE_DLL_CLASS __declspec(dllexport)
#define SLDATABASE_DLLEXPORT_CLASS
#else
#define SLDATABASE_DLL_CLASS __declspec(dllimport)
#define SLDATABASE_DLLEXPORT_CLASS extern
#endif

#ifdef _UNICODE
using string_t = std::wstring;
using sqlchar_t = SQLWCHAR;
using char_t = wchar_t;
#else
using string_t = std::string;
using sqlchar_t = SQLCHAR;
using char_t = char;
#endif