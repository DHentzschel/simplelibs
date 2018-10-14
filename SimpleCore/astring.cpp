#include "astring.h"

#include <algorithm>
#include <regex>

#include "char.h"
#include "functions.h"

AString::AString(const AString& string) : std::string(string)
{}

AString::AString(const std::string& right) : std::string(right)
{}

AString::AString(const char* right) : std::string(right)
{}

AString AString::arg(const AString& value)
{
    AString copy = *this;
    for (auto i = 0; i < 20; ++i) {
        const auto replacable = "%" + TO_STRING(i);
        if (copy.contains(replacable)) {
            copy.replaceFirst(replacable, value);
            if (copy.contains(replacable)) {
                continue;
            }
            else {
                break;
            }
        }
    }
    return copy;
}

AString AString::left(const uint n) const
{
    AString result;
    if (n < size()) {
        for (uint64 i = 0; i < n; ++i) {
            result += at(STATIC_CAST(uint, i));
        }
    }
    return result;
}

AString AString::right(const uint n) const
{
    AString result;
    if (n < size()) {
        for (auto i = size() - n; i < size(); ++i) {
            result += at(i);
        }
    }
    return result;
}

AString& AString::append(const char c)
{
    *this += c;
    return *this;
}

AString& AString::append(const AString& string)
{
    *this += string;
    return *this;
}

AString& AString::fill(const char c, const int size)
{
    if (size == -1) {
        for (auto& i : *this) {
            i = c;
        }
    }
    else {
        clear();
        for (auto i = 0; i < size; ++i) {
            *this += c;
        }
    }
    return *this;
}

AString& AString::prepend(const char c)
{
    return *this = c + *this;
}

AString& AString::prepend(const AString& string)
{
    return *this = string + *this;
}

AString& AString::removeAll(const char c, const CaseSensitivity cs)
{
    return replaceAll(AString().prepend(c), "", cs);
}

AString& AString::removeAll(const AString& string, const CaseSensitivity cs)
{
    return replaceAll(string, "", cs);
}

AString& AString::removeFirst(const char c, const CaseSensitivity cs)
{
    return replaceFirst(AString().prepend(c), "", cs);
}

AString& AString::removeFirst(const AString& string, const CaseSensitivity cs)
{
    return replaceFirst(string, "", cs);
}

AString& AString::repeat(const int times)
{
    if (times < 1) {
        clear();
    }
    else {
        const auto copy = *this;
        for (auto i = 0; i < times; ++i) {
            append(copy);
        }
    }
    return *this;
}

AString& AString::replaceAll(const AString& from, const AString& to, const CaseSensitivity cs)
{
    auto copyFrom = from;
    if (cs == CaseInsensitive) {
        copyFrom.toLower();
    }
    size_t position = 0;
    while ((position = find(copyFrom, position)) != npos) {
        replace(position, copyFrom.length(), to);
        position += to.length();
    }
    return *this;
}

AString& AString::replaceFirst(const AString& from, const AString& to, const CaseSensitivity cs)
{
    auto copyFrom = from;
    if (cs == CaseInsensitive) {
        copyFrom.toLower();
    }
    size_t position = 0;
    if ((position = find(copyFrom, position)) != npos) {
        replace(position, copyFrom.length(), to);
        // ReSharper disable CppAssignedValueIsNeverUsed
        position += to.length();
        // ReSharper restore CppAssignedValueIsNeverUsed
    }
    return *this;
}

AString& AString::toLower()
{
    std::transform(begin(), end(), begin(), tolower);
    return *this;
}

AString& AString::toUpper()
{
    std::transform(begin(), end(), begin(), toupper);
    return *this;
}

AString& AString::trim()
{
    AString result;
    auto nonWhitespaceFound = false;
    for (size_t i = size(); i > 0; --i) {
        if (nonWhitespaceFound) {
            result.prepend(at(--i));
        }
        else {
            if (!Char(at(--i)).isWhitespace()) {
                nonWhitespaceFound = true;
                result.prepend(at(i));
            }
        }
    }
    return *this = result;
}

AVector<AString> AString::split(const char separator, const CaseSensitivity cs) const
{
    return split(AString().append(separator));
}

