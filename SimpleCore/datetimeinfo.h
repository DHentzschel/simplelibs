#ifndef DATEINFO_H
#define DATEINFO_H

#include "types.h"

struct DateTimeInfo {
    byte day;
    byte month;
    ushort year;
    byte hour;
    byte minute;
    byte second;

    DateTimeInfo() :
        day(1),
        month(1),
        year(1970),
        hour(0),
        minute(0),
        second(0)
    {}

    DateTimeInfo(byte day,
        byte month,
        ushort year,
        byte hour,
        byte minute,
        byte second) :
        day(day),
        month(month),
        year(year),
        hour(hour),
        minute(minute),
        second(second)
    {}
};

#endif // DATEINFO_H
