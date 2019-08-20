#include <avector.h>
#include <logger.h>

class VectorTest {
public:
	int testAll() {
		Logger::logTestInit("VectorTest");

		int result = 0;
		result += Logger::logTestResult(testAppend());
		result += Logger::logTestResult(testPrepend());
		return result;
	}

	bool testAppend() {
		Logger::logTestBegin("testAppend");
		init();

		vector_.append(6);
		if (vector_.size() != 6) {
			return false;
		}

		for (byte i = 0; i < vector_.size(); ++i) {
			if (vector_[i] == i + 1) {
				continue;
			}
			return false;
		}
		return true;
	}

	bool testPrepend() {
		Logger::logTestBegin("testPrepend");
		init();

		vector_.prepend(0);
		if (vector_.size() != 6) {
			return false;
		}

		for (byte i = 0; i < vector_.size(); ++i) {
			if (vector_[i] != i) {
				return false;
			}
		}
		return true;
	}

private:
	AVector<int> vector_;

	void init() {
		vector_ = { 1, 2, 3, 4, 5 };
	}
};
