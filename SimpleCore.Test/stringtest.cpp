#include <logger.h>
#include <astring.h>
#include <stringvector.h>

class StringTest {
public:
	TEST_ALL_METHODS(testAll)
	{
		Logger::logTestInit("StringTest");
		init();

		int result = 0;
		result += Logger::logTestResult(testArg());
		result += Logger::logTestResult(testLeft());
		result += Logger::logTestResult(testRight());
		result += Logger::logTestResult(testAppend());
		result += Logger::logTestResult(testFill());
		result += Logger::logTestResult(testPrepend());
		result += Logger::logTestResult(testRemoveAll());
		result += Logger::logTestResult(testRemoveFirst());
		result += Logger::logTestResult(testRepeat());
		result += Logger::logTestResult(testReplaceAll());
		result += Logger::logTestResult(testReplaceFirst());
		result += Logger::logTestResult(testToLower());
		result += Logger::logTestResult(testToUpper());
		result += Logger::logTestResult(testTrim());
		result += Logger::logTestResult(testSplit());
		result += Logger::logTestResult(testSplitByNonNumerics());
		result += Logger::logTestResult(testSplitByNumerics());
		result += Logger::logTestResult(testToByteArray());
		result += Logger::logTestResult(testContains());
		result += Logger::logTestResult(testEquals());
		return result;
	}

	TEST_METHOD(testArg)
	{
		Logger::logTestBegin("testArg");

		String temp = "%1 %2 %1 %2 %3 %5";
		const auto replaced = temp.arg("hello").arg("test").arg("this");
		ASSERT_EQUALS("hello test hello test this %5", replaced);

		TEST_FINISH;
	}

	TEST_METHOD(testLeft)
	{
		Logger::logTestBegin("testLeft");

		String temp = "This is a test string";
		String left = temp.left(14);
		ASSERT_EQUALS("This is a test", left);

		temp.clear();
		left = temp.left(14);
		ASSERT_TRUE(left.isEmpty());

		TEST_FINISH;
	}

	TEST_METHOD(testRight)
	{
		Logger::logTestBegin("testRight");

		String temp = "This is a test string";
		String right = temp.right(11);
		ASSERT_EQUALS("test string", right);

		temp.clear();
		right = temp.right(11);
		ASSERT_TRUE(right.isEmpty());

		TEST_FINISH;
	}

	TEST_METHOD(testAppend)
	{
		Logger::logTestBegin("testAppend");

		const String temp = "This is a test";
		String tempCopy = "This is a";
		tempCopy.append(" test");
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy.clear();
		tempCopy.append(temp);
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy = temp;
		tempCopy.append("");
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy.clear();
		tempCopy.append('A');
		ASSERT_EQUALS("A", tempCopy);
		
		TEST_FINISH;
	}

	TEST_METHOD(testFill)
	{
		Logger::logTestBegin("testAppend");

		const String temp = "This is a test";
		String tempCopy = temp;
		tempCopy.fill('a', 4);
		ASSERT_EQUALS("aaaa is a test", tempCopy);

		tempCopy = temp;
		tempCopy.fill('a');
		ASSERT_EQUALS("aaaaaaaaaaaaaa", tempCopy);

		TEST_FINISH;
	}

	TEST_METHOD(testPrepend)
	{
		Logger::logTestBegin("testPrepend");

		const String temp = "This is a test";
		String tempCopy = "is a test";
		tempCopy.prepend("This ");
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy.clear();
		tempCopy.prepend(temp);
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy = temp;
		tempCopy.prepend("");
		ASSERT_EQUALS(temp, tempCopy);

		tempCopy.clear();
		tempCopy.prepend('A');
		ASSERT_EQUALS("A", tempCopy);
		
		TEST_FINISH;
	}

	TEST_METHOD(testRemoveAll)
	{
		Logger::logTestBegin("testRemoveAll");

		const String temp = "This is a test";
		String tempCopy = temp;
		tempCopy.removeAll("is");
		ASSERT_EQUALS("Th  a test", tempCopy);

		tempCopy = "ThIs iS a test";
		tempCopy.removeAll("is", false);
		ASSERT_EQUALS("Th  a test", tempCopy);

		tempCopy = "ThIs iS a test";
		tempCopy.removeAll("is");
		ASSERT_EQUALS("ThIs iS a test", tempCopy);

		tempCopy.clear();
		tempCopy.removeAll("is");
		ASSERT_TRUE(tempCopy.isEmpty());

		tempCopy = temp;
		tempCopy.removeAll("xyz");
		ASSERT_EQUALS(temp, tempCopy);

		/* Test removeAll(char) */
		tempCopy = "This is a test";
		tempCopy.removeAll('i');
		ASSERT_EQUALS("Ths s a test", tempCopy);

		tempCopy = "ThIs is a test";
		tempCopy.removeAll('i', false);
		ASSERT_EQUALS("Ths s a test", tempCopy);

		tempCopy = "ThIs is a test";
		tempCopy.removeAll('i');
		ASSERT_EQUALS("ThIs s a test", tempCopy);

		tempCopy.clear();
		tempCopy.removeAll('i');
		ASSERT_TRUE(tempCopy.isEmpty());

		tempCopy = temp;
		tempCopy.removeAll('z');
		ASSERT_EQUALS(temp, tempCopy);

		TEST_FINISH;
	}

