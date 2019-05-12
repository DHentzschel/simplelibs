#ifndef CHAR_H
#define CHAR_H

namespace Char {
	bool isWhitespace(char character)
	{
		return character == '\t' || character == '\r' || character == '\n' || character == ' ' || character == '\f' || character == '\v';
	}

	char toLower(char character)
	{
		return character | 0x20;
	}

	char toUpper(char character)
	{
		return character & ~0x20;
	}
};

#endif   // CHAR_H
