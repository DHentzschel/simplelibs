#include <logger.h>
#include <stopwatch.h>
#include <thread>

class StopwatchTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("StopwatchTest");

		int result = 0;
		result += Logger::logTestResult(testRestart());
		result += Logger::logTestResult(testGetElapsedTimeInMillis());
		result += Logger::logTestResult(testGetElapsedTimeInSeconds());
		return result;
	}

	TEST_METHOD(testRestart)
	{
		Logger::logTestBegin("testRestart");
		init();

		ASSERT(stopwatch_.getElapsedTimeInMillis().count() < 10.0F);
	}

	TEST_METHOD(testGetElapsedTimeInMillis)
	{
		Logger::logTestBegin("testGetElapsedTimeInMillis");
		init();

		using namespace std::chrono_literals;
		for (byte i = 0; i < 10; ++i) {
			std::this_thread::sleep_for(100ms);

			const float elapsedTime = stopwatch_.getElapsedTimeInMillis().count();
			ASSERT_TRUE(elapsedTime >= 100.0F && elapsedTime <= 103.0F);
			init();
		}
		TEST_FINISH;
	}

	TEST_METHOD(testGetElapsedTimeInSeconds)
	{
		Logger::logTestBegin("testGetElapsedTimeInSeconds");
		init();

		using namespace std::chrono_literals;
		for (char i = 0; i < 10; ++i) {
			std::this_thread::sleep_for(100ms);

			const float elapsedTime = stopwatch_.getElapsedTimeInSeconds().count();
			ASSERT_TRUE(elapsedTime >= 0.1F && elapsedTime <= 0.103F);
			stopwatch_.restart();
		}
		TEST_FINISH;
	}

private:
	Stopwatch stopwatch_;

	void init()
	{
		stopwatch_.restart();
	}
};
