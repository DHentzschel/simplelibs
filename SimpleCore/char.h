#ifndef CHAR_H
#define CHAR_H

#include "simplecore.h"

/**
 * These functions are used as auxiliary functions for characters.
 *
 * @author Daniel Hentzschel on 12.05.2019.
 */
namespace Char {
	/**
	 * Returns whether the character passed as parameter is a whitespace character.
	 *
	 * @param character the char to check
	 * @return whether character is a whitespace character
	 */
	inline bool isWhitespace(char character)
	{
		return character == '\t' || character == '\r' || character == '\n' || character == ' ' || character == '\f' || character == '\v';
	}

	/**
	 * Returns the character passed as parameter converted to lowercase.
	 *
	 * @param character the char to convert
	 * @return the character converted to lowercase
	 */
	inline char toLower(char character)
	{
		return character | 0x20;
	}

	/**
	 * Returns the character passed as parameter converted to uppercase.
	 *
	 * @param character the char to convert
	 * @return the character converted to uppercase
	 */
	inline char toUpper(char character)
	{
		return character & ~0x20;
	}
};

#endif // !CHAR_H
