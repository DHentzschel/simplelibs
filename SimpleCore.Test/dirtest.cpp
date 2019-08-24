#include <dir.h>
#include <logger.h>
#include <thread>

class DirTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("DirTest");

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

		/* Testing relative path. */
		Dir dir("test");
		ASSERT_TRUE(dir.getPath().contains(Dir::getDir(Directory::CurrentApplication).replaceAll("\\", "/"), false));
		
		TEST_FINISH;
	}

	TEST_METHOD(testCreate)
	{
		Logger::logTestBegin("testCreate");

		/* This directory MUST NOT exist */
		Dir dir(Dir::getDir(Directory::CurrentApplication) + "/test/testdir2");
		if (dir.exists()) {
			dir.erase();
		}
		ASSERT_TRUE(dir.create());
		dir.erase();

		TEST_FINISH;
	}

	TEST_METHOD(testExists)
	{
		Logger::logTestBegin("testExists");

		/* This directory has to exist */
		Dir dir(Dir::getDir(Directory::CurrentApplication) + "/test/testdir");
		ASSERT_TRUE(dir.exists());

		TEST_FINISH;
	}

	TEST_METHOD(testErase)
	{
		Logger::logTestBegin("testErase");

		Dir dir(Dir::getDir(Directory::CurrentApplication) + "/test/testdir2");
		if (!dir.exists()) {
			dir.create();
		}
		ASSERT_TRUE(dir.erase());

		TEST_FINISH;
	}

	TEST_METHOD(testGetFileCount)
	{
		Logger::logTestBegin("testGetFileCount");

		Dir dir(Dir::getDir(Directory::CurrentApplication) + "/test/testdir");
		if (dir.exists()) {
			dir.erase();
		}
		dir.create();
		File file(dir.getPath());

		TEST_FINISH;
	}
};
