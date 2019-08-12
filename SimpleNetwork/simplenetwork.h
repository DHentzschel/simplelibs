#ifndef SIMPLENETWORK_H
#define SIMPLENETWORK_H 

#include "osdetection.h"

#if defined (_MSC_VER) && defined (OS_WIN)
#  ifdef SIMPLENETWORK_EXPORTS
#    define SIMPLENETWORK_API __declspec(dllexport)
#  else
#    define SIMPLENETWORK_API __declspec(dllimport)
#  endif
#elif defined(OS_LINUX)
#    define SIMPLENETWORK_API extern
#endif // OS_LINUX

#ifdef SIMPLENETWORK_TEST
#  ifdef SIMPLENETWORK_API
#    undef SIMPLENETWORK_API
#  endif // SIMPLENETWORK_API
#  define SIMPLENETWORK_API
#endif // SIMPLENETWORK_TEST
#endif // !SIMPLENETWORK_H
