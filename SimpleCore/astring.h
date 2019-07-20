#ifndef ASTRING_H
#define ASTRING_H

#include <string>
#include <variant>

#include "functions.h"

#include "bytearray.h"
#include "stringvector.h"

class StringVector;

/**
 * This class extends the std::string class by auxiliary functions.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class AString : public std::string {
public:
	using std::string::string;

	/**
	 * Calls the default constructor.
	 */
	SIMPLECORE_API AString() = default;

	/**
	 * Copies the value from the specified string.
	 *
	 * @param string the string to copy from
	 */
	SIMPLECORE_API AString(const AString& string);

	/**
	 * Copies the value from the specified std::string.
	 *
	 * @param string the string to copy from
	 */
	SIMPLECORE_API AString(const std::string& string);

	/**
	 * Copies the value from the specified char array.
	 *
	 * @param string the char array to copy from
	 */
	SIMPLECORE_API AString(const char* string);

	/**
	 * Replaces the next placeholder (%number) by the specified string.
	 *
	 * @param value the string to copy from
	 * @return the replaced string
	 */
	SIMPLECORE_API AString arg(const AString& value);

	/**
	 * Returns the left side of the string starting at index 0 ending at index n as new string.
	 *
	 * @param n the length of the substring
	 * @return the left side of the string
	 */
	SIMPLECORE_API AString left(size_t n) const;

	/**
	 * Returns the right side of the string starting at index n ending at index size-1 as new string.
	 *
	 * @param n the length of the substring
	 * @return the right side of the string
	 */
	SIMPLECORE_API AString right(size_t n) const;

	/**
	 * Appends the specified char to the string and returns the reference to the current instance.
	 *
	 * @param c the char to append
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& append(char c);

	/**
	 * Appends the specified string to the string and returns the reference to the current instance.
	 *
	 * @param string the string to append
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& append(const AString& string);

	/**
	 * Fills the string with the specified char from index 0 up to index size-1.
	 * If the size is -1 (default), each char of the string will be replaced by the specified char.
	 * If the size is not -1, the string will be cleared and filled with the specified char size times.
	 *
	 * @param c the char to set
	 * @param size the size of the string to fill
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& fill(char c, size_t size = -1);

	/**
	 * Prepends the specified char to the string and returns the reference to the current instance.
	 *
	 * @param c the char to prepend
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& prepend(char c);

	/**
	 * Prepends the specified string to the string and returns the reference to the current instance.
	 *
	 * @param string the string to prepend
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& prepend(const AString& string);

	/**
	 * Removes all occurrences that are equal to the specified char.
	 * If caseSensitive is true (default), the char will be searched case sensitive.
	 *
	 * @param c the char to remove
	 * @param caseSensitive whether the char should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& removeAll(char c, bool caseSensitive = true);

	/**
	 * Removes all occurrences that are equal to the specified string.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to remove
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& removeAll(const AString& string, bool caseSensitive = true);

	/**
	 * Removes the first occurrence that is equal to the specified char.
	 * If caseSensitive is true (default), the char will be searched case sensitive.
	 *
	 * @param c the char to remove
	 * @param caseSensitive whether the char should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& removeFirst(char c, bool caseSensitive = true);

	/**
	 * Removes the first occurrence that is equal to the specified string.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to remove
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& removeFirst(const AString& string, bool caseSensitive = true);

	/**
	 * Appends the current string to the current instance "times" times.
	 * If "times" is less than 1, the string will be cleared.
	 *
	 * @param times the count to repeat
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& repeat(int times);

	/**
	 * Replaces all occurrences that are equal to "from" by "to".
	 * If caseSensitive is true (default), the string "from" will be searched case sensitive.
	 *
	 * @param from the string to replace
	 * @param to the new value
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& replaceAll(const AString& from, const AString& to, bool caseSensitive = true);

	/**
	 * Replaces the first occurrence that is equal to "from" by "to".
	 * If caseSensitive is true (default), the string "from" will be searched case sensitive.
	 *
	 * @param from the string to replace
	 * @param to the new value
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& replaceFirst(const AString& from, const AString& to, bool caseSensitive = true);

	/**
	 * Converts the current string to lowercase and returns the reference to the current instance.
	 *
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& toLower();

	/**
	 * Converts the current string to uppercase and returns the reference to the current instance.
	 *
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& toUpper();

	/**
	 * Removes all trailing whitespaces and returns the reference to the current instance.
	 *
	 * @return the reference to the current instance
	 */
	SIMPLECORE_API AString& trim();

	/**
	 * Splits the current string by the specified separator and returns a new string vector.
	 * If caseSensitive is true (default), the separator will be searched case sensitive.
	 *
	 * @param separator the char to split by
	 * @param caseSensitive whether the char should be searched case sensitive or not
	 * @return the new string vector containing the split result of the string
	 */
	SIMPLECORE_API StringVector split(char separator, bool caseSensitive = true) const;

	/**
	 * Splits the current string by the specified separator and returns a new string vector.
	 * If caseSensitive is true (default), the separator will be searched case sensitive.
	 *
	 * @param separator the string to split by
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return the new string vector containing the split result of the string
	 */
	SIMPLECORE_API StringVector split(const AString& separator, bool caseSensitive = true) const;

	/**
	 * Splits the current string by non numeric chars and returns a new string vector.
	 *
	 * @return the new string vector containing the split result of the string
	 */
	SIMPLECORE_API StringVector splitByNonNumerics() const;

	/**
	 * Splits the current string by numeric chars and returns a new string vector.
	 *
	 * @return the new string vector containing the split result of the string
	 */
	SIMPLECORE_API StringVector splitByNumerics() const;

	/**
	 * Converts the current string to a byte array and returns it.
	 *
	 * @return the current string converted to a new byte array
	 */
	SIMPLECORE_API ByteArray toByteArray() const;

	/**
	 * Returns whether the string contains the specified char.
	 * If caseSensitive is true (default), the separator will be searched case sensitive.
	 *
	 * @param c the char to find
	 * @param caseSensitive whether the char should be searched case sensitive or not
	 * @return whether the current string contains the specified char
	 */
	SIMPLECORE_API bool contains(char c, bool caseSensitive = true) const;

	/**
	 * Returns whether the string contains the specified string.
	 * If caseSensitive is true (default), the separator will be searched case sensitive.
	 *
	 * @param string the string to find
	 * @param caseSensitive whether the string should be searched case sensitive or not
	 * @return whether the current string contains the specified string
	 */
	SIMPLECORE_API bool contains(const AString& string, bool caseSensitive = true) const;

	/**
	 * Returns whether the string ends with the specified string.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to compare
	 * @param caseSensitive whether the string should be compared case sensitive or not
	 * @return whether the current string ends with the specified string
	 */
	SIMPLECORE_API bool endsWith(const AString& string, bool caseSensitive = true) const;

	/**
	 * Returns whether the string is equal to the specified string.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to compare
	 * @param caseSensitive whether the string should be compared case sensitive or not
	 * @return whether the string is equal to the specified string
	 */
	SIMPLECORE_API bool equals(const AString& string, bool caseSensitive = true) const;

	/**
	 * Returns whether the current string is empty.
	 *
	 * @return whether the current string is empty
	 */
	SIMPLECORE_API bool isEmpty() const;

	/**
	 * Returns whether the current string is a floating point number.
	 *
	 * @return whether the current string is a floating point number
	 */
	SIMPLECORE_API bool isFloatNumber() const;

	/**
	 * Returns whether the current string is a number.
	 *
	 * @return whether the current string is a number
	 */
	SIMPLECORE_API bool isNumber() const;

	/**
	 * Returns whether the current string consists of escape characters only.
	 *
	 * @return whether the current string consists of escape characters only
	 */
	SIMPLECORE_API bool isOnlyEscapes() const;

	/**
	 * Returns whether the current string consists of whitespaces only.
	 *
	 * @return whether the current string consists of whitespaces only
	 */
	SIMPLECORE_API bool isOnlyWhitespaces() const;

	/**
	 * Returns whether the current string does not contain whitespaces.
	 *
	 * @return whether the current string does not contain whitespaces
	 */
	SIMPLECORE_API bool isWithoutWhitespaces() const;

	/**
	 * Returns whether the string starts with the specified string.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to compare
	 * @param caseSensitive whether the string should be compared case sensitive or not
	 * @return whether the current string starts with the specified string
	 */
	SIMPLECORE_API bool startsWith(const AString& string, bool caseSensitive = true) const;

	/**
	 * Counts the occurrences of the specified char and returns the value.
	 * If caseSensitive is true (default), the char will be searched case sensitive.
	 *
	 * @param c the char to count
	 * @param caseSensitive whether the char should be counted case sensitive or not
	 * @return the count of c occurring in the string
	 */
	SIMPLECORE_API size_t count(char c, bool caseSensitive = true) const;

	/**
	 * Counts the occurrences of the specified string and returns the value.
	 * If caseSensitive is true (default), the string will be searched case sensitive.
	 *
	 * @param string the string to count
	 * @param caseSensitive whether the string should be counted case sensitive or not
	 * @return the count of string occurring in the string
	 */
	SIMPLECORE_API size_t count(const AString& string, bool caseSensitive = true) const;

	/**
	 * Counts the words in the string and returns the value.
	 *
	 * @return the count of words in the string
	 */
	SIMPLECORE_API size_t countWords() const;

	/**
	 * Returns the first index of the specified character occurrence.
	 * Returns (uint64)-1 if there is no such char.
	 *
	 * @param c the char to find
	 * @return the first index of the specified char
	 */
	SIMPLECORE_API size_t firstIndexOf(char c) const;

	/**
	 * Returns the first index of the specified character occurrence.
	 * Returns (uint64)-1 if there is no such char.
	 *
	 * @param c the char to find
	 * @return the first index of the specified char
	 */
	SIMPLECORE_API size_t indexOf(char c) const;

	/**
	 * Returns the last index of the specified character occurrence.
	 * Returns (uint64)-1 if there is no such char.
	 *
	 * @param c the char to find
	 * @return the last index of the specified char
	 */
	SIMPLECORE_API size_t lastIndexOf(char c) const;

	/**
	 * Converts the current string to bool and returns it.
	 * If the lowercase string is "true" or a number greater than zero,
	 * the function returns true.
	 * If the string is anything else than a number greater than zero
	 * or lowercase "true", the function returns false.
	 *
	 * @return the bool converted from string
	 */
	SIMPLECORE_API bool toBool() const;

	/**
	 * Converts the current string to char and returns it.
	 *
	 * @return the char converted from string
	 */
	SIMPLECORE_API char toChar() const;

	/**
	 * Converts the current string to byte and returns it.
	 *
	 * @return the byte converted from string
	 */
	SIMPLECORE_API byte toByte() const;

	/**
	 * Converts the current string to short and returns it.
	 *
	 * @return the short converted from string
	 */
	SIMPLECORE_API short toShort() const;

	/**
	 * Converts the current string to ushort and returns it.
	 *
	 * @return the ushort converted from string
	 */
	SIMPLECORE_API ushort toUShort() const;

	/**
	 * Converts the current string to int32 and returns it.
	 *
	 * @return the int32 converted from string
	 */
	SIMPLECORE_API int toInt(int base = 10) const;

	/**
	 * Converts the current string to uint32 and returns it.
	 *
	 * @return the uint32 converted from string
	 */
	SIMPLECORE_API uint toUInt(int base = 10) const;

	/**
	 * Converts the current string to int64 and returns it.
	 *
	 * @return the int64 converted from string
	 */
	SIMPLECORE_API int64 toInt64(int base = 10) const;

	/**
	 * Converts the current string to uint64 and returns it.
	 *
	 * @return the uint64 converted from string
	 */
	SIMPLECORE_API uint64 toUInt64(int base = 10) const;

	/**
	 * Converts the current string to char array and returns it.
	 *
	 * @return the char array converted from string
	 */
	SIMPLECORE_API const char* toCString() const;

	/**
	 * Converts the current string to float and returns it.
	 *
	 * @return the float converted from string
	 */
	SIMPLECORE_API float toFloat() const;

	/**
	 * Converts the current string to double and returns it.
	 *
	 * @return the double converted from string
	 */
	SIMPLECORE_API double toDouble() const;

	/**
	 * Converts the current string to long double and returns it.
	 *
	 * @return the long double converted from string
	 */
	SIMPLECORE_API long double toLongDouble() const;

	/**
	 * Converts the current string to std::string and returns it.
	 *
	 * @return the string converted to std::string
	 */
	SIMPLECORE_API std::string toStdString() const;

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @param inLetters whether the string should be printed in letters
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(bool n, bool inLetters = false);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(char n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(short n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(int n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(int64 n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(byte n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(ushort n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(uint n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(uint64 n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(float n);

	/**
	 * Converts the specified number to string and returns it.
	 *
	 * @param n the number to convert
	 * @return the specified number converted to string
	 */
	SIMPLECORE_API static AString toString(double n);

};

#endif   // ASTRING_H
