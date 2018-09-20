#ifndef PSQLCOL_H
#define PSQLCOL_H

#include <astring.h>

struct SqlColumn {
    AString name;

    int type;

    uint length;
};

#endif   // PSQLCOL_H
