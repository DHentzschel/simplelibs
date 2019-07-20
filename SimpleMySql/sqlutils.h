#ifndef SQLUTILS_H
#define SQLUTILS_H

#include <astring.h>
#include <binary_log_types.h>
#include "simplemysql.h"

class SqlUtils {
  public:
	SIMPLEMYSQL_API static enum_field_types getMySqlType(const AString& string);

	SIMPLEMYSQL_API static short getMySqlLength(const AString& string);

  private:
    static bool startsWithEntry(const AString& string,
                                const AVector<AString>& vector);
};

#endif   // SQLUTILS_H
