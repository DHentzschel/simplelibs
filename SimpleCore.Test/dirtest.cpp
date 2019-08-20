#include <dir.h>
#include <logger.h>
#include <thread>

class DirTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("testAll");

		int result = 0;
		result += Logger::logTestResult(testSetPath());
		result += Logger::logTestResult(testCreate());
		result += Logger::logTestResult(testExists());
		result += Logger::logTestResult(testErase());
		result += Logger::logTestResult(testGetFileCount());
		return result;
	}

	TEST_METHOD(testSetPath)
	{
		Logger::logTestBegin("testSetPath");
		init();

		/* Testing relative path. */
		Dir dir("test");
#ifdef OS_WIN
		/* All relative paths will be concatenated at the end with the sub path of the VS test unit */
		auto result = dir.getPath().contains(Dir::getDir(Directory::CurrentApplication), false);
		ASSERT_TRUE(dir.getPath().contains(Dir::getDir(Directory::CurrentApplication), false));
#elif defined OS_LINUX || defined OS_UNIX
#endif // OS_LINUX || OS_UNIX
		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testCreate)
	{
		Logger::logTestBegin("testCreate");
		init();

		/* This directory MUST NOT exist */
		Dir dir(Dir::getDir(Directory::Desktop) + "/testdir2");
		if (dir.exists()) {
			dir.erase();
		}
		ASSERT_TRUE(dir.create());
		dir.erase();

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testExists)
	{
		Logger::logTestBegin("testExists");
		init();

		/* This directory has to exist */
		Dir dir(Dir::getDir(Directory::Desktop) + "/testdir");
		ASSERT_TRUE(dir.exists());

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testErase)
	{
		Logger::logTestBegin("testErase");
		init();

		Dir dir(Dir::getDir(Directory::Desktop) + "/testdir2");
		if (!dir.exists()) {
			dir.create();
		}
		ASSERT_TRUE(dir.erase());

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testGetFileCount)
	{
		Logger::logTestBegin("testGetFileCount");
		init();

		Dir dir(Dir::getDir(Directory::Desktop) + "/testdir");
		if (dir.exists()) {
			dir.erase();
		}
		dir.create();
		File file(dir.getPath());

		dispose();
		TEST_FINISH;
	}
private:
	void init()
	{
#ifdef OS_WIN
		system("setup.bat");
#elif defined OS_LINUX || defined OS_UNIX
		system("sh setup.sh");
#endif // OS_LINUX || OS_UNIX
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10ms);
	}

	void dispose()
	{
#ifdef OS_WIN
		system("cleanup.bat");
#elif defined OS_LINUX || defined OS_UNIX
		system("sh cleanup.sh");
#endif // OS_LINUX || OS_UNIX
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10ms);
	}
};
