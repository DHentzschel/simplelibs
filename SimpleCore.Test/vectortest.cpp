#include "CppUnitTest.h"
#include "stdafx.h"

#include "../SimpleCore/alist.h"
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
        vector_.append(6);
        Assert::IsTrue(vector_.size() == 6);

        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 1);
        }
    }

    TEST_METHOD(testPrepend)
    {
        vector_.prepend(0);
        Assert::IsTrue(vector_.size() == 6);

        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i);
        }
    }

    TEST_METHOD(testStartsWith)
    {
        Assert::IsTrue(vector_.startsWith(1));
        Assert::IsFalse(vector_.startsWith(2));
    }

    TEST_METHOD(testEndsWith)
    {
        Assert::IsTrue(vector_.endsWith(5));
        Assert::IsFalse(vector_.endsWith(6));
    }

    TEST_METHOD(testIsEmpty)
    {
        Assert::IsFalse(vector_.isEmpty());
    }

    TEST_METHOD(testContains)
    {
        byte i;
        for (i = 1; i < 6; ++i) {
            Assert::IsTrue(vector_.contains(i));
        }
        Assert::IsFalse(vector_.contains(i));
    }

    TEST_METHOD(testCount)
    {
        vector_.clear();

        const byte count = 100;
        vector_.reserve(count * 3);

        for (byte i = 0; i < count; ++i) {
            vector_.append(i);
            vector_.append(i);
            vector_.append(i);
        }

        for (ushort i = 0; i < vector_.size(); i += 3) {
            Assert::IsTrue(vector_.count(i % 100) == 3);
        }
    }

    TEST_METHOD(testFirstIndexOf)
    {
        vector_.assign({ 3, 2, 1, 3, 3, 2 });

        for (byte i = 3; i > 0; --i) {
            Assert::IsTrue(vector_.firstIndexOf(i) == 3 - i);
        }
    }

    TEST_METHOD(testLastIndexOf)
    {
        vector_.assign({ 2, 3, 3, 1, 2, 3 });

        for (byte i = 3; i > 0; --i) {
            Assert::IsTrue(vector_.lastIndexOf(i) == 2 + i);
        }
    }

    TEST_METHOD(testReplace)
    {
        vector_.replace(2, 4);
        Assert::IsTrue(vector_[2] == 4);
    }

    TEST_METHOD(testRemoveAt)
    {
        vector_.removeAt(0);
        Assert::IsTrue(vector_.size() == 4);
        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 2);
        }
    }

    TEST_METHOD(testRemoveFirst)
    {
        vector_.removeFirst();
        Assert::IsTrue(vector_.size() == 4);
        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 2);
        }
    }

    TEST_METHOD(testRemoveDuplicates)
    {
        vector_.clear();

        const byte count = 100;
        vector_.reserve(count * 3);
        for (byte i = 0; i < count; ++i) {
            vector_.append(i);
            vector_.append(i);
            vector_.append(i);
        }

        vector_.removeDuplicates();
        Assert::IsTrue(vector_.size() == count);

        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i);
        }
    }

    TEST_METHOD(testRemoveLast)
    {
        vector_.clear();

        const byte count = 100;
        vector_.reserve(1 + count * 3);

        for (byte i = 0; i < count; ++i) {
            vector_.append(i);
            vector_.append(i);
            vector_.append(i);
        }

        vector_.append(1234);
        vector_.removeLast();

        Assert::IsTrue(vector_.size() == count * 3);

        for (ushort i = 0, j = 0; i < vector_.size(); i += 3, ++j) {
            Assert::IsTrue(vector_[i] == j);
            Assert::IsTrue(vector_[i + 1] == j);
            Assert::IsTrue(vector_[i + 2] == j);
        }
    }

    TEST_METHOD(testRemoveFirstValue)
    {
        vector_.clear();

        const byte count = 100;
        vector_.reserve(1 + count * 3);

        for (byte i = 0; i < count; ++i) {
            vector_.append(i);
            vector_.append(i);
            vector_.append(i);
        }

        vector_.prepend(1234);
        vector_.removeFirst(1234);

        Assert::IsTrue(vector_.size() == count * 3);

        for (ushort i = 0, j = 0; i < vector_.size(); i += 3, ++j) {
            Assert::IsTrue(vector_[i] == j);
            Assert::IsTrue(vector_[i + 1] == j);
            Assert::IsTrue(vector_[i + 2] == j);
        }

    }

    TEST_METHOD(testRemoveAll)
    {
        vector_.clear();

        const byte count = 100;
        vector_.reserve(count * 3);

        for (byte i = 0; i < count; ++i) {
            vector_.append(i);
            vector_.append(i);
            vector_.append(i);
        }

        vector_.removeAll(44);

        for (ushort i = 0; i < 100; ++i) {
            if (i == 44) {
                Assert::IsFalse(vector_.contains(i));
            }
            else {
                Assert::IsTrue(vector_.contains(i));
            }
        }
    }

    TEST_METHOD(testMid)
    {
        auto midVector = vector_.mid(2);
        Assert::IsTrue(midVector.size() == (vector_.size() - 2));

        for (byte i = 2; i < vector_.size(); ++i) {
            Assert::IsTrue(i == vector_[i - 1]);
        }
    }

    TEST_METHOD(testMove)
    {
        vector_.move(0, 4);
        Assert::IsTrue(vector_[0] == 5);
        Assert::IsTrue(vector_[4] == 1);
    }

    TEST_METHOD(testFirst)
    {
        const auto first = vector_.first();
        Assert::IsTrue(first == vector_[0]);
    }

    TEST_METHOD(testLast)
    {
        const auto last = vector_.last();
        Assert::IsTrue(last == vector_[vector_.size() - 1]);
    }

    TEST_METHOD(testTakeAt)
    {
        const auto value = vector_.takeAt(2);
        Assert::IsTrue(vector_.size() == 4);
        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 1 + (i >= 2 ? 1 : 0));
        }
        Assert::IsTrue(value == 3);
    }

    TEST_METHOD(testTakeFirst)
    {
        const auto value = vector_.takeFirst();
        Assert::IsTrue(vector_.size() == 4);
        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 2);
        }
        Assert::IsTrue(value == 1);
    }

    TEST_METHOD(testTakeLast)
    {
        const auto value = vector_.takeLast();
        Assert::IsTrue(vector_.size() == 4);
        for (byte i = 0; i < vector_.size(); ++i) {
            Assert::IsTrue(vector_[i] == i + 1);
        }
        Assert::IsTrue(value == 5);
    }

    TEST_METHOD(testToList)
    {
        auto list = vector_.toList();
        Assert::IsTrue(list.size() == vector_.size());

        auto i = 0;
        for (auto it = list.begin(); it != list.end(); ++it, ++i) {
            Assert::IsTrue(*it == vector_[i]);
        }
    }

private:
    Vector<int> vector_;

    };
};