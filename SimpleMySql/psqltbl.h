#ifndef PSQLTBL_H
#define PSQLTBL_H

#include <astring.h>

#include "psqlcol.h"

struct SqlTable {
    AString name;

    AVector<SqlColumn> columns;
};

#endif   // PSQLTBL_H
