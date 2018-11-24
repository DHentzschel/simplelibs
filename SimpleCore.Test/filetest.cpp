#include "CppUnitTest.h"
#include "stdafx.h"

#include <chrono>
#include <thread>

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
#pragma warning(disable : 4309)
#pragma warning(disable : 4838)
        const char byteArray[] = { 0xC0, 0xDE, 0xBA, 0x5E, 0x00, 0xC0, 0xFF, 0xEE,
            0x00, 0xF0, 0x0D, 0x00, 0xFE, 0xED, 0x00, 0xFF };
#pragma warning(default : 4309)
#pragma warning(default : 4838)
        byteArray_ = ByteArray(byteArray, 16);
    }

    ~FileTest()
    {
        file_.close();
        file2_.close();
    }

    TEST_METHOD(testOpen)
    {
        /* This file should exists on desktop path*/
        Assert::IsTrue(file_.open(ReadOnly));
    }

    TEST_METHOD(testExists)
    {
        const auto filename2 = Dir::getDesktopDir() + "\\testfile2.txt";
        File file(filename2);
        if (file.exists()) {
            file.erase();
        }

        /* This file should exist */
        Assert::IsTrue(File(Dir::getDesktopDir() + "\\testfile.txt").exists());

        /* This file should NOT exist */
        Assert::IsTrue(!File(filename2).exists());
    }

    TEST_METHOD(testCreate)
    {
        File file(Dir::getDesktopDir() + "\\testfile4.txt");
        if (file.exists()) {
            file.erase();
        }

        /* Test simple file creation */
        Assert::IsTrue(file.create());
        Assert::IsTrue(file.erase());

        /* Test recursive file creation */
        const auto recursiveFilePath = Dir::getDesktopDir() + "\\test_level1\\test_level2\\test_level3\\testfile.txt";
        Assert::IsTrue(File(recursiveFilePath).create(true));
        Assert::IsTrue(File(recursiveFilePath).erase());

        /* Remove folder from recursive creation test for cleanup, true test of functionality is in extra class dirtest */
        Assert::IsTrue(Dir(Dir::getDesktopDir() + "\\test_level1").erase());
    }

    TEST_METHOD(testDelete)
    {
        /* Make sure the file exists */
        File file(Dir::getDesktopDir() + "\\testfile3.txt");
        if (!file.exists()) {
            Assert::IsTrue(file.create());
        }

        /* Test file deletion */
        Assert::IsTrue(file.erase());
    }

    TEST_METHOD(testReadAllText)
    {
        /* The following code won't work: Assert::AreEqual(file_.readAllText(), fileContent)*/
        Assert::IsTrue(file_.readAllText() == exampleFileContent_);
    }

    TEST_METHOD(testWriteAllText)
    {
        File file(Dir::getDesktopDir() + "\\testfile2.txt");
        if (file.exists()) {
            file.erase();
            file.create();
        }

        file.writeAllText(exampleFileContent_);
        Assert::IsTrue(file.readAllText() == exampleFileContent_);
        file.close();
        file.erase();
    }

    TEST_METHOD(testReadAllBytes)
    {
        Assert::IsTrue(file2_.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));
    }

    TEST_METHOD(testWriteAllBytes)
    {
        File file(Dir::getDesktopDir() + "\\testfile2.txt");
        if (file.exists()) {
            file.erase();
            file.create();
        }

        file.writeAllBytes(byteArray_);
        Assert::IsTrue(file.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));
        file.close();
        file.erase();
    }

    TEST_METHOD(testReadLineByLine)
    {
        Assert::IsTrue(file_.open(ReadOnly));

        AString buffer;
        while (!file_.atEnd()) {
            buffer += file_.readLine();
        }

        Assert::IsTrue(AString(exampleFileContent_).removeAll('\n') == buffer);
    }

    TEST_METHOD(testAppend)
    {
        File file(Dir::getDesktopDir() + "\\testfile2.txt");
        if (file.exists()) {
            file.erase();
            file.create();
        }

        Assert::IsTrue(file.open(ReadWrite | Append));
        const AString appendable = "Appendable text";
        file << appendable;
        Assert::IsTrue(appendable == file.readAllText());
        file.close();
        file.erase();
    }

    TEST_METHOD(testGetDirectory)
    {
        const AString directory = "C:/Users/test/";
        const auto* filename = "test.txt";

        /* Testing absolute path. */
        File file(directory + filename);
        Assert::IsTrue(directory.left(directory.size() - 1) == file.getDirectory());

        /* Testing relative path. All relative paths will be concatenated at the end with the sub path of the VS test unit */
        file = File(filename);
        Assert::IsTrue(file.getDirectory().contains("/COMMON7/IDE/EXTENSIONS/TESTPLATFORM", CaseInsensitive));
    }

    TEST_METHOD(testGetFilename)
    {
        const AString filename = "test.txt";
        File file("C:/Users/test/" + filename);
        auto assertFilenameEqualsExpected = [filename](const AString& comparable) {
            Assert::IsTrue(filename == comparable);
        };

        assertFilenameEqualsExpected(file.getFilename());
        file = File(file.getFilename());
        assertFilenameEqualsExpected(file.getFilename());
    }

    TEST_METHOD(testSetFilepath)
    {
        AString filepath = "C:\\Users\\test\\test.txt";

        /* setFilePath() is being invoked in the ctor */
        File file(filepath);
        Assert::IsTrue(filepath.replaceAll("\\", "/") == file.getFilepath());
    }

private:
    File file_;

    File file2_;

    const char* exampleFileContent_ = "This is an example\nfor a text file\n";

    ByteArray byteArray_;

    };
}
