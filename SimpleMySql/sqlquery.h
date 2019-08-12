#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <types.h>

#include "psqltbl.h"
#include "psqlvarparam.h"
#include "sqldatabase.h"
#include "sqlvariant.h"

struct SqlQueryPrivate;

class SqlQuery {
public:
	SIMPLEMYSQL_API explicit SqlQuery(const AString& connectionName = defaultConnection);

	SIMPLEMYSQL_API SqlQuery(const SqlQuery& query);

	SIMPLEMYSQL_API ~SqlQuery();

	SIMPLEMYSQL_API bool prepare(const AString& query) const;

	SIMPLEMYSQL_API void addBindValue(const SqlVariantParam&) const;

	SIMPLEMYSQL_API bool exec() const;

	SIMPLEMYSQL_API bool exec(const AString& query) const;

	SIMPLEMYSQL_API bool next() const;

	SIMPLEMYSQL_API SqlVariant value(const AString& column) const;

	SIMPLEMYSQL_API uint64 getRecordCount() const;

	SIMPLEMYSQL_API uint64 getFieldCount() const;

	SIMPLEMYSQL_API void clear() const;

	SIMPLEMYSQL_API void setDatabase(const AString& connectionName) const;

	SIMPLEMYSQL_API void printSqlError();

private:
	void addBindValue(int type, void* buffer, char isUnsigned = 0, uint bufferLength = 0) const;

	std::shared_ptr<SqlTable> parseQuery() const;

	void countRows(const AString& query) const;

	void printSqlError(const char* file, const char* function, int line, const char* reason = nullptr) const;

	SqlQueryPrivate* private_;
};

#endif   // SQLQUERY_H
