#ifndef PPARSEDQ_H
#define PPARSEDQ_H

#include <avector.h>
#include <astring.h>

#include "psqlcol.h"

struct ParsedQuery {
    AString database;

    AVector<SqlColumn> columns;
};

#endif   // PPARSEDQ_H
