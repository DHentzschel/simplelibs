#include "bytearray.h"

ByteArray::ByteArray()
{}

ByteArray::ByteArray(const AVector<char> & vector) : AVector<char>(vector)
{}

ByteArray::~ByteArray()
{}

ByteArray& ByteArray::operator+=(const ByteArray& right)
{
    insert(end(), right.begin(), right.end());
    return *this;
}
