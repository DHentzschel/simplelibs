#include "stopwatch.h"

Stopwatch::TimePoint Stopwatch::startupTime_ = std::chrono::high_resolution_clock::now();

/**
 * \brief Constructs instance and calls restart on default.
 */
Stopwatch::Stopwatch()
{
    restart();
}

/**
 * \brief Returns elapsed time in seconds sind application startup.
 * \return elapsed time
 */
std::chrono::duration<float, std::milli> Stopwatch::getElapsedSystemTimeInSeconds()
{
    return getElapsedSystemTimeInMillis() * 0.001F;
}

/**
 * \brief Returns elapsed time in seconds.
 * \return elapsed time
 */
std::chrono::duration<float, std::milli> Stopwatch::getElapsedTimeInSeconds() const
{
    return getElapsedTimeInMillis() * 0.001F;
}

/**
 * \brief Returns elapsed time in milliseconds since application startup.
 * \return elapsed time
 */
std::chrono::duration<float, std::milli> Stopwatch::getElapsedSystemTimeInMillis()
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - startupTime_);
}

/**
 * \brief Returns elapsed time in milliseconds.
 * \return elapsed time
 */
std::chrono::duration<float, std::milli> Stopwatch::getElapsedTimeInMillis() const
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - time_);
}

std::chrono::time_point<std::chrono::steady_clock> Stopwatch::getSystemTimeInSeconds()
{
    return std::chrono::high_resolution_clock::now();
}

/**
 * \brief Resets now var to current time.
 */
void Stopwatch::restart()
{
    time_ = std::chrono::high_resolution_clock::now();
}
