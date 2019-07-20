#ifndef PSQLCOL_H
#define PSQLCOL_H

#include <astring.h>

struct SqlColumn {
	AString name;

    int type;

    uint length;

    SqlColumn() :
        type(-1),
        length(0)
    {}
};

#endif   // PSQLCOL_H
