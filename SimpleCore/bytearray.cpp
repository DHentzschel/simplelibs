#include "bytearray.h"

ByteArray::ByteArray(const char* charArray, size_t size)
{
	reserve(size);
	for (uint i = 0; i < size; ++i) {
		*this += charArray[i];
	}
}

ByteArray::ByteArray(const ByteArray& byteArray) :
	AVector<char>(byteArray)
{
}

ByteArray::ByteArray(const AVector<char>& vector) :
	AVector<char>(vector)
{}

bool ByteArray::isEqual(const char* charArray, size_t size)
{
	if (this->size() != size) {
		return false;
	}

	for (uint i = 0; i < size; ++i) {
		if (charArray[i] != (*this)[i]) {
			return false;
		}
	}

	return true;
}

ByteArray& ByteArray::operator+=(const char right)
{
	insert(end(), right);
	return *this;
}

ByteArray& ByteArray::operator+=(const ByteArray& right)
{
	insert(end(), right.begin(), right.end());
	return *this;
}
