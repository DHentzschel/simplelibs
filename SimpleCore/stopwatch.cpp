#include "stopwatch.h"

Stopwatch::TimePoint Stopwatch::startupTime_ = std::chrono::high_resolution_clock::now();

Stopwatch::Stopwatch()
{
    restart();
}

void Stopwatch::restart()
{
    time_ = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<float, std::milli> Stopwatch::getElapsedSystemTimeInSeconds()
{
    return getElapsedSystemTimeInMillis() * 0.001F;
}

std::chrono::duration<float, std::milli> Stopwatch::getElapsedTimeInSeconds() const
{
    return getElapsedTimeInMillis() * 0.001F;
}

std::chrono::duration<float, std::milli> Stopwatch::getElapsedSystemTimeInMillis()
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - startupTime_);
}

std::chrono::duration<float, std::milli> Stopwatch::getElapsedTimeInMillis() const
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - time_);
}

std::chrono::time_point<std::chrono::steady_clock> Stopwatch::getSystemTimeInSeconds()
{
    return std::chrono::high_resolution_clock::now();
}
