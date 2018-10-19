#include "bytearray.h"

ByteArray::ByteArray()
{}

ByteArray::ByteArray(const char* byteArray, size_t size)
{
    reserve(size);
    for (uint i = 0; i < size; ++i) {
        *this += byteArray[i];
    }
}

ByteArray::ByteArray(const AVector<char> & vector) : AVector<char>(vector)
{}

ByteArray::~ByteArray()
{}

bool ByteArray::isEqual(const char* byteArray, size_t size)
{
    if (this->size() != size) {
        return false;
    }

    for (uint i = 0; i < size; ++i) {
        if (byteArray[i] != (*this)[i]) {
            return false;
        }
    }

    return true;
}

ByteArray& ByteArray::operator+=(const char character)
{
    insert(end(), character);
    return *this;
}


ByteArray& ByteArray::operator+=(const ByteArray& right)
{
    insert(end(), right.begin(), right.end());
    return *this;
}
