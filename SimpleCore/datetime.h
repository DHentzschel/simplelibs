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
	SIMPLECORE_API DateTime();

	/**
	 * Sets the unixTimestamp member variable to zero and copies the dateTimeInfo from parameter.
	 *
	 * @param dateTimeInfo the copyable dateTimeInfo
	 */
	SIMPLECORE_API DateTime(const DateTimeInfo& dateTimeInfo);

	/**
	 * Sets the unixTimestamp member variable to zero and parses the datetime from string parameter.
	 *
	 * @param string the parsable datetime string
	 */
	SIMPLECORE_API DateTime(const AString& string);

	/**
	 * Returns the current datetime as object.
	 */
	SIMPLECORE_API static DateTime now();

	/**
	 * Returns the current datestamp in the format "dd.MM.yyyy".
	 *
	 * @return the datestamp as string
	 */
	SIMPLECORE_API static AString getDatestamp();

	/**
	 * Returns the current timestamp in the following format: hh:mm:ss
	 *
	 * @return the timestamp as string
	 */
	SIMPLECORE_API static AString getTimestamp();

	/**
	 * Returns the current date and timestamp in the following format: dd.MM.yyyy hh:mm:ss
	 *
	 * @return the current date and timestamp as string
	 */
	SIMPLECORE_API static AString getCurrentTimestamp();

	/**
	 * Returns whether the datetime specified was reached.
	 *
	 * @param reachableDatetime the reachable datetime
	 * @return whether the datetime specified was reached
	 */
	SIMPLECORE_API static bool isDateTimeReached(const DateTime& reachableDatetime);

	/**
	 * Returns whether the datetime specified was reached.
	 *
	 * @param reachableDatetime the reachable datetime
	 * @return whether the datetime specified was reached
	 */
	SIMPLECORE_API static bool isDateTimeReached(const AString& reachableDatetime);

	/**
	 * Returns whether the datetime specified was reached.
	 *
	 * @param target the datetime which implies "now"
	 * @param reachableDatetime the reachable datetime
	 * @return whether the datetime specified was reached
	 */
	SIMPLECORE_API static bool isDateTimeReached(const AString& target, const AString& reachableDatetime);
	/**
	 * Returns whether the year given as parameter is a leap year.
	 *
	 * @param year the year to check
	 * @return whether specified year is a leap year
	 */
	SIMPLECORE_API static bool isLeapYear(ushort year);

	/**
	 * Returns the count of leap years from the first year to the second year.
	 *
	 * @param to the begin date
	 * @param from the end date
	 * @return the leap year count between both years
	 */
	SIMPLECORE_API static ushort getLeapYearCountFromTo(ushort to, ushort from = beginDateTime_.year);

	/**
	 * Returns the datetime instance calculated from given timestamp parameter.
	 *
	 * @param timestamp the unix timestamp in seconds
	 * @return the DateTime instance intialized by specified timestamp
	 */
	SIMPLECORE_API static DateTime fromUnixTimestamp(int64 timestamp);

	/**
	 * Adds the count of days given by parameter.
	 *
	 * @param count the count of days to add
	 */
	SIMPLECORE_API void addDays(uint count);

	/**
	 * Subtracts the count of days given by parameter.
	 *
	 * @param count the count of days to subtract
	 */
	SIMPLECORE_API void subDays(uint count);

	/**
	 * Adds the count of months given by parameter.
	 *
	 * @param count the count of months to add
	 */
	SIMPLECORE_API void addMonths(uint count);

	/**
	 * Subtracts the count of months given by parameter.
	 *
	 * @param count the count of months to subtract
	 */
	SIMPLECORE_API void subMonths(uint count);

	/**
	 * Adds the count of years given by parameter.
	 *
	 * @param count the count of years to add
	 */
	SIMPLECORE_API void addYears(uint count);

	/**
	 * Subtracts the count of years given by parameter.
	 *
	 * @param count the count of years to subtract
	 */
	SIMPLECORE_API void subYears(uint count);

	/**
	 * Adds the count of hours given by parameter.
	 *
	 * @param count the count of hours to add
	 */
	SIMPLECORE_API void addHours(uint count);

	/**
	 * Subtracts the count of hours given by parameter.
	 *
	 * @param count the count of hours to subtract
	 */
	SIMPLECORE_API void subHours(uint count);

	/**
	 * Adds the count of minutes given by parameter.
	 *
	 * @param count the count of minutes to add
	 */
	SIMPLECORE_API void addMinutes(uint count);

	/**
	 * Subtracts the count of minutes given by parameter.
	 *
	 * @param count the count of minutes to subtract
	 */
	SIMPLECORE_API void subMinutes(uint count);

	/**
	 * Adds the count of seconds given by parameter.
	 *
	 * @param count the count of seconds to add
	 */
	SIMPLECORE_API void addSeconds(uint count);

	/**
	 * Subtracts the count of seconds given by parameter.
	 *
	 * @param count the count of seconds to subtract
	 */
	SIMPLECORE_API void subSeconds(uint count);

	/**
	 * Returns the day set.
	 *
	 * @return the day set
	 */
	SIMPLECORE_API byte getDay() const;

	/**
	 * Returns the month set.
	 *
	 * @return the month set
	 */
	SIMPLECORE_API byte getMonth() const;

	/**
	 * Returns the year set.
	 *
	 * @return the year set
	 */
	SIMPLECORE_API ushort getYear() const;

	/**
	 * Returns the hour set.
	 *
	 * @return the hour set
	 */
	SIMPLECORE_API byte getHour() const;

	/**
	 * Returns the minute set.
	 *
	 * @return the minute set
	 */
	SIMPLECORE_API byte getMinute() const;

	/**
	 * Returns the second set.
	 *
	 * @return the second set
	 */
	SIMPLECORE_API byte getSecond() const;

	/**
	 * Returns the count of month days from parameters.
	 *
	 * @param year the year to calculate
	 * @param month the month to calculate
	 */
	SIMPLECORE_API byte getMonthDayCount(ushort year, byte month);

	/**
	 * Returns the unix timestamp set.
	 *
	 * @return the unix timestamp
	 */
	SIMPLECORE_API time_t toUnixTimestamp();

	/**
	 * Returns the datetime set as string.
	 *
	 * @return the datetime set as string
	 */
	SIMPLECORE_API AString toString() const;

	/**
	 * Converts the datetime values to the standard time struct.
	 *
	 * @return the standard time struct
	 */
	SIMPLECORE_API std::tm toStdTm();

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
	* @param leapYear whether the year to calculate is a leap year
	* @return the count of days until
	*/
	static int64 getDaysCountUntil(byte month, bool leapYear);
};

#endif // DATETIME_H
