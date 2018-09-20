#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();

    void restart();

    static std::chrono::duration<float, std::milli> getElapsedSystemTimeInSeconds();

    std::chrono::duration<float, std::milli> getElapsedTimeInSeconds() const;

    static std::chrono::duration<float, std::milli> getElapsedSystemTimeInMillis();

    std::chrono::duration<float, std::milli> getElapsedTimeInMillis() const;

    static std::chrono::time_point<std::chrono::steady_clock> getSystemTimeInSeconds();

private:
    typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

    TimePoint time_;

    static TimePoint startupTime_;
};

#endif   // STOPWATCH_H
