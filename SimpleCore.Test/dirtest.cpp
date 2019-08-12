#include "CppUnitTest.h"
#include "stdafx.h"

#include "../SimpleCore/dir.h"
#include "../SimpleCore/file.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleCoreTest {
	TEST_CLASS(DirTest) {
public:
	DirTest()
	{
		system("setup.bat");
	}

	~DirTest()
	{
		system("cleanup.bat");
	}

	TEST_METHOD(testSetPath)
	{
		/* Testing relative path. All relative paths will be concatenated at the end with the sub path of the VS test unit */
		Dir dir("test");
		auto result = dir.getPath().contains("/COMMON7/IDE/EXTENSIONS/TESTPLATFORM", false);
		Assert::IsTrue(dir.getPath().contains("/COMMON7/IDE/EXTENSIONS/TESTPLATFORM", false));
	}

	TEST_METHOD(testCreate)
	{
		/* This directory MUST NOT exist */
		Dir dir(Dir::getDir(Directory::Desktop) + "\\testdir2");
		if (dir.exists()) {
			dir.erase();
		}
		Assert::IsTrue(dir.create());
		dir.erase();
	}

	TEST_METHOD(testExists)
	{
		/* This directory has to exist */
		Dir dir(Dir::getDir(Directory::Desktop) + "\\testdir");
		Assert::IsTrue(dir.exists());
	}

	TEST_METHOD(testErase)
	{
		Dir dir(Dir::getDir(Directory::Desktop) + "\\testdir2");
		if (!dir.exists()) {
			dir.create();
		}

		Assert::IsTrue(dir.erase());
	}

	TEST_METHOD(testGetFileCount)
	{
		Dir dir(Dir::getDir(Directory::Desktop) + "\\testdir");
		if (dir.exists()) {
			dir.erase();
		}
		dir.create();
		File file(dir.getPath());
	}
	};
}