#ifndef PSQLVARPARAM_H
#define PSQLVARPARAM_H

#include <astring.h>
#include <variant>

typedef std::variant<bool,
	char,
	byte,
	short,
	ushort,
	int,
	uint,
	int64,
	uint64,
	float,
	double,
	const char*,
	AString>
	SqlVariantParam;

#endif // PSQLVARPARAM_H
