#include <avector.h>
#include <logger.h>

class VectorTest {
public:
	int testAll()
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
		result += Logger::logTestResult(testRemoveFirst());
		return result;
	}

	bool testAppend()
	{
		Logger::logTestBegin("testAppend");
		init();

		vector_.append(6);
		ASSERT_EQUALS(6, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 1, vector_[i]);
		}
		FINISH;
	}

	bool testPrepend()
	{
		Logger::logTestBegin("testPrepend");
		init();

		vector_.prepend(0);
		ASSERT_EQUALS(6, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i, vector_[i]);
		}
		FINISH;
	}

	bool testStartsWith()
	{
		Logger::logTestBegin("testStartsWith");
		init();

		ASSERT(vector_.startsWith(1) && !vector_.startsWith(2));
	}

	bool testEndsWith()
	{
		Logger::logTestBegin("testEndsWith");
		init();

		ASSERT(vector_.endsWith(5) && !vector_.endsWith(6));
	}

	bool testIsEmpty()
	{
		Logger::logTestBegin("testIsEmpty");
		init();

		ASSERT_EQUALS(false, vector_.isEmpty());

		vector_.clear();
		ASSERT(vector_.isEmpty());
	}

	bool testContains()
	{
		Logger::logTestBegin("testContains");
		init();

		byte i;
		for (i = 1; i < 6; ++i) {
			ASSERT_EQUALS(true, vector_.contains(i));
		}
		ASSERT(!vector_.contains(i));
	}

	bool testCount()
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
		FINISH;
	}

	bool testFirstIndexOf()
	{
		Logger::logTestBegin("testFirstIndexOf");
		init();

		vector_.assign({ 3, 2, 1, 3, 3, 2 });

		for (byte i = 3; i > 0; --i) {
			ASSERT_EQUALS(3 - i, vector_.firstIndexOf(i));
		}
		FINISH;
	}

	bool testLastIndexOf()
	{
		Logger::logTestBegin("testLastIndexOf");
		vector_.assign({ 2, 3, 3, 1, 2, 3 });

		for (byte i = 3; i > 0; --i) {
			ASSERT_EQUALS(i + 2, vector_.lastIndexOf(i));
		}
		FINISH;
	}

	bool testReplace()
	{
		Logger::logTestBegin("testReplace");
		init();

		vector_.replace(2, 4);
		ASSERT(vector_[2] == 4);
	}

	bool testRemoveAt()
	{
		Logger::logTestBegin("testRemoveAt");
		init();

		vector_.removeAt(0);
		ASSERT_EQUALS(4, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 2, vector_[i]);
		}
		FINISH;
	}

	bool testRemoveFirst()
	{
		Logger::logTestBegin("testRemoveFirst");
		init();

		vector_.removeFirst();
		ASSERT_EQUALS(4, vector_.size());

		for (byte i = 0; i < vector_.size(); ++i) {
			ASSERT_EQUALS(i + 2, vector_[i]);
		}
		FINISH;
	}

private:
	AVector<int> vector_;

	void init()
	{
		vector_ = { 1, 2, 3, 4, 5 };
	}
};
