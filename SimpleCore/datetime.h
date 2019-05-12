#ifndef DATETIME_H
#define DATETIME_H

#include <chrono>
#include <ctime>
#include <sstream>

#include "astring.h"
#include "datetimeinfo.h"

/**
 * This class can store information about datetime and makes it easy to calculate dates and time values.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class DateTime {
public:
	/**
	 * Sets the unixTimestamp member variable to zero.
	 */
	DateTime();

	/**
	 * Sets the unixTimestamp member variable to zero and copies the dateTimeInfo from parameter.
	 *
	 * @param dateTimeInfo the copyable dateTimeInfo
	 */
	DateTime(const DateTimeInfo& dateTimeInfo);

	/**
	 * Sets the unixTimestamp member variable to zero and parses the datetime from string parameter.
	 *
	 * @param string the parsable datetime string
	 */
	DateTime(const AString& string);

	/**
	 * Returns the current datetime as object.
	 */
	static DateTime now();

	/*
	 * Returns the current datestamp in the following format: dd.MM.yyyy
	 */
	static AString getDatestamp();

	/**
	 * Returns the current timestamp in the following format: hh:mm:ss
	 */
	static AString getTimestamp();

	/**
	 * Returns the current date and timestamp in the following format: dd.MM.yyyy hh:mm:ss
	 */
	static AString getCurrentTimestamp();

	/**
	 * Returns either the datetime given as parameter was reached.
	 *
	 * @param reachableDatetime the reachable datetime
	 */
	static bool isDateTimeReached(const DateTime& reachableDatetime);

	/**
	 * Returns either the datetime given as parameter was reached.
	 *
	 * @param reachableDatetime the reachable datetime
	 */
	static bool isDateTimeReached(const AString& reachableDatetime);

	/**
	 * Returns either the datetime given as parameter was reached.
	 *
	 * @param target the datetime which implies "now"
	 * @param reachableDatetime the reachable datetime
	 */
	static bool isDateTimeReached(const AString& target, const AString& reachableDatetime);
	/**
	 * Returns either the year given as parameter is a leap year.
	 *
	 * @param year the year to check
	 */
	static bool isLeapYear(ushort year);

	/**
	 * Returns the count of leap years from the first year to the second year.
	 *
	 * @param to the begin date
	 * @param from the end date
	 */
	static ushort getLeapYearCountFromTo(ushort to, ushort from = beginDateTime_.year);

	/**
	 * Returns the datetime instance calculated from given timestamp parameter.
	 *
	 * @param timestamp the unix timestamp in seconds
	 */
	static DateTime fromUnixTimestamp(int64 timestamp);

	/**
	 * Adds the count of days given by parameter.
	 *
	 * @param count the count of days to add
	 */
	void addDays(uint count);

	/**
	 * Subtracts the count of days given by parameter.
	 *
	 * @param count the count of days to subtract
	 */
	void subDays(uint count);

	/**
	 * Adds the count of months given by parameter.
	 *
	 * @param count the count of months to add
	 */
	void addMonths(uint count);

	/**
	 * Subtracts the count of months given by parameter.
	 *
	 * @param count the count of months to subtract
	 */
	void subMonths(uint count);

	/**
	 * Adds the count of years given by parameter.
	 *
	 * @param count the count of years to add
	 */
	void addYears(uint count);

	/**
	 * Subtracts the count of years given by parameter.
	 *
	 * @param count the count of years to subtract
	 */
	void subYears(uint count);

	/**
	 * Adds the count of hours given by parameter.
	 *
	 * @param count the count of hours to add
	 */
	void addHours(uint count);

	/**
	 * Subtracts the count of hours given by parameter.
	 *
	 * @param count the count of hours to subtract
	 */
	void subHours(uint count);

	/**
	 * Adds the count of minutes given by parameter.
	 *
	 * @param count the count of minutes to add
	 */
	void addMinutes(uint count);

	/**
	 * Subtracts the count of minutes given by parameter.
	 *
	 * @param count the count of minutes to subtract
	 */
	void subMinutes(uint count);

	/**
	 * Adds the count of seconds given by parameter.
	 *
	 * @param count the count of seconds to add
	 */
	void addSeconds(uint count);

	/**
	 * Subtracts the count of seconds given by parameter.
	 *
	 * @param count the count of seconds to subtract
	 */
	void subSeconds(uint count);

	/**
	 * Returns the day set.
	 *
	 * @return the day set
	 */
	byte getDay() const;

	/**
	 * Returns the month set.
	 *
	 * @return the month set
	 */
	byte getMonth() const;

	/**
	 * Returns the year set.
	 *
	 * @return the year set
	 */
	ushort getYear() const;

	/**
	 * Returns the hour set.
	 *
	 * @return the hour set
	 */
	byte getHour() const;

	/**
	 * Returns the minute set.
	 *
	 * @return the minute set
	 */
	byte getMinute() const;

	/**
	 * Returns the second set.
	 *
	 * @return the second set
	 */
	byte getSecond() const;

	/**
	 * Returns the count of month days from parameters.
	 *
	 * @param year the year to calculate
	 * @param month the month to calculate
	 */
	byte getMonthDayCount(ushort year, byte month);

	/**
	 * Returns the unix timestamp set.
	 *
	 * @return the unix timestamp
	 */
	time_t toUnixTimestamp();

	/**
	 * Returns the datetime set as string.
	 *
	 * @return the datetime set as string
	 */
	AString toString() const;

	/**
	 * Converts the datetime values to the standard time struct.
	 *
	 * @return the standard time struct
	 */
	std::tm toStdTm();

private:
	DateTimeInfo dateTimeInfo_;

	int64 unixTimestamp_;

	static DateTime dateTimeInitializer_;

	static ushort fourYearCycle_;

	static DateTimeInfo beginDateTime_;

	static byte monthDays_[];

	/**
	 * Sets the datetime values by the parameter.
	 *
	 * @param string the parsable string
	 */
	void parse(const AString& string);

	/**
	 * Calculates the unix timestamp from dateTimeInfo.
	 */
	void calculateUnixTimestamp();

	/**
	* Returns the count of days until the targeted month is reached.
	*
	* @param month the month to target
	* @param leapYear either the year to calculate is a leap year
	* @return the count of days until
	*/
	static int64 getDaysCountUntil(byte month, bool leapYear);
};

#endif // DATETIME_H
