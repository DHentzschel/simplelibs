#ifndef ASTRING_H
#define ASTRING_H

#include <string>
#include <variant>

#include "functions.h"

#include "avector.h"
#include "bytearray.h"
#include "types.h"

class AString : public std::string {
public:
    using std::string::string;

    AString() = default;

    AString(const AString& string);

    AString(const std::string& right);

    AString(const char* right);

    AString arg(const AString& value);

    AString left(size_t n) const;

    AString right(size_t n) const;

    AString& append(char c);

    AString& append(const AString& string);

    AString& fill(char c, size_t size = -1);

    AString& prepend(char c);

    AString& prepend(const AString& string);

    AString& removeAll(char c, bool caseSensitive = true);

    AString& removeAll(const AString& string, bool caseSensitive = true);

    AString& removeFirst(char c, bool caseSensitive = true);

    AString& removeFirst(const AString& string, bool caseSensitive = true);

    AString& repeat(int times);

    AString& replaceAll(const AString& from, const AString& to, bool caseSensitive = true);

    AString& replaceFirst(const AString& from, const AString& to, bool caseSensitive = true);

    AString& toLower();

    AString& toUpper();

    AString& trim();

    AVector<AString> split(char separator, bool caseSensitive = true) const;

    AVector<AString> split(const AString& separator, bool caseSensitive = true) const;

    AVector<AString> splitByNonNumerics() const;

    AVector<AString> splitByNumerics() const;

    ByteArray toByteArray() const;

    bool contains(char c, bool caseSensitive = true) const;

    bool contains(const AString& string, bool caseSensitive = true) const;

    bool endsWith(const AString& string, bool caseSensitive = true) const;

    bool equals(const AString& string, bool caseSensitive = true) const;

    bool isEmpty() const;

    bool isFloatNumber() const;

    bool isNumber() const;

    bool isOnlyEscapes() const;

    bool isOnlyWhitespaces() const;

    bool isWithoutWhitespaces() const;

    bool startsWith(const AString& string, bool caseSensitive = true) const;

    size_t count(char c, bool caseSensitive = true) const;

    size_t count(const AString& string, bool caseSensitive = true) const;

    size_t countWords() const;

    size_t firstIndexOf(char c) const;

    size_t indexOf(char c) const;

    size_t lastIndexOf(char c) const;

    bool toBool() const;

    char toChar() const;

    byte toByte() const;

    short toShort() const;

    ushort toUShort() const;

    int toInt(int base = 10) const;

    uint toUInt(int base = 10) const;

    int64 toInt64(int base = 10) const;

    uint64 toUInt64(int base = 10) const;

    const char* toCString() const;

    float toFloat() const;

    double toDouble() const;

    long double toLongDouble() const;

    std::string toStdString() const;

    static AString toString(bool n, bool inLetters = false);

    static AString toString(char n);

    static AString toString(short n);

    static AString toString(int n);

    static AString toString(int64 n);

    static AString toString(byte n);

    static AString toString(ushort n);

    static AString toString(uint n);

    static AString toString(uint64 n);

    static AString toString(float n);

    static AString toString(double n);

};

#endif   // ASTRING_H
