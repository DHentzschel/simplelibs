#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include "astring.h"

class AString;

template class SIMPLECORE_API AVector<AString>;

/**
 * This class is used to improve handling string vectors.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class SIMPLECORE_API StringVector : public AVector<AString> {
public:
	/**
	 * Calls the default constructor.
	 */
	StringVector() = default;

	/**
	 * Copies the value of the specified string vector.
	 *
	 * @param stringVector the string vector to copy from
	 */
	StringVector(const StringVector& stringVector);

	/**
	 * Copies the value of the specified string vector.
	 *
	 * @param stringVector the string vector to copy from
	 */
	StringVector(const AVector<AString>& stringVector);

	/**
	 * Removes any string from the vector that is empty.
	 */
	void removeEmpties();

	/**
	 * Removes any string from the vector that only contains whitespaces.
	 */
	void removeWhitespaces();

	/**
	 * Removes any string from the vector that only contains escape characters.
	 */
	void removeEscapes();
};

#endif // STRINGVECTOR_H