AVector<AString> AString::split(const AString& separator, const CaseSensitivity cs) const
{
    auto copySeparator = AString(separator);
    auto copyThis = AString(*this);

    if (cs == CaseInsensitive) {
        copySeparator.toLower();
        copyThis.toLower();
    }

    AVector<AString> result;
    auto start = copyThis.find_first_not_of(separator);

    size_t end;
    while ((end = copyThis.find_first_of(copySeparator, start)) != npos) {
        result.push_back(substr(start, end - start));
        start = copyThis.find_first_not_of(copySeparator, end);
    }
    if (start != npos) {
        result.push_back(substr(start));
    }
    return result;
}

AVector<AString> AString::splitByNonNumerics() const
{
    AVector<AString> result;

    bool wasNumber = false;
    AString tempString;
    for (size_t i = 0; i <= size(); ++i) {
        wasNumber = i < size() ? AString(1, at(i)).isNumber() : false;
        if (wasNumber && i < size()) {
            tempString.append(at(i));
        }
        else {
            if (!tempString.isEmpty()) {
                result.append(tempString);
                tempString.clear();
            }
        }
    }
    return result;
}

AVector<AString> AString::splitByNumerics() const
{
    AVector<AString> result;

    bool wasNumber = false;
    AString tempString;
    for (size_t i = 0; i < size(); ++i) {
        wasNumber = AString(1, at(i)).isNumber();
        if (!wasNumber) {
            tempString.append(at(i));
        }
        else {
            if (!tempString.isEmpty()) {
                result.append(tempString);
                tempString.clear();
            }
        }
    }
    return result;
}

ByteArray AString::toByteArray() const
{
    ByteArray result;
    result.assign(begin(), end());
    return result;
}

bool AString::contains(const char c, const CaseSensitivity cs) const
{
    return contains(AString(1, c), cs);
}

bool AString::contains(const AString& string, const CaseSensitivity cs) const
{
    if (cs == CaseInsensitive) {
        return AString(*this).toLower().find(AString(string).toLower()) != npos;
    }
    return find(string) != npos;
}

bool AString::endsWith(const AString& string, const CaseSensitivity cs) const
{
    /* Save calculating time by comparing length of both */
    if (size() < string.size()) {
        return false;
    }

    /* Only lower both strings if desired */
    if (cs == CaseInsensitive) {
        return AString(*this).toLower().rfind(AString(string).toLower()) ==
            string.size();
    }

    /* Store data in var for faster access */
    const auto data = this->data();

    auto result = true;
    for (auto i = size() - 1, j = string.size() - 1; i >= 0 && j > 0; --i) {
        /* Compare chars exactly */
        if (data[i] != string[j]) {
            result = false;

            break;
        }
        --j;
    }
    return result;
}

bool AString::equals(const AString& string, CaseSensitivity cs) const
{
    auto copyThis = *this;
    auto copyString = string;
    if (cs == CaseInsensitive) {
        copyThis.toLower();
        copyString.toLower();
    }
    return copyThis == copyString;
}

bool AString::isEmpty() const
{
    return empty();
}

bool AString::isFloatNumber() const
{
    return std::regex_match(*this, std::regex("-?[0-9]+([.][0-9]+)?"));
}

bool AString::isNumber() const
{
    return std::regex_match(*this, std::regex("-?[0-9]+"));
}

bool AString::isOnlyEscapes() const
{
    auto result = true;
    for (auto it = begin(); it != end(); ++it) {
        if (!(*it >= 0 && *it <= 0x1F || *it == 0x7F)) {
            result = false;
        }
    }
    return result;
}

bool AString::isOnlyWhitespaces() const
{
    for (auto it = begin(); it != end(); ++it) {
        if (!Char(*it).isWhitespace()) {
            return false;
        }
    }
    return true;
}

bool AString::isWithoutWhitespaces() const
{
    for (auto it = begin(); it != end(); ++it) {
        if (Char(*it).isWhitespace()) {
            return false;
        }
    }
    return true;
}

