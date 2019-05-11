#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include <ctime>
#include <sstream>

#include "astring.h"
#include "datetimeinfo.h"

class DateTime {
public:
    DateTime();

    DateTime(const DateTimeInfo& dateTimeInfo);

    DateTime(const AString& string);

    static DateTime now();

    static AString getDatestamp();

    static AString getTimestamp();

    static AString getCurrentTimestamp();

    static bool isDateTimeReached(const DateTime& dateTime);

    static bool isDateTimeReached(const AString& comparable);

    static bool isDateTimeReached(const AString& target, const AString& comparable);

    static bool isLeapYear(ushort year);

    static ushort getLeapYearCountFromTo(ushort to, ushort from = beginDateTime_.year);

    static DateTime fromUnixTimestamp(int64 timestamp);

    void addDays(uint count);

    void subDays(uint count);

    void addMonths(uint count);

    void subMonths(uint count);

    void addYears(uint count);

    void subYears(uint count);

    void addHours(uint count);

    void subHours(uint count);

    void addMinutes(uint count);

    void subMinutes(uint count);

    void addSeconds(uint count);

    void subSeconds(uint count);

    byte getDay() const;

    byte getMonth() const;

    ushort getYear() const;

    byte getHour() const;

    byte getMinute() const;

    byte getSecond() const;

    byte getMonthDayCount(ushort year, byte month);

    time_t toUnixTimestamp();

    AString toString() const;

    std::tm toStdTm();

private:
    DateTimeInfo dateTimeInfo_;

    int64 unixTimestamp_;

    static DateTime dateTimeInitializer_;

    static ushort fourYearCycle_;

    static DateTimeInfo beginDateTime_;

    static byte monthDays_[];

    void parse(const AString& string);

    void calculateUnixTimestamp();

    static int64 getDaysCountUntil(byte month, bool leapYear);

};

#endif // DATETIME_H
