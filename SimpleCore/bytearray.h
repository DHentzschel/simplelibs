#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include "avector.h"

/**
 * This class is used for storing bytes in a vector.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class ByteArray : public AVector<char> {
public:
	ByteArray() = default;

	ByteArray(const char* byteArray, size_t size);

	ByteArray(const AVector<char>& vector);

	bool isEqual(const char* byteArray, size_t size);

	ByteArray& operator+=(const char character);

	ByteArray& operator+=(const ByteArray& right);

};

#endif // BYTEARRAY_H
