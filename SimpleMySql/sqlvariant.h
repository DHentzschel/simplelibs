#ifndef SQLVARIANT_H
#define SQLVARIANT_H

#include <astring.h>

class SqlVariant {
public:
	explicit SqlVariant(void* data, bool useCasts = false, bool fromString = false);

	bool isValid() const;

	bool toBool() const;

	char toChar() const;

	byte toByte() const;

	short toShort() const;

	ushort toUShort() const;

	int toInt() const;

	uint toUInt() const;

	int64 toInt64() const;

	uint64 toUInt64() const;

	float toFloat() const;

	double toDouble() const;

	const char* toCString() const;

	AString toString() const;

private:
    bool useCasts_;

    bool fromString_;

    void* data_;
};

#endif // SQLVARIANT_H
