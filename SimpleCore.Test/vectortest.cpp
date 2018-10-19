#include "CppUnitTest.h"
#include "stdafx.h"

#include "../SimpleCore/avector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleCoreTest {
    TEST_CLASS(VectorTest) {
public:
    TEST_METHOD_INITIALIZE(setUp)
    {
        vector_ = { 1, 2, 3, 4, 5 };
    }

    TEST_METHOD(testAppend)
    {
        Assert::IsTrue(vector_.size() == 5);
        vector_.append(6);
        Assert::IsTrue(vector_.size() == 6 && vector_[5] == 6);
    }

private:
    AVector<int> vector_;

    };
};