bool AString::startsWith(const AString& string, CaseSensitivity cs) const
{
    /* Save calculating time by comparing length of both */
    if (size() < string.size()) {
        return false;
    }

    /* Only lower both strings if desired */
    if (cs == CaseInsensitive) {
        return AString(*this).toLower().rfind(AString(string).toLower(), 0) ==
            0;
    }

    /* Store data in vars for faster access */
    const auto data = this->data();
    const auto indexSizeI = size() - 1;
    const auto indexSizeJ = string.size() - 1;

    for (size_t i = 0, j = 0; i < size() && j <= indexSizeJ; ++i, ++j) {
        /* Compare chars exactly */
        if (data[i] != string[j]) {
            return false;
        }
    }
    return true;
}

size_t AString::count(const char c, const CaseSensitivity cs) const
{
    if (cs == CaseInsensitive) {
        auto lowerThis = AString(*this).toLower();
        return std::count(lowerThis.begin(), lowerThis.end(),
            Char(c).toLower());
    }
    return std::count(begin(), end(), c);
}

size_t AString::count(const AString& string, const CaseSensitivity cs) const
{
    uint result = 0;
    size_t position = 0;
    auto copyThis = AString(*this);
    auto copyString = AString(string);

    if (cs == CaseInsensitive) {
        copyThis.toLower();
        copyString.toLower();
    }
    else {
        copyThis = AString(*this);
        copyString = AString(string);
    }
    while ((position = copyThis.find(copyString, position)) != npos) {
        ++result;
        position += copyString.length();
    }
    return result;
}

size_t AString::countWords() const
{
    return count(' ');
}

size_t AString::firstIndexOf(const char c) const
{
    return indexOf(c);
}

size_t AString::indexOf(const char c) const
{
    for (size_t i = 0; i < size(); ++i) {
        if (at(i) == c) {
            return i;
        }
    }
    return -1;
}

size_t AString::lastIndexOf(const char c) const
{
#pragma warning (disable : 4244)
    for (long double i = size() - 1; i >= 0; --i) {
        if (at(i) == c) {
            return i;
        }
    }
    return STATIC_CAST(size_t, -1);
#pragma warning (default : 4244)
}

bool AString::toBool() const
{
    return *this == "1" || AString(*this).toLower() == "true";
}

char AString::toChar() const
{
    return STATIC_CAST(char, toInt());
}

byte AString::toByte() const
{
    return STATIC_CAST(byte, toUInt());
}

short AString::toShort() const
{
    return STATIC_CAST(short, toInt());
}

ushort AString::toUShort() const
{
    return STATIC_CAST(ushort, toUInt());
}

int AString::toInt(const int base) const
{
    return std::stoi(*this, nullptr, base);
}

uint AString::toUInt(const int base) const
{
    return std::stoul(*this, nullptr, base);
}

int64 AString::toInt64(const int base) const
{
    return std::stoll(*this, nullptr, base);
}

uint64 AString::toUInt64(const int base) const
{
    return std::stoull(*this, nullptr, base);
}

float AString::toFloat() const
{
    return std::stof(*this);
}

double AString::toDouble() const
{
    return std::stod(*this);
}

long double AString::toLongDouble() const
{
    return std::stold(*this);
}

const char* AString::toCString() const
{
    return c_str();
}

std::string AString::toStdString() const
{
    return *this;
}

AString AString::toString(const bool n, const bool inLetters)
{
    return inLetters ? (n ? "true" : "false") : (n ? "1" : "0");
}

AString AString::toString(const char n)
{
    return std::to_string(n);
}

AString AString::toString(const short n)
{
    return std::to_string(n);
}

AString AString::toString(const int n)
{
    return AString(std::to_string(n));
}

AString AString::toString(const int64 n)
{
    return std::to_string(n);
}

AString AString::toString(const byte n)
{
    return std::to_string(n);
}

AString AString::toString(const ushort n)
{
    return std::to_string(n);
}

AString AString::toString(const uint n)
{
    return std::to_string(n);
}

AString AString::toString(const uint64 n)
{
    return std::to_string(n);
}

AString AString::toString(const float n)
{
    return std::to_string(n);
}

AString AString::toString(const double n)
{
    return std::to_string(n);
}
