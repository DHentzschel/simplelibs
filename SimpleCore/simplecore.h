#ifndef SIMPLECORE_H
#define SIMPLECORE_H

#include "osdetection.h"

#ifdef SIMPLECORE_EXPORTS

#ifdef _MSC_VER
#define SIMPLECORE_API __declspec(dllexport)
#else
#define SIMPLECORE_API
#endif // OS_LINUX

#elif defined(SIMPLELIBS_TEST)
#define SIMPLECORE_API 
#endif // SIMPLECORE_EXPORTS

#endif // !SIMPLECORE_H
