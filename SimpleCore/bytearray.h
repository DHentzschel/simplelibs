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
	/**
	* Calls the default initialization.
	*/
	ByteArray() = default;

	/**
	 * Initializes the byte array by a char array and its size.
	 *
	 * @param charArray the char array to copy from
	 * @param size the size of the char array
	 */
	ByteArray(const char* charArray, size_t size);

	/**
	 * Initializes the byte array by the given char vector passed as parameter.
	 *
	 * @param vector the char vector to copy from
	 */
	ByteArray(const AVector<char>& vector);

	/**
	 * Returns whether the char array passed as parameter is equal to the
	 * data saved in the current ByteArray instance.
	 *
	 * @param charArray the byte array to compare
	 * @param size the size of the byte array to compare
	 * @return whether the passed char array is equal to the data in the current ByteArray instance
	 */
	bool isEqual(const char* charArray, size_t size);

	/**
	 * Appends the char passed as parameter to the current ByteArray instance.
	 *
	 * @param right the char to append
	 * @return the reference to the current ByteArray instance
	 */
	ByteArray& operator+=(const char right);

	/**
	 * Appends the data of the ByteArray passed as parameter to the current ByteArray instance.
	 *
	 * @param right the ByteArray to copy the data from
	 * @return the reference to the current ByteArray instance
	 */
	ByteArray& operator+=(const ByteArray& right);
};

#endif // BYTEARRAY_H
