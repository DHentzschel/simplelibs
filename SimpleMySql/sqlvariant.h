#ifndef SQLVARIANT_H
#define SQLVARIANT_H

#include <astring.h>

#include "simplemysql.h"

class SqlVariant {
public:
	SIMPLEMYSQL_API explicit SqlVariant(void* data, bool useCasts = false, bool fromString = false);

	SIMPLEMYSQL_API bool isValid() const;

	SIMPLEMYSQL_API bool toBool() const;

	SIMPLEMYSQL_API char toChar() const;

	SIMPLEMYSQL_API byte toByte() const;

	SIMPLEMYSQL_API short toShort() const;

	SIMPLEMYSQL_API ushort toUShort() const;

	SIMPLEMYSQL_API int toInt() const;

	SIMPLEMYSQL_API uint toUInt() const;

	SIMPLEMYSQL_API int64 toInt64() const;

	SIMPLEMYSQL_API uint64 toUInt64() const;

	SIMPLEMYSQL_API float toFloat() const;

	SIMPLEMYSQL_API double toDouble() const;

	SIMPLEMYSQL_API const char* toCString() const;

	SIMPLEMYSQL_API AString toString() const;

private:
    bool useCasts_;

    bool fromString_;

    void* data_;
};

#endif // SQLVARIANT_H
