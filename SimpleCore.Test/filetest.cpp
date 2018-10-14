#include "CppUnitTest.h"
#include "stdafx.h"

#include "../SimpleCore/file.h"
#include "../SimpleCore/dir.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleCoreTest {
    TEST_CLASS(FileTest) {
public:
    FileTest() :
        file_(Dir::getDesktopDir() + "\\testfile.txt"),
        file2_(Dir::getDesktopDir() + "\\testfile2.bin")
    {
    }

    TEST_METHOD_INITIALIZE(beforeEachTest)
    {
    }

    TEST_METHOD(testOpen)
    {
        /* This file should exists on desktop path*/
        Assert::IsTrue(file_.open(ReadOnly));
    }

    TEST_METHOD(testExists)
    {
        /* This file should exist */
        Assert::IsTrue(File::exists(Dir::getDesktopDir() + "\\testfile.txt"));

        /* This file should NOT exist */
        Assert::IsFalse(File::exists(Dir::getDesktopDir() + "\\testfile2.txt"));
    }

    TEST_METHOD(testCreate)
    {
        /* Test simple file creation */
        Assert::IsTrue(File::create(Dir::getDesktopDir() + "\\testfile3.txt"));

        /* Test recursive file creation */
        const AString recursiveFilePath = Dir::getDesktopDir() + "\\test_level1\\test_level2\\test_level3\\testfile.txt";
        Assert::IsTrue(File::create(recursiveFilePath, true && File::erase(recursiveFilePath)));

        /* Remove folder from recursive creation test for cleanup, true test of functionality is in extra class dirtest */
        Assert::IsTrue(Dir::erase(Dir::getDesktopDir() + "\\test_level1"));
    }

    TEST_METHOD(testDelete)
    {
        const AString filepath = Dir::getDesktopDir() + "\\testfile3.txt";

        /* Make sure the file exists */
        if (!File::exists(filepath)) {
            Assert::IsTrue(File::create(filepath));
        }

        /* Test file deletion */
        Assert::IsTrue(File::erase(Dir::getDesktopDir() + "\\testfile3.txt"));
    }

    TEST_METHOD(testReadAllText)
    {
        const AString fileContent = "This is an example\nfor a text file";
        /* The following code won't work: Assert::AreEqual(file_.readAllText(), fileContent)*/
        Assert::IsTrue(file_.readAllText() == fileContent);
    }

    TEST_METHOD(testReadAllBytes)
    {
        const char byteArray[]{ 0xC0, 0xDE, 0xBA, 0x5E, 0x00, 0xC0, 0xFF, 0xEE, 0x00, 0xF0, 0x0D, 0x00, 0xFE, 0xED, 0x00, 0xFF };
        Assert::IsTrue(ByteArray(file2_.readAllBytes()).isEqual(byteArray, 16));
    }

    TEST_METHOD(testReadLineByLine)
    {
        Assert::IsTrue(file_.open(ReadOnly));

        const AString fileContent = "This is an examplefor a text file";
        AString buffer;

        while (!file_.atEnd()) {
            buffer += file_.readLine();
        }

        Assert::IsTrue(fileContent == buffer);
    }

private:
    File file_;

    File file2_;

    };
}
