#ifndef SIMPLECORE_H
#define SIMPLECORE_H

#include "osdetection.h"

#if defined (_MSC_VER) && defined (OS_WIN)
#  ifdef SIMPLECORE_EXPORTS
#    define SIMPLECORE_API __declspec(dllexport)
#  else
#    define SIMPLECORE_API __declspec(dllimport)
#  endif
#elif defined(OS_LINUX)
#    define SIMPLECORE_API extern
#endif // OS_LINUX

#ifdef SIMPLECORE_TEST
#  ifdef SIMPLECORE_API
#    undef SIMPLECORE_API
#  endif // SIMPLECORE_API
#  define SIMPLECORE_API
#endif // SIMPLECORE_TEST

#endif // !SIMPLECORE_H
