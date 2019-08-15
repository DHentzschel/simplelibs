#include <avector.h>
#include <logger.h>

class VectorTest {
public:
	int testAll() {
		LOGGER_LOG_TEST_INIT("VectorTest");

		int result = 0;
		result += LOGGER_LOG_RESULT(testAppend());
		result += LOGGER_LOG_RESULT(testPrepend());

	}

	bool testAppend() {
		LOGGER_LOG_TEST_BEGIN("testAppend");
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
		LOGGER_LOG_TEST_BEGIN("testPrepend");
		init();

		vector_.prepend(0);
		if (vector_.size() != 6) {
			return false;
		}

		for (byte i = 0; i < vector_.size(); ++i) {
			if (vector_[i] == i) {
				continue;
			}
			return false;
		}
		return true;
	}

private:
	Vector<int> vector_;

	void init() {
		vector_ = { 1, 2, 3, 4, 5 };
	}
};