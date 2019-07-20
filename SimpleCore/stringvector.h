#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include "astring.h"

class AString;

/**
 * This class is used to improve handling string vectors.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class StringVector : public AVector<AString> {
public:
	/**
	 * Calls the default constructor.
	 */
	SIMPLECORE_API StringVector() = default;

	/**
	 * Copies the value of the specified string vector.
	 *
	 * @param stringVector the string vector to copy from
	 */
	SIMPLECORE_API StringVector(const StringVector& stringVector);

	/**
	 * Copies the value of the specified string vector.
	 *
	 * @param stringVector the string vector to copy from
	 */
	SIMPLECORE_API StringVector(const AVector<AString>& stringVector);

	/**
	 * Removes any string from the vector that is empty.
	 */
	SIMPLECORE_API void removeEmpties();

	/**
	 * Removes any string from the vector that only contains whitespaces.
	 */
	SIMPLECORE_API void removeWhitespaces();

	/**
	 * Removes any string from the vector that only contains escape characters.
	 */
	SIMPLECORE_API void removeEscapes();
};

#endif // STRINGVECTOR_H
