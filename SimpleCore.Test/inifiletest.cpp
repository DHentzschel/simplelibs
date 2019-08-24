#include <logger.h>
#include <inifile.h>

class IniFileTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("IniFileTest");

		int result = 0;
		result += Logger::logTestResult(testSetValue());
		result += Logger::logTestResult(testValue());
		result += Logger::logTestResult(testDeleteGroup());
		result += Logger::logTestResult(testGetGroupCount());
		result += Logger::logTestResult(testGetKeyCount());
		return result;
	}

	TEST_METHOD(testSetValue)
	{
		Logger::logTestBegin("testSetValue");
		init();

		auto fileContent = readFile();
		auto expectedCopy = AString(expectedString_);

		ASSERT_EQUALS(expectedCopy, fileContent);

		expectedCopy.replaceFirst("val0", "vala");
		expectedCopy.replaceFirst("val1", "valb");
		expectedCopy.replaceFirst("val2", "valc");
		expectedCopy.replaceFirst("val3", "vald");
		expectedCopy.replaceFirst("val4", "vale");
		expectedCopy.replaceFirst("val5", "valf");

		iniFile_.beginGroup("TestGroup0");
		iniFile_.setValue("key0", "vala");
		iniFile_.setValue("key1", "valb");

		iniFile_.beginGroup("TestGroup2");
		iniFile_.setValue("key2", "valc");
		iniFile_.setValue("key3", "vald");

		iniFile_.beginGroup("TestGroup4");
		iniFile_.setValue("key4", "vale");
		iniFile_.setValue("key5", "valf");

		fileContent = readFile();
		ASSERT_EQUALS(expectedCopy, fileContent);

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testValue)
	{
		Logger::logTestBegin("testValue");
		init();

		for (int i = 0; i < 6; ++i) {
			if (i % 2 == 0) {
				iniFile_.beginGroup("TestGroup" + AString::toString(i));
			}
			const auto value = iniFile_.value("key" + AString::toString(i));
			ASSERT_EQUALS("val" + AString::toString(i), value);
		}

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testDeleteGroup)
	{
		Logger::logTestBegin("testDeleteGroup");
		init();

		iniFile_.deleteGroup("TestGroup2");
		const auto fileContent = readFile();
		const auto expectedCopy = AString(expectedString_).removeFirst("[TestGroup2]\nkey2 = val2\nkey3 = val3\n\n");
		ASSERT_EQUALS(expectedCopy, fileContent);

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testGetGroupCount)
	{
		Logger::logTestBegin("testGetKeyCount");
		init();

		ASSERT_EQUALS(3, iniFile_.getGroupCount());

		dispose();
		TEST_FINISH;
	}

	TEST_METHOD(testGetKeyCount)
	{
		Logger::logTestBegin("testGetKeyCount");
		init();

		ASSERT_EQUALS(6, iniFile_.getKeyCount());

		dispose();
		TEST_FINISH;
	}

private:
	IniFile iniFile_;

	AString expectedString_ = "[TestGroup0]\nkey0 = val0\nkey1 = val1\n\n"
		"[TestGroup2]\nkey2 = val2\nkey3 = val3\n\n"
		"[TestGroup4]\nkey4 = val4\nkey5 = val5\n\n";

	void init()
	{
		iniFile_ = IniFile();
		iniFile_.setFilepath("test/test.ini");
		iniFile_.beginGroup("TestGroup0");
		iniFile_.setValue("key0", "val0");
		iniFile_.setValue("key1", "val1");

		iniFile_.beginGroup("TestGroup2");
		iniFile_.setValue("key2", "val2");
		iniFile_.setValue("key3", "val3");

		iniFile_.beginGroup("TestGroup4");
		iniFile_.setValue("key4", "val4");
		iniFile_.setValue("key5", "val5");
	}

	void dispose()
	{
		const auto filename = "test/test.ini";
		if (File::exists(filename)) {
			File::erase(filename);
		}
	}

	AString readFile() const
	{
		return File("test/test.ini").readAllText();
	}
};
