#include "CppUnitTest.h"
#include "stdafx.h"

#include "../SimpleCore/aqueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleCoreTest {
	TEST_CLASS(AQueueTest) {
public:
	TEST_METHOD(testEnqueue)
	{
		for (int i = 0; i < 100; ++i) {
			queue_.enqueue(i);
			Assert::IsTrue(i == queue_.dequeue());
		}
	}
	TEST_METHOD(testDequeue)
	{
		for (int i = 0; i < 100; ++i) {
			queue_.enqueue(i);
		}
		for (int i = 0; i < 100; ++i) {
			Assert::IsTrue(i == queue_.dequeue());
		}
	}
private:
	AQueue<int> queue_;
	};
}
