#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <astring.h>
#include <avector.h>
#include <memory>
#include <types.h>

#include "psqltbl.h"
#include "simplemysql.h"

static const AString defaultConnection = "default_sql_connection";

class SqlQuery;

struct st_mysql;

typedef st_mysql MYSQL;

struct SqlDatabasePrivate;

class SqlDatabase {
	friend class SqlQuery;

public:
	SIMPLEMYSQL_API SqlDatabase(const SqlDatabase& database);

	SIMPLEMYSQL_API explicit SqlDatabase(const AString& connectionName = defaultConnection);

	SIMPLEMYSQL_API ~SqlDatabase();

	SIMPLEMYSQL_API bool open() const;

	SIMPLEMYSQL_API bool open(const AString& hostname,
		ushort port,
		const AString& username,
		const AString& password,
		const AString& databaseName) const;

	SIMPLEMYSQL_API void switchDatabase(const AString&) const;

	SIMPLEMYSQL_API void close() const;

	SIMPLEMYSQL_API AString getHostname() const;

	SIMPLEMYSQL_API void setHostname(const AString&) const;

	SIMPLEMYSQL_API ushort getPort() const;

	SIMPLEMYSQL_API void setPort(ushort) const;

	SIMPLEMYSQL_API AString getUsername() const;

	SIMPLEMYSQL_API void setUsername(const AString&) const;

	SIMPLEMYSQL_API AString getPassword() const;

	SIMPLEMYSQL_API void setPassword(const AString&) const;

	SIMPLEMYSQL_API AString getDatabaseName() const;

	SIMPLEMYSQL_API bool setDatabaseName(const AString&) const;

	SIMPLEMYSQL_API bool isOpen() const;

	SIMPLEMYSQL_API AString getConnectionName() const;

	SIMPLEMYSQL_API AString getLastError() const;

	SIMPLEMYSQL_API static SqlDatabase
		addDatabase(const AString& connectionName = defaultConnection);

	SIMPLEMYSQL_API static void
		removeDatabase(const AString& connectionName = defaultConnection);

	SIMPLEMYSQL_API static SqlDatabase*
		database(const AString& connectionName = defaultConnection);

private:
	SqlDatabasePrivate * private_;

	void readTables() const;

	void readTableTypes() const;

	MYSQL* getMySql() const;

	AVector<std::shared_ptr<SqlTable>>& getTables() const;

	static AVector<SqlDatabase*> databases_;

	static bool addToList(SqlDatabase*);

	static bool removeFromList(SqlDatabase*);

	static SqlDatabase* findFromList(const AString& connectionName);
};

#endif   // SQLDATABASE_H
