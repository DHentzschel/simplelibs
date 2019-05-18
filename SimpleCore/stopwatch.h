#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

/**
 * This class makes it easy to measure the runtime.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class Stopwatch {
public:
	/**
	 * Calls the restart functions on default.
	 */
	Stopwatch();

	/**
	 * Resets the time variable to the current time.
	 */
	void restart();

	/**
	 * Returns the elapsed time in seconds since the application startup.
	 *
	 * @return the elapsed time in seconds
	 */
	static std::chrono::duration<float, std::milli> getElapsedSystemTimeInSeconds();

	/**
	 * Returns the elapsed time in seconds.
	 *
	 * @return the elapsed time in seconds
	 */
	std::chrono::duration<float, std::milli> getElapsedTimeInSeconds() const;

	/**
	 * Returns the elapsed time in milliseconds since the application startup.
	 *
	 * @return the elapsed time in milliseconds
	 */
	static std::chrono::duration<float, std::milli> getElapsedSystemTimeInMillis();

	/**
	 * Returns the elapsed time in milliseconds.
	 *
	 * @return the elapsed time in milliseconds
	 */
	std::chrono::duration<float, std::milli> getElapsedTimeInMillis() const;

	/**
	 * Returns the current system time in seconds.
	 *
	 * @return the current system time in seconds
	 */
	static std::chrono::time_point<std::chrono::steady_clock> getSystemTimeInSeconds();

private:
	typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

	TimePoint time_;

	static TimePoint startupTime_;
};

#endif   // STOPWATCH_H
