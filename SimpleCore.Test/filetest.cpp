#include <file.h>
#include <dir.h>
#include <logger.h>
#include <thread>

class FileTest {
public:
	FileTest()
	{
#pragma warning(disable : 4309)
#pragma warning(disable : 4838)
		const char byteArray[] = { 0xC0, 0xDE, 0xBA, 0x5E, 0x00, 0xC0, 0xFF, 0xEE,
			0x00, 0xF0, 0x0D, 0x00, 0xFE, 0xED, 0x00, 0xFF };
#pragma warning(default : 4309)
#pragma warning(default : 4838)
		byteArray_ = ByteArray(byteArray, 16);
	}

	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("FileTest");

		int result = 0;
		result += Logger::logTestResult(testOpen());
		result += Logger::logTestResult(testExists());
		result += Logger::logTestResult(testCreate());
		result += Logger::logTestResult(testDelete());
		result += Logger::logTestResult(testReadAllText());
		result += Logger::logTestResult(testWriteAllText());
		result += Logger::logTestResult(testReadAllBytes());
		result += Logger::logTestResult(testWriteAllBytes());
		result += Logger::logTestResult(testReadLine());
		result += Logger::logTestResult(testAppend());
		result += Logger::logTestResult(testGetDirectory());
		result += Logger::logTestResult(testGetFilename());
		result += Logger::logTestResult(testSetFilepath());
		return result;
	}

	TEST_METHOD(testOpen)
	{
		Logger::logTestBegin("testOpen");
		init();

		/* This file should exists on current application path */
		ASSERT_TRUE(file_.open(OpenMode::ReadOnly));

		TEST_FINISH;
	}

	TEST_METHOD(testExists)
	{
		Logger::logTestBegin("testExists");
		init();

		const auto filename2 = Dir::getDir(Directory::CurrentApplication) + "/test/testfile2.txt";
		File file(filename2);
		if (file.exists()) {
			file.erase();
		}

		/* This file should exist */
		ASSERT_TRUE(File(Dir::getDir(Directory::CurrentApplication) + "/test/testfile.txt").exists());

		/* This file should NOT exist */
		ASSERT_TRUE(!File(filename2).exists());

		TEST_FINISH;
	}

	TEST_METHOD(testCreate)
	{
		Logger::logTestBegin("testCreate");
		init();

		Dir::erase(Dir::getDir(Directory::CurrentApplication) + "/test/test_level1", true);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		File file(Dir::getDir(Directory::CurrentApplication) + "/test/testfile4.txt");
		if (file.exists()) {
			file.erase();
		}

		/* Test simple file creation */
		ASSERT_TRUE(file.create());
		ASSERT_TRUE(file.erase());

		/* Test recursive file creation */
		const auto recursiveFilePath = Dir::getDir(Directory::CurrentApplication) + "/test/test_level1/test_level2/test_level3/testfile.txt";
		ASSERT_TRUE(File(recursiveFilePath).create(true));
		ASSERT_TRUE(File(recursiveFilePath).erase());

		/* Remove folder from recursive creation test for cleanup, true test of functionality is in extra class dirtest */
		ASSERT_TRUE(Dir(Dir::getDir(Directory::CurrentApplication) + "/test/test_level1").erase());

		TEST_FINISH;
	}

	TEST_METHOD(testDelete)
	{
		Logger::logTestBegin("testDelete");
		init();

		/* Make sure the file exists */
		File file(Dir::getDir(Directory::CurrentApplication) + "/test/testfile3.txt");
		if (!file.exists()) {
			ASSERT_TRUE(file.create());
		}

		/* Test file deletion */
		ASSERT_TRUE(file.erase());
		TEST_FINISH;
	}

	TEST_METHOD(testReadAllText)
	{
		Logger::logTestBegin("testReadAllText");
		init();

		ASSERT_TRUE(file_.readAllText() == exampleFileContent_);

		TEST_FINISH;
	}

	TEST_METHOD(testWriteAllText)
	{
		Logger::logTestBegin("testWriteAllText");
		init();

		File file(Dir::getDir(Directory::CurrentApplication) + "/test/testfile2.txt");
		if (file.exists()) {
			file.erase();
			file.create();
		}

		file.writeAllText(exampleFileContent_);
		ASSERT_TRUE(file.readAllText() == exampleFileContent_);
		file.close();
		file.erase();

		TEST_FINISH;
	}

	TEST_METHOD(testReadAllBytes)
	{
		Logger::logTestBegin("testReadAllBytes");
		init();

		ASSERT_TRUE(file2_.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));

		TEST_FINISH;
	}

	TEST_METHOD(testWriteAllBytes)
	{
		Logger::logTestBegin("testWriteAllBytes");
		init();

		File file(Dir::getDir(Directory::CurrentApplication) + "/test/testfile2.txt");
		if (file.exists()) {
			file.erase();
			file.create();
		}

		file.writeAllBytes(byteArray_);
		ASSERT_TRUE(file.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));
		file.close();
		file.erase();

		TEST_FINISH;
	}

	TEST_METHOD(testReadLine)
	{
		Logger::logTestBegin("testReadLine");
		init();

		ASSERT_TRUE(file_.open(OpenMode::ReadOnly));

		AString buffer;
		while (!file_.atEnd()) {
			buffer += file_.readLine();
		}

		ASSERT_TRUE(AString(exampleFileContent_).removeAll('\n') == buffer);

		TEST_FINISH;
	}

	TEST_METHOD(testAppend)
	{
		Logger::logTestBegin("testAppend");
		init();

		File file(Dir::getDir(Directory::CurrentApplication) + "/test/testfile2.txt");
		if (file.exists()) {
			file.erase();
			file.create();
		}

		ASSERT_TRUE(file.open(OpenMode::ReadWrite | OpenMode::Append));
		const AString appendable = "Appendable text";
		file.append(appendable);
		ASSERT_TRUE(appendable == file.readAllText());
		file.close();
		file.erase();

		TEST_FINISH;
	}

	TEST_METHOD(testGetDirectory)
	{
		Logger::logTestBegin("testGetDirectory");
		init();

#ifdef OS_WIN
		const AString directory = "C:/Users/test/";
#elif defined OS_LINUX || defined OS_UNIX
		const AString directory = "/home/test/";
#endif // OS_LINUX || OS_UNIX
		const auto* filename = "test.txt";

		/* Testing absolute path. */
		File file(directory + filename);
		ASSERT_TRUE(directory.left(directory.size() - 1) == file.getDirectory());

		/* Testing relative path. All relative paths will be concatenated at the end with the sub path of the VS test unit */
		file = File(filename);
		ASSERT_TRUE(file.getDirectory().contains(Dir::getDir(Directory::CurrentApplication), false));

		TEST_FINISH;
	}

	TEST_METHOD(testGetFilename)
	{
		Logger::logTestBegin("testGetFilename");
		init();

		const AString filename = "test.txt";
#ifdef OS_WIN
		File file("C:/Users/test/" + filename);
#elif defined OS_LINUX || defined OS_UNIX
		File file("/home/test/" + filename);
#endif // OS_LINUX || OS_UNIX
		auto assertFilenameEqualsExpected = [filename, file]() {
			return filename == file.getFilename();
		};

		ASSERT_TRUE(assertFilenameEqualsExpected());
		file = File(file.getFilename());
		ASSERT_TRUE(assertFilenameEqualsExpected());

		TEST_FINISH;
	}

	TEST_METHOD(testSetFilepath)
	{
		Logger::logTestBegin("testSetFilepath");
		init();

#ifdef OS_WIN
		AString filepath = "C:\\Users\\test\\test.txt";
#elif defined OS_LINUX || defined OS_UNIX
		AString filepath = "\\home\\test\\test.txt";
#endif // OS_LINUX || OS_UNIX

		/* setFilePath() is being invoked in the ctor */
		File file(filepath);
		ASSERT_TRUE(filepath.replaceAll("\\", "/") == file.getFilepath());

		TEST_FINISH;
	}


private:
	File file_;

	File file2_;

	ByteArray byteArray_;

	const char* exampleFileContent_ = "This is a\ntext file example\n";

	void init()
	{
		file_.close();
		file2_.close();
		file_ = File(Dir::getDir(Directory::CurrentApplication) + "/test/testfile.txt");
		file2_ = File(Dir::getDir(Directory::CurrentApplication) + "/test/testfile2.bin");
	}
};
