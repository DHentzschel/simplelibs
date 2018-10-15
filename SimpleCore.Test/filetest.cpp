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
        const char byteArray[] = { 0xC0, 0xDE, 0xBA, 0x5E, 0x00, 0xC0, 0xFF, 0xEE, 0x00, 0xF0, 0x0D, 0x00, 0xFE, 0xED, 0x00, 0xFF };
        byteArray_ = ByteArray(byteArray, 16);
    }

    ~FileTest()
    {
        file_.close();
        file2_.close();
    }

    TEST_METHOD_INITIALIZE(setUp)
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
        Assert::IsTrue(File(Dir::getDesktopDir() + "\\testfile.txt").exists());

        /* This file should NOT exist */
        Assert::IsFalse(File(Dir::getDesktopDir() + "\\testfile2.txt").exists());
    }

    TEST_METHOD(testCreate)
    {
        /* Test simple file creation */
        Assert::IsTrue(File(Dir::getDesktopDir() + "\\testfile3.txt").create());

        /* Test recursive file creation */
        const AString recursiveFilePath = Dir::getDesktopDir() + "\\test_level1\\test_level2\\test_level3\\testfile.txt";
        Assert::IsTrue(File(recursiveFilePath).create(true) && File::erase(recursiveFilePath));

        /* Remove folder from recursive creation test for cleanup, true test of functionality is in extra class dirtest */
        Assert::IsTrue(Dir(Dir::getDesktopDir() + "\\test_level1").erase());
    }

    TEST_METHOD(testDelete)
    {
        const AString filepath = Dir::getDesktopDir() + "\\testfile3.txt";

        /* Make sure the file exists */
        File file(filepath);
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
        file.writeAllText(exampleFileContent_);
        Assert::IsTrue(file.readAllText() == exampleFileContent_);
    }

    TEST_METHOD(testReadAllBytes)
    {
        Assert::IsTrue(file2_.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));
    }

    TEST_METHOD(testWriteAllBytes)
    {
        File file(Dir::getDesktopDir() + "\\testfile2.txt");
        file.writeAllBytes(byteArray_);
        Assert::IsTrue(file.readAllBytes().isEqual(byteArray_.data(), byteArray_.size()));
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
    }

    TEST_METHOD(testGetDirectory)
    {
        /* Testing absolute path. */
        const auto* directory = "C:/Users/test";
        File file("C:/Users/test/test.txt");
        Assert::IsTrue(directory == file.getDirectory());

        /* Testing relative path. All relative paths will be concatenated at the end with the sub path of the VS test unit */
        file = File("test.txt");
        Assert::IsTrue(file.getDirectory().contains("\\COMMON7\\IDE\\EXTENSIONS\\TESTPLATFORM", CaseInsensitive));
    }

    TEST_METHOD(testGetFilename)
    {
        File file("C:/Users/test/test.txt");
        Assert::IsTrue(file.getFilename() == "test.txt");

        file = File(file.getFilename());
        Assert::IsTrue(file.getFilename() == "test.txt");
    }

    TEST_METHOD(testSetFilepath)
    {
        File file("");
        file.setFilepath("C:\\Users\\test\\test.txt");
        Assert::IsTrue(file.getFilepath() == "C:/Users/test/test.txt");
    }

private:
    File file_;

    File file2_;

    const char* exampleFileContent_ = "This is an example\nfor a text file";

    ByteArray byteArray_;

    };
}
