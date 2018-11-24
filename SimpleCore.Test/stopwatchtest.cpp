#include "CppUnitTest.h"
#include "stdafx.h"

#include <thread>
#include "../SimpleCore/stopwatch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleCoreTest {
    TEST_CLASS(StopwatchTest) {
public:

    TEST_METHOD_INITIALIZE(setUp)
    {
        stopwatch_.restart();
    }

    TEST_METHOD(testRestart)
    {
        Assert::IsTrue(stopwatch_.getElapsedTimeInMillis().count() < 10.0F);
    }

    TEST_METHOD(testGetElapsedTimeInMillis)
    {
        using namespace std::chrono_literals;
        for (char i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(100ms);

            const float elapsedTime = stopwatch_.getElapsedTimeInMillis().count();
            Assert::IsTrue(elapsedTime >= 100.0F && elapsedTime <= 103.0F);
            stopwatch_.restart();
        }
    }

    TEST_METHOD(testGetElapsedTimeInSeconds)
    {
        using namespace std::chrono_literals;
        for (char i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(100ms);

            const float elapsedTime = stopwatch_.getElapsedTimeInSeconds().count();
            Assert::IsTrue(elapsedTime >= 0.1F && elapsedTime <= 0.103F);
            stopwatch_.restart();
        }
    }

private:
    Stopwatch stopwatch_;

    };
}
