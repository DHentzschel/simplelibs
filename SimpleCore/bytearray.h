#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include "avector.h"

class ByteArray : public AVector<char> {
public:
    ByteArray();

    ByteArray(const char* byteArray, size_t size);

    ByteArray(const AVector<char>& vector);

    ~ByteArray();

    bool isEqual(const char* byteArray, size_t size);

    ByteArray& operator+=(const char character);

    ByteArray& operator+=(const ByteArray& right);

};

#endif // BYTEARRAY_H
