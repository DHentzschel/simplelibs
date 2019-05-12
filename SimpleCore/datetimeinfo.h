#ifndef DATETIMEINFO_H
#define DATETIMEINFO_H

#include "types.h"

/**
 * This struct stores datetime information.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
struct DateTimeInfo {
	byte day;
	byte month;
	ushort year;
	byte hour;
	byte minute;
	byte second;

	/**
	 * Sets the values to 01.01.1970 00:00 on default.
	 */
	DateTimeInfo() :
		day(1),
		month(1),
		year(1970),
		hour(0),
		minute(0),
		second(0)
	{}

	/**
	* Sets the values by the given date and time parameters.
	*
	* @param day the day to set
	* @param month the month to set
	* @param year the year to set
	* @param hour the hour to set
	* @param minute the minute to set
	* @param second the second to set
	*/
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

#endif // !DATETIMEINFO_H
