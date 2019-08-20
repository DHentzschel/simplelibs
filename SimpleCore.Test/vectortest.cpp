#include <avector.h>
#include <logger.h>

class VectorTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("VectorTest");

		int result = 0;
		result += Logger::logTestResult(testAppend());
		result += Logger::logTestResult(testPrepend());
		result += Logger::logTestResult(testStartsWith());
		result += Logger::logTestResult(testEndsWith());
		result += Logger::logTestResult(testIsEmpty());
		result += Logger::logTestResult(testContains());
		result += Logger::logTestResult(testCount());
		result += Logger::logTestResult(testFirstIndexOf());
		result += Logger::logTestResult(testLastIndexOf());
		result += Logger::logTestResult(testReplace());
		result += Logger::logTestResult(testRemoveAt());
		result += Logger::logTestResult(testRemoveFirst());
		result += Logger::logTestResult(testRemoveDuplicates());
		result += Logger::logTestResult(testRemoveLast());
		result += Logger::logTestResult(testRemoveFirstValue());
		result += Logger::logTestResult(testRemoveAll());
		result += Logger::logTestResult(testMid());
		result += Logger::logTestResult(testMove());
		result += Logger::logTestResult(testFirst());
		result += Logger::logTestResult(testLast());
		result += Logger::logTestResult(testTakeAt());
		result += Logger::logTestResult(testTakeFirst());
		result += Logger::logTestResult(testTakeLast());
		result += Logger::logTestResult(testToList());
		return result;
	}

	TEST_METHOD(testAppend)
	{
		Logger::logTestBegin("testAppend");
		init();

		vector_.append(6);
		ASSERT_EQUALS(6, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 1, vector_[i]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testPrepend)
	{
		Logger::logTestBegin("testPrepend");
		init();

		vector_.prepend(0);
		ASSERT_EQUALS(6, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i, vector_[i]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testStartsWith)
	{
		Logger::logTestBegin("testStartsWith");
		init();

		ASSERT(vector_.startsWith(1) && !vector_.startsWith(2));
	}

	TEST_METHOD(testEndsWith)
	{
		Logger::logTestBegin("testEndsWith");
		init();

		ASSERT(vector_.endsWith(5) && !vector_.endsWith(6));
	}

	TEST_METHOD(testIsEmpty)
	{
		Logger::logTestBegin("testIsEmpty");
		init();

		ASSERT_EQUALS(false, vector_.isEmpty());

		vector_.clear();
		ASSERT(vector_.isEmpty());
	}

	TEST_METHOD(testContains)
	{
		Logger::logTestBegin("testContains");
		init();

		byte i;
		for (i = 1; i < 6; ++i) {
			ASSERT_EQUALS(true, vector_.contains(i));
		}
		ASSERT(!vector_.contains(i));
	}

	TEST_METHOD(testCount)
	{
		Logger::logTestBegin("testCount");
		vector_.clear();

		byte count = 100;
		vector_.reserve(count * 3);

		for (byte i = 0; i < count; ++i) {
			vector_.append(i);
			vector_.append(i);
			vector_.append(i);
		}

		for (ushort i = 0; i < vector_.size(); i += 3) {
			ASSERT_EQUALS(3, vector_.count(i % 100));
		}
		TEST_FINISH;
	}

	TEST_METHOD(testFirstIndexOf)
	{
		Logger::logTestBegin("testFirstIndexOf");
		init();

		vector_.assign({ 3, 2, 1, 3, 3, 2 });

		for (byte i = 3; i > 0; --i) {
			ASSERT_EQUALS(3 - i, vector_.firstIndexOf(i));
		}
		TEST_FINISH;
	}

	TEST_METHOD(testLastIndexOf)
	{
		Logger::logTestBegin("testLastIndexOf");
		vector_.assign({ 2, 3, 3, 1, 2, 3 });

		for (byte i = 3; i > 0; --i) {
			ASSERT_EQUALS(i + 2, vector_.lastIndexOf(i));
		}
		TEST_FINISH;
	}

	TEST_METHOD(testReplace)
	{
		Logger::logTestBegin("testReplace");
		init();

		vector_.replace(2, 4);
		ASSERT(vector_[2] == 4);
	}

	TEST_METHOD(testRemoveAt)
	{
		Logger::logTestBegin("testRemoveAt");
		init();

		vector_.removeAt(0);
		ASSERT_EQUALS(4, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 2, vector_[i]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveFirst)
	{
		Logger::logTestBegin("testRemoveFirst");
		init();

		vector_.removeFirst();
		ASSERT_EQUALS(4, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 2, vector_[i]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveDuplicates)
	{
		Logger::logTestBegin("testRemoveDuplicates");
		vector_.clear();

		const byte count = 100;
		vector_.reserve(count * 3);
		for (byte i = 0; i < count; ++i) {
			vector_.append(i);
			vector_.append(i);
			vector_.append(i);
		}

		vector_.removeDuplicates();
		ASSERT_EQUALS(count, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i, vector_[i]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveLast)
	{
		Logger::logTestBegin("testRemoveLast");
		vector_.clear();

		const byte count = 100;
		vector_.reserve(1 + count * 3);

		for (byte i = 0; i < count; ++i) {
			vector_.append(i);
			vector_.append(i);
			vector_.append(i);
		}

		vector_.append(1234);
		vector_.removeLast();

		ASSERT_EQUALS(count * 3, vector_.size());

		for (ushort i = 0, j = 0; i < vector_.size(); i += 3, ++j) {
			ASSERT_EQUALS(j, vector_[i]);
			ASSERT_EQUALS(j, vector_[static_cast<size_t>(i) + 1]);
			ASSERT_EQUALS(j, vector_[static_cast<size_t>(i) + 2]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveFirstValue)
	{
		Logger::logTestBegin("testRemoveFirstValue");
		vector_.clear();

		const byte count = 100;
		vector_.reserve(1 + count * 3);

		for (byte i = 0; i < count; ++i) {
			vector_.append(i);
			vector_.append(i);
			vector_.append(i);
		}

		vector_.prepend(1234);
		vector_.removeFirst(1234);

		ASSERT_EQUALS(count * 3, vector_.size());

		for (ushort i = 0, j = 0; i < vector_.size(); i += 3, ++j) {
			ASSERT_EQUALS(j, vector_[i]);
			ASSERT_EQUALS(j, vector_[static_cast<size_t>(i) + 1]);
			ASSERT_EQUALS(j, vector_[static_cast<size_t>(i) + 2]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveAll)
	{
		Logger::logTestBegin("testRemoveAll");
		vector_.clear();

		const byte count = 100;
		vector_.reserve(count * 3);

		for (byte i = 0; i < count; ++i) {
			vector_.append(i);
			vector_.append(i);
			vector_.append(i);
		}

		vector_.removeAll(44);

		for (ushort i = 0; i < 100; ++i) {
			if (i == 44) {
				ASSERT_EQUALS(false, vector_.contains(i));
			}
			else {
				ASSERT_EQUALS(true, vector_.contains(i));
			}
		}
		TEST_FINISH;
	}

	TEST_METHOD(testMid)
	{
		Logger::logTestBegin("testMid");
		init();

		auto midVector = vector_.mid(2);
		ASSERT_EQUALS(vector_.size() - 2, midVector.size());

		for (byte i = 2; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i, vector_[i - 1]);
		}
		TEST_FINISH;
	}

	TEST_METHOD(testMove)
	{
		Logger::logTestBegin("testMove");
		init();

		vector_.move(0, 4);
		ASSERT(vector_[0] == 5 && vector_[4] == 1);
	}

	TEST_METHOD(testFirst)
	{
		Logger::logTestBegin("testFirst");
		init();

		const auto first = vector_.first();
		ASSERT(first == vector_[0]);
	}

	TEST_METHOD(testLast)
	{
		Logger::logTestBegin("testLast");
		init();

		const auto last = vector_.last();
		ASSERT(last == vector_[vector_.size() - 1]);
	}

	TEST_METHOD(testTakeAt)
	{
		Logger::logTestBegin("testTakeAt");
		init();

		const auto value = vector_.takeAt(2);
		ASSERT_EQUALS(4, vector_.size());
		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 1 + (i >= 2 ? 1 : 0), vector_[i]);
		}
		ASSERT(value == 3);
	}

	TEST_METHOD(testTakeFirst)
	{
		Logger::logTestBegin("testTakeFirst");
		init();

		const auto value = vector_.takeFirst();
		ASSERT_EQUALS(4, vector_.size());
		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 2, vector_[i]);
		}
		ASSERT(value == 1);
	}

	TEST_METHOD(testTakeLast)
	{
		Logger::logTestBegin("testTakeLast");
		init();

		const auto value = vector_.takeLast();
		ASSERT_EQUALS(4, vector_.size());
		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 1, vector_[i]);
		}
		ASSERT(value == 5);
	}

	TEST_METHOD(testToList)
	{
		Logger::logTestBegin("testToList");
		init();

		auto list = vector_.toList();
		ASSERT_EQUALS(list.size(), vector_.size());

		auto i = 0;
		for (auto it = list.begin(); it != list.end(); ++it, ++i) {
			ASSERT_EQUALS(*it, vector_[i]);
		}
		TEST_FINISH;
	}

private:
	AVector<int> vector_;

	void init()
	{
		vector_ = { 1, 2, 3, 4, 5 };
	}
};