	TEST_METHOD(testRemoveFirst)
	{
		Logger::logTestBegin("testRemoveFirst");

		String temp = "This is a test";

		auto tempCopy = temp;
		tempCopy.removeFirst("is");
		ASSERT_EQUALS("Th is a test", tempCopy);

		tempCopy = "ThIs iS a test";
		tempCopy.removeFirst("is", false);
		ASSERT_EQUALS("Th iS a test", tempCopy);

		tempCopy = "ThIs iS a test";
		tempCopy.removeFirst("is");
		ASSERT_EQUALS("ThIs iS a test", tempCopy);

		tempCopy.clear();
		tempCopy.removeFirst("is");
		ASSERT_TRUE(tempCopy.isEmpty());

		tempCopy = temp;
		tempCopy.removeFirst('i');
		ASSERT_EQUALS("Ths is a test", tempCopy);

		tempCopy = "ThIs is a test";
		tempCopy.removeFirst('i', false);
		ASSERT_EQUALS("Ths is a test", tempCopy);

		tempCopy = "ThIs is a test";
		tempCopy.removeFirst('i');
		ASSERT_EQUALS("ThIs s a test", tempCopy);

		tempCopy.clear();
		tempCopy.removeFirst('i');
		ASSERT_TRUE(tempCopy.isEmpty());

		TEST_FINISH;
	}

	TEST_METHOD(testRepeat)
	{
		Logger::logTestBegin("testRepeat");

		const String temp = "Hello, this is a test";
		auto copyTemp = temp;
		auto copyTemp2 = temp;

		const int n = 10;
		for (int i = 0; i < n; ++i) {
			copyTemp += temp;
		}

		copyTemp2.repeat(n);
		ASSERT_EQUALS(copyTemp, copyTemp2);

		copyTemp2 = temp;
		copyTemp2.repeat(0);
		ASSERT_TRUE(copyTemp2.isEmpty());

		TEST_FINISH;
	}

	TEST_METHOD(testReplaceAll)
	{
		Logger::logTestBegin("testReplaceAll");

		const String temp = "This is is a test";

		auto copyTemp = temp;
		copyTemp.replaceAll("t", "a");
		ASSERT_EQUALS("This is is a aesa", copyTemp);

		copyTemp = temp;
		copyTemp.replaceAll("is", "");
		ASSERT_EQUALS("Th   a test", copyTemp);

		copyTemp = temp;
		copyTemp.replaceAll("t", "a", false);
		ASSERT_EQUALS("ahis is is a aesa", copyTemp);

		copyTemp = temp;
		copyTemp.replaceAll("", "", false);
		ASSERT_EQUALS(temp, copyTemp);

		TEST_FINISH;
	}
	
	TEST_METHOD(testReplaceFirst)
	{
		Logger::logTestBegin("testReplaceFirst");

		const String temp = "This is a test";

		auto copyTemp = temp;
		copyTemp.replaceFirst("t", "a");
		ASSERT_EQUALS("This is a aest", copyTemp);

		copyTemp = temp;
		copyTemp.replaceFirst("is", "");
		ASSERT_EQUALS("Th is a test", copyTemp);

		copyTemp = temp;
		copyTemp.replaceFirst("t", "a", false);
		ASSERT_EQUALS("ahis is a test", copyTemp);

		copyTemp = temp;
		copyTemp.replaceFirst("", "", false);
		ASSERT_EQUALS(temp, copyTemp);

		TEST_FINISH;
	}

	TEST_METHOD(testToLower)
	{
		Logger::logTestBegin("testToLower");
		
		const String temp = "AbCdEfGhIjKlMnOpQrStUvWxYz0123456789ÄöÜß";
		auto tempCopy = temp;
		tempCopy.toLower();
		ASSERT_EQUALS("abcdefghijklmnopqrstuvwxyz0123456789äöüß", tempCopy);

		TEST_FINISH;
	}

