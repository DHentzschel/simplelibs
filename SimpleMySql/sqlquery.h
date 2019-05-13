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
    explicit SqlQuery(const AString& connectionName = defaultConnection);

    SqlQuery(const SqlQuery& query);

    ~SqlQuery();

    bool prepare(const AString& query) const;

    void addBindValue(const SqlVariantParam&) const;

    bool exec() const;

    bool exec(const AString& query) const;

    bool next() const;

    SqlVariant value(const AString& column) const;

    uint64 getRecordCount() const;

    uint64 getFieldCount() const;

    void clear() const;

    void setDatabase(const AString& connectionName) const;

    void printSqlError();

private:
    void addBindValue(int type,
        void* buffer,
        char isUnsigned = 0,
        uint bufferLength = 0) const;

    std::shared_ptr<SqlTable> parseQuery() const;

    void countRows(const AString& query) const;

    void printSqlError(const char* file,
        const char* function,
        int line,
        const char* reason = nullptr) const;

    SqlQueryPrivate* private_;
};

#endif   // SQLQUERY_H
