#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <astring.h>
#include <avector.h>
#include <memory>
#include <types.h>

#include "psqltbl.h"

static const AString defaultConnection = "default_sql_connection";

class SqlQuery;

struct st_mysql;

typedef st_mysql MYSQL;

struct SqlDatabasePrivate;

class SqlDatabase {
	friend class SqlQuery;

public:
	SqlDatabase(const SqlDatabase& database);

	explicit SqlDatabase(const AString& connectionName = defaultConnection);

	~SqlDatabase();

	bool open() const;

	bool open(const AString& hostname,
		ushort port,
		const AString& username,
		const AString& password,
		const AString& databaseName) const;

	void switchDatabase(const AString&) const;

	void close() const;

	AString getHostname() const;

	void setHostname(const AString&) const;

	ushort getPort() const;

	void setPort(ushort) const;

	AString getUsername() const;

	void setUsername(const AString&) const;

	AString getPassword() const;

	void setPassword(const AString&) const;

	AString getDatabaseName() const;

	bool setDatabaseName(const AString&) const;

	bool isOpen() const;

	AString getConnectionName() const;

	AString getLastError() const;

	static SqlDatabase
		addDatabase(const AString& connectionName = defaultConnection);

	static void
		removeDatabase(const AString& connectionName = defaultConnection);

	static SqlDatabase*
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
