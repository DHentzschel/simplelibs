#ifndef SIMPLEMYSQL_H
#define SIMPLEMYSQL_H

#include "osdetection.h"

#if defined (_MSC_VER) && defined (OS_WIN)
#  ifdef SIMPLEMYSQL_EXPORTS
#    define SIMPLEMYSQL_API __declspec(dllexport)
#  else 
#    define SIMPLEMYSQL_API __declspec(dllimport)
#  endif
#elif defined(OS_LINUX)
#    define SIMPLEMYSQL_API extern
#endif // OS_LINUX

#ifdef SIMPLEMYSQL_TEST
#  ifdef SIMPLEMYSQL_API
#    undef SIMPLEMYSQL_API
#  endif // SIMPLEMYSQL_API
#  define SIMPLEMYSQL_API
#endif // SIMPLEMYSQL_TEST

#endif // !SIMPLEMYSQL_H
