#ifndef SIMPLECORE_H
#define SIMPLECORE_H

#ifdef SIMPLECORE_EXPORTS
#define SIMPLECORE_API __declspec(dllexport)
#elif defined(SIMPLELIBS_TEST)
#define SIMPLECORE_API 
#else
#define SIMPLECORE_API __declspec(dllimport)
#endif // SIMPLECORE_EXPORTS

#endif // !SIMPLECORE_H
