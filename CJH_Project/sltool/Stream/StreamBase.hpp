#pragma once
#include <cstdint>
#include <string>

#ifdef NIO_EXPORTS
#define SLTOOL_CLASS NIO_DLL_CLASS
#elif SLLOGIC_EXPORTS

#elif SLDATA_EXPORTS

#elif DATABASE_EXPORTS

#else
#define SLTOOL_CLASS
#endif
