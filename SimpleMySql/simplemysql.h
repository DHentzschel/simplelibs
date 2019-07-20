#ifndef SIMPLEMYSQL_H
#define SIMPLEMYSQL_H

#ifdef SIMPLEMYSQL_EXPORTS
#define SIMPLEMYSQL_API __declspec(dllexport)
#elif defined(SIMPLELIBS_TEST)
#define SIMPLEMYSQL_API 
#else
#define SIMPLEMYSQL_API __declspec(dllimport)
#endif // SIMPLEMYSQL_EXPORTS

#endif // !SIMPLEMYSQL_H
