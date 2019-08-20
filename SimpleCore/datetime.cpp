#include "datetime.h"

#include "char.h"
#include "osdetection.h"

DateTime DateTime::dateTimeInitializer_;

ushort DateTime::fourYearCycle_ = 1461;

DateTimeInfo DateTime::beginDateTime_ = DateTimeInfo(1, 1, 1970, 0, 0, 0);

byte DateTime::monthDays_[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DateTime::DateTime() :
	unixTimestamp_(0)
{}

DateTime::DateTime(const DateTimeInfo& dateTimeInfo) :
	unixTimestamp_(0),
	dateTimeInfo_(dateTimeInfo)
{}

DateTime::DateTime(const AString& string) :
	unixTimestamp_(0)
{
	parse(string);
}

DateTime DateTime::now()
{
	char buffer[20];
	auto tm = getTm();
	std::strftime(buffer, sizeof buffer, "%d.%m.%Y %H:%M:%S", &tm);
	DateTime dateTime;
	dateTime.parse(buffer);
	return dateTime;
}

AString DateTime::getDatestamp()
{
	char buffer[11];
	auto tm = getTm();
	std::strftime(buffer, sizeof buffer, "%d.%m.%Y", &tm);
	return buffer;
}

AString DateTime::getTimestamp()
{
	char buffer[9];
	auto tm = getTm();
	std::strftime(buffer, sizeof buffer, "%H.%M.%S", &tm);
	return buffer;
}

AString DateTime::getCurrentTimestamp()
{
	return now().toString();
}

bool DateTime::isDateTimeReached(const DateTime& dateTime)
{
	return now().unixTimestamp_ >= dateTime.unixTimestamp_;
}

bool DateTime::isDateTimeReached(const AString& comparable)
{
	return now().unixTimestamp_ >= DateTime(comparable).unixTimestamp_;
}

bool DateTime::isDateTimeReached(const AString& target, const AString& comparable)
{
	return DateTime(comparable).unixTimestamp_ >= DateTime(target).unixTimestamp_;
}

bool DateTime::isLeapYear(const ushort year)
{
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

ushort DateTime::getLeapYearCountFromTo(ushort to, ushort from)
{
	ushort result = 0;
	for (ushort i = isLeapYear(from) ? from : from + 2; i <= to; i += 4) {
		++result;
	}
	return result;
}

DateTime DateTime::fromUnixTimestamp(const int64 timestamp)
{
	auto sysTime = std::chrono::system_clock::from_time_t(timestamp);
	auto tm = getTm((time_t*)& timestamp);

	DateTime result;
	DateTimeInfo dateTimeInfo;
	dateTimeInfo.day = tm.tm_mday;
	dateTimeInfo.month = tm.tm_mon + 1;
	dateTimeInfo.year = tm.tm_year;
	dateTimeInfo.hour = tm.tm_hour;
	dateTimeInfo.minute = tm.tm_min;
	dateTimeInfo.second = tm.tm_sec;
	result.dateTimeInfo_ = dateTimeInfo;
	result.unixTimestamp_ = timestamp;
	return result;
}

void DateTime::addDays(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ + static_cast<int64>(count) * 86400);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::subDays(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ - static_cast<int64>(count) * 86400);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::addMonths(uint count)
{
	if (count > 0) {
		bool tempIsLeapYearAnFebruary = false;
		auto daysTotal = 0;
		auto monthOld = 0;

		auto calculateRest = [this](bool& tempIsLeapYearAnFebruary, int& daysTotal) {
			tempIsLeapYearAnFebruary = dateTimeInfo_.month == 2 && isLeapYear(dateTimeInfo_.year);
			daysTotal += monthDays_[dateTimeInfo_.month - 1] - dateTimeInfo_.day + 1 + (tempIsLeapYearAnFebruary ? 1 : 0);
		};

		auto addFirstMonth = [count, this] {
			if (count % 12 != 0) {
				++dateTimeInfo_.month;
				dateTimeInfo_.month %= 13;
				if (dateTimeInfo_.month == 0) {
					dateTimeInfo_.month = 1;
				}
			}
		};

		auto calculateYear = [this](int monthOld) {
			dateTimeInfo_.year += (monthOld > dateTimeInfo_.month ? 1 : 0);
		};

		auto maxIndex = count;

		calculateRest(tempIsLeapYearAnFebruary, daysTotal);
		monthOld = dateTimeInfo_.month;
		addFirstMonth();
		calculateYear(monthOld);

		if (maxIndex > 12) {
			addYears(count / 12);
			maxIndex = count % 12;
		}

		for (uint i = 1; i < maxIndex; ++i) {
			monthOld = dateTimeInfo_.month;
			calculateRest(tempIsLeapYearAnFebruary, daysTotal);
			addFirstMonth();
			calculateYear(monthOld);
		}

		calculateUnixTimestamp();
	}
}

void DateTime::subMonths(uint count)
{
	if (count > 0) {
		bool tempIsLeapYearAnFebruary = false;
		auto monthOld = 0;

		auto calculateRest = [this](bool& tempIsLeapYearAnFebruary/*, int& daysTotal*/) {
			tempIsLeapYearAnFebruary = dateTimeInfo_.month == 2 && isLeapYear(dateTimeInfo_.year);
		};

		auto calculateMonth = [count, this] {
			if (count % 12 != 0) {
				--dateTimeInfo_.month;
				if (dateTimeInfo_.month == 0) {
					dateTimeInfo_.month = 12;
				}
			}
		};

		auto calculateYear = [this](int monthOld) {
			dateTimeInfo_.year -= (monthOld < dateTimeInfo_.month ? 1 : 0);
		};


		calculateRest(tempIsLeapYearAnFebruary);
		monthOld = dateTimeInfo_.month;
		calculateMonth();
		calculateYear(monthOld);

		auto maxIndex = count;
		if (count > 12) {
			subYears(count / 12);
			maxIndex = count % 12;
		}

		for (uint i = 1; i < maxIndex; ++i) {
			monthOld = dateTimeInfo_.month;
			calculateRest(tempIsLeapYearAnFebruary);
			calculateMonth();
			calculateYear(monthOld);
		}

		calculateUnixTimestamp();
	}
}

void DateTime::addYears(uint count)
{
	if (count > 0) {
		for (uint i = 0; i < count; ++i) {
			++dateTimeInfo_.year;
		}

		calculateUnixTimestamp();
	}
}

void DateTime::subYears(uint count)
{
	if (count > 0) {
		for (uint i = 0; i < count; ++i) {
			--dateTimeInfo_.year;
		}

		calculateUnixTimestamp();
	}
}

void DateTime::addHours(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ + static_cast<int64>(count) * 3600);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::subHours(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ - static_cast<int64>(count) * 3600);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::addMinutes(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ + static_cast<int64>(count) * 60);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::subMinutes(uint count)
{
	if (count == 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ - static_cast<int64>(count) * 60);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::addSeconds(uint count)
{
	if (count > 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ + count);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

void DateTime::subSeconds(uint count)
{
	if (count == 0) {
		DateTime dateTime = fromUnixTimestamp(unixTimestamp_ - count);
		dateTimeInfo_ = dateTime.dateTimeInfo_;
		unixTimestamp_ = dateTime.unixTimestamp_;
	}
}

byte DateTime::getDay() const
{
	return dateTimeInfo_.day;
}

byte DateTime::getMonth() const
{
	return dateTimeInfo_.month;
}

ushort DateTime::getYear() const
{
	return dateTimeInfo_.year;
}

byte DateTime::getHour() const
{
	return dateTimeInfo_.hour;
}

byte DateTime::getMinute() const
{
	return dateTimeInfo_.minute;
}

byte DateTime::getSecond() const
{
	return dateTimeInfo_.second;
}

byte DateTime::getMonthDayCount(ushort year, byte month)
{
	if (month == 0 || month > 12) {
		return 0;
	}
	bool addOne = month == 2 && isLeapYear(year);
	return monthDays_[month - 1] + (addOne ? 1 : 0);
}

int64 DateTime::toUnixTimestamp()
{
	return unixTimestamp_;
}

AString DateTime::toString() const
{
	return (dateTimeInfo_.day < 10 ? "0" : "") + AString::toString(dateTimeInfo_.day) + "."
		+ (dateTimeInfo_.month < 10 ? "0" : "") + AString::toString(dateTimeInfo_.month) + "."
		+ AString::toString(dateTimeInfo_.year) + " "
		+ (dateTimeInfo_.hour < 10 ? "0" : "") + AString::toString(dateTimeInfo_.hour) + ":"
		+ (dateTimeInfo_.minute < 10 ? "0" : "") + AString::toString(dateTimeInfo_.minute) + ":"
		+ (dateTimeInfo_.second < 10 ? "0" : "") + AString::toString(dateTimeInfo_.second);
}

std::tm DateTime::toStdTm()
{
	std::tm result;
	result.tm_year = dateTimeInfo_.year;
	result.tm_mon = dateTimeInfo_.month;
	result.tm_mday = dateTimeInfo_.day;
	result.tm_hour = dateTimeInfo_.hour;
	result.tm_min = dateTimeInfo_.minute;
	result.tm_sec = dateTimeInfo_.second;
	result.tm_wday = 0;
	result.tm_yday = 0;
	result.tm_isdst = 0;
	return result;
}

void DateTime::parse(const AString& string)
{
	const auto dateTimeArray = string.splitByNonNumerics();
	if (dateTimeArray.size() != 6) {
		return;
	}

	dateTimeInfo_.day = dateTimeArray[0].toByte();
	dateTimeInfo_.month = dateTimeArray[1].toByte();
	dateTimeInfo_.year = dateTimeArray[2].toUShort();
	dateTimeInfo_.hour = dateTimeArray[3].toByte();
	dateTimeInfo_.minute = dateTimeArray[4].toByte();
	dateTimeInfo_.second = dateTimeArray[5].toByte();

	calculateUnixTimestamp();
}

void DateTime::calculateUnixTimestamp()
{
	const auto differenceToBeginDate = dateTimeInfo_.year - beginDateTime_.year;
	const auto leapYearCount = getLeapYearCountFromTo(static_cast<ushort>(dateTimeInfo_.year));
	const auto difference = differenceToBeginDate - leapYearCount;

	unixTimestamp_ = 0;

	/* Add full leap year seconds */
	unixTimestamp_ += static_cast<int64>(leapYearCount) * 31622400;
	/* Add full normal year seconds */
	unixTimestamp_ += static_cast<int64>(difference) * 31536000;
	/* ???? */
	//unixTimestamp_ += (dateTimeInfo_.day - 1) * 86400;

	unixTimestamp_ += getDaysCountUntil(dateTimeInfo_.month, isLeapYear(dateTimeInfo_.year)) * 86400;

	unixTimestamp_ += static_cast<int64>(dateTimeInfo_.day - 1) * 86400;

	/* Add full hour seconds */
	unixTimestamp_ += static_cast<int64>(dateTimeInfo_.hour) * 3600;
	/* Add full minute seconds */
	unixTimestamp_ += static_cast<int64>(dateTimeInfo_.minute) * 60;
	/* Add seconds */
	unixTimestamp_ += dateTimeInfo_.second;
}

int64 DateTime::getDaysCountUntil(byte month, bool leapYear)
{
	int64 daysResult = 0;
	for (char i = month - 2; i >= 0; --i) {
		daysResult += monthDays_[i];
		if (i == 1 && leapYear) {
			daysResult += 1;
		}
	}
	return daysResult;
}

std::tm DateTime::getTm(std::time_t* timestamp)
{
	std::tm tm;
	std::time_t timeNow = time(timestamp);
#ifdef OS_WIN
#  pragma warning (disable : 6001)
	localtime_s(&tm, &timeNow);
#  pragma warning (default : 6001)
#else
	tm = *std::localtime(&timeNow);
#endif // !OS_WIN
	return tm;
}
