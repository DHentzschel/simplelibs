#ifndef SIMPLECORE_H
#define SIMPLECORE_H

#include "osdetection.h"

#ifdef SIMPLECORE_EXPORTS

#ifdef OS_WIN
#define SIMPLECORE_API __declspec(dllexport)
#elif defined (OS_LINUX)
#define SIMPLECORE_API extern
#endif // OS_LINUX

#elif defined(SIMPLELIBS_TEST)
#define SIMPLECORE_API 
#else
#define SIMPLECORE_API __declspec(dllimport)
#endif // SIMPLECORE_EXPORTS

#endif // !SIMPLECORE_H
