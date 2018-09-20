#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include "avector.h"

class ByteArray : public AVector<char> {
public:
    ByteArray();

    ByteArray(const AVector<char>& vector);

    ~ByteArray();

    ByteArray& operator+=(const ByteArray& right);

};

#endif // BYTEARRAY_H