	TEST_METHOD(testToUpper)
	{
		Logger::logTestBegin("testToUpper");

		const String temp = "AbCdEfGhIjKlMnOpQrStUvWxYz0123456789ÄöÜß";
		auto tempCopy = temp;
		tempCopy.toUpper();
		ASSERT_EQUALS("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ÄÖÜß", tempCopy);

		TEST_FINISH;
	}

	TEST_METHOD(testTrim)
	{
		Logger::logTestBegin("testTrim");

		const String expected = "test";

		String temp = "\t\n\v\f\r test\t\n\v\f\r ";
		temp.trim();
		ASSERT_EQUALS(expected, temp);

		temp = "test \t\n\v\f\r";
		temp.trim();
		ASSERT_EQUALS(expected, temp);

		temp = " \t\n\v\f\rtest";
		temp.trim();
		ASSERT_EQUALS(expected, temp);

		temp = "test";
		temp.trim();
		ASSERT_EQUALS(expected, temp);

		TEST_FINISH;
	}

	TEST_METHOD(testSplit)
	{
		Logger::logTestBegin("testSplit");

		StringVector expected({ "this", "is", "a", "test" });
		String temp = "this is a test";
		auto splitted = temp.split(' ');
		ASSERT_EQUALS(expected, splitted);

		/* Test AString::split(char) */
		expected = StringVector({ "This", "Is", "A", "Test" });
		temp = "This Is A Test";
		splitted = temp.split(' ');
		ASSERT_EQUALS(expected, splitted);

		/* Test AString::split(AString) */
		expected = StringVector({ "user", "passphrase", "just a test" });
		temp = "user;;passphrase;;just a test";
		splitted = temp.split(";;");
		ASSERT_EQUALS(expected, splitted);

		TEST_FINISH;
	}

	TEST_METHOD(testSplitByNonNumerics)
	{
		Logger::logTestBegin("testSplitByNonNumerics");

		StringVector expected({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" });
		String temp = "1a2b3c4d5e6f7g8h9i0";
		auto splitted = temp.splitByNonNumerics();
		ASSERT_EQUALS(expected, splitted);

		TEST_FINISH;
	}

	TEST_METHOD(testSplitByNumerics)
	{
		Logger::logTestBegin("testSplitByNumerics");

		StringVector expected({ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" });
		String temp = "1a2b3c4d5e6f7g8h9i0j";
		auto splitted = temp.splitByNumerics();
		ASSERT_EQUALS(expected, splitted);

		TEST_FINISH;
	}

	TEST_METHOD(testToByteArray)
	{
		Logger::logTestBegin("testToByteArray");
		
		String temp = "Hello world!";
		ByteArray expected(temp.toCString(), temp.size());
		ASSERT_EQUALS(expected, temp.toByteArray());

		TEST_FINISH;
	}

	TEST_METHOD(testContains)
	{
		Logger::logTestBegin("testContains");

		String temp = "this is a test";
		/* Test AString::contains(const AString&) */
		ASSERT_TRUE(temp.contains("test"));
		ASSERT_FALSE(temp.contains("tesz"));
		ASSERT_TRUE(temp.contains("test", false));
		ASSERT_FALSE(temp.contains("Test"));
		ASSERT_TRUE(temp.contains("Test", false));
		
		/* Test AString::contains(char) */
		ASSERT_TRUE(temp.contains('a'));
		ASSERT_FALSE(temp.contains('z'));

		TEST_FINISH;
	}

	TEST_METHOD(testEndsWith)
	{
		Logger::logTestBegin("testEndsWith");

		String temp = "Hello World!";
		ASSERT_TRUE(temp.endsWith("World!"));
		ASSERT_TRUE(temp.endsWith("World!", false));
		ASSERT_FALSE(temp.endsWith("world!"));
		ASSERT_TRUE(temp.endsWith("world!", false));
		ASSERT_FALSE(temp.endsWith("Worldz"));

		TEST_FINISH;
	}
	
	TEST_METHOD(testEquals)
	{
		Logger::logTestBegin("testEquals");

		auto testEquals = [](String& temp, String& temp2) {
			auto result = false;
			if (&temp == &temp2) {
				result = true;
			}
			else if (temp.size() != temp2.size()) {
				result = false;
			}

			for (auto it = temp.begin(), it2 = temp2.begin(); it != temp.end() && it2 != temp2.end(); ++it, ++it2) {
				if (*it != *it2) {
					result = false;
					break;
				}
			}
			result = true;
			ASSERT_EQUALS(result, temp.equals(temp2));
		};

		String temp = "Hello World!";
		String temp2 = "";
		testEquals(temp, temp2);

		temp2 = "Hello World!";
		testEquals(temp, temp2);
		
		temp2 = "Hello Worldz";
		testEquals(temp, temp2);		
		
		TEST_FINISH;
	}

private:
	void init()
	{
		String::setLocaleGermany();
	}

};
