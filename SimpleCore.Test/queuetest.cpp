#include <aqueue.h>
#include <logger.h>

class QueueTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("QueueTest");
		int result = 0;
		result += Logger::logTestResult(testEnqueue());
		result += Logger::logTestResult(testDequeue());
		return result;
	}

	TEST_METHOD(testEnqueue)
	{
		Logger::logTestBegin("testEnqueue");

		for (int i = 0; i < 100; ++i) {
			queue_.enqueue(i);
			ASSERT_TRUE(i == queue_.dequeue());
		}
		TEST_FINISH;
	}

	TEST_METHOD(testDequeue)
	{
		Logger::logTestBegin("testDequeue");

		for (int i = 0; i < 100; ++i) {
			queue_.enqueue(i);
		}
		for (int i = 0; i < 100; ++i) {
			ASSERT_TRUE(i == queue_.dequeue());
		}
		TEST_FINISH;
	}

private:
	Queue<int> queue_;

};
