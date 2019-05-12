#ifndef CHAR_H
#define CHAR_H

namespace Char {
	inline bool isWhitespace(char character)
	{
		return character == '\t' || character == '\r' || character == '\n' || character == ' ' || character == '\f' || character == '\v';
	}

	inline char toLower(char character)
	{
		return character | 0x20;
	}

	inline char toUpper(char character)
	{
		return character & ~0x20;
	}
};

#endif   // CHAR_H
