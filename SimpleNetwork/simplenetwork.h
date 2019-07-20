#ifndef SIMPLENETWORK_H
#define SIMPLENETWORK_H 

#ifdef SIMPLENETWORK_EXPORTS
#define SIMPLENETWORK_API __declspec(dllexport)
#elif defined(SIMPLELIBS_TEST)
#define SIMPLENETWORK_API 
#else
#define SIMPLENETWORK_API __declspec(dllimport)
#endif // SIMPLENETWORK_EXPORTS

#endif // !SIMPLENETWORK_H
