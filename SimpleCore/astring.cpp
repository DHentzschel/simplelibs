#include "astring.h"

#include <algorithm>
#include <regex>

#include "char.h"
#include "functions.h"

AString::AString(const AString& string) : std::string(string)
{}

AString::AString(const std::string& string) : std::string(string)
{}

AString::AString(const char* string) : std::string(string)
{}

AString AString::arg(const AString& value)
{
	// TODO: compare performance to find and then replace
	String copy = *this;
	for (auto i = 1; i <= 100; ++i) {
		const auto replacable = "%" + String::toString(i);
		if (copy.contains(replacable)) {
			copy.replaceAll(replacable, value);
			break;
		}
	}
	return copy;
}

AString AString::left(const size_t n) const
{
	String result;
	if (n < size()) {
		for (size_t i = 0; i < n && i != UINT32_MAX; ++i) {
			result += at(i);
		}
	}
	return result;
}

AString AString::right(const size_t n) const
{
	AString result;
	if (n < size()) {
		for (uint i = size() - n; i < size() && i != UINT32_MAX; ++i) {
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

AString& AString::fill(const char c, const size_t size)
{
	if (size == UINT32_MAX) {
		for (auto& i : *this) {
			i = c;
		}
	}
	else {
		for (uint i = 0; i < size && i != UINT32_MAX; ++i) {
			(*this)[i] = c;
		}
	}
	return *this;
}

AString& AString::prepend(const char c)
{
	*this = c + *this;
	return *this;
}

AString& AString::prepend(const AString& string)
{
	*this = string + *this;
	return *this;
}

AString& AString::removeAll(const char c, const bool caseSensitive)
{
	return replaceAll(String().prepend(c), "", caseSensitive);
}

AString& AString::removeAll(const AString& string, const bool caseSensitive)
{
	return replaceAll(string, "", caseSensitive);
}

AString& AString::removeFirst(const char c, const bool caseSensitive)
{
	return replaceFirst(String().prepend(c), "", caseSensitive);
}

AString& AString::removeFirst(const AString& string, const bool caseSensitive)
{
	return replaceFirst(string, "", caseSensitive);
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

AString& AString::replaceAll(const AString& from, const AString& to, const bool caseSensitive)
{
	if (from.isEmpty()) {
		return *this;
	}

	auto copyThis = *this;
	auto copyFrom = from;

	if (!caseSensitive) {
		copyThis.toLower();
		copyFrom.toLower();
	}
	auto position = copyThis.find(copyFrom);
	while (position != std::string::npos) {
		std::string::replace(position, copyFrom.size(), to);
		copyThis.replace(position, copyFrom.size(), to);
		position = copyThis.find(copyFrom);
	}
	return *this;
}

AString& AString::replaceFirst(const AString& from, const AString& to, const bool caseSensitive)
{
	if (from.isEmpty()) {
		return *this;
	}

	auto copyThis = *this;
	auto copyFrom = from;

	if (!caseSensitive) {
		copyThis.toLower();
		copyFrom.toLower();
	}
	auto position = copyThis.find(copyFrom);
	while (position != std::string::npos) {
		std::string::replace(position, copyFrom.size(), to);
		copyThis.replace(position, copyFrom.size(), to);
		position = copyThis.find(copyFrom);
		return *this;
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
	static auto chars = "\t\n\v\f\r ";
	erase(find_last_not_of(chars) + 1);
	erase(0, find_first_not_of(chars));
	return *this;
}

StringVector AString::split(const char separator, const bool caseSensitive) const
{
	return split(String().append(separator), caseSensitive);
}

StringVector AString::split(const AString& separator, const bool caseSensitive) const
{
	auto copySeparator = String(separator);
	auto copyThis = String(*this);

	if (!caseSensitive) {
		copySeparator.toLower();
		copyThis.toLower();
	}

	StringVector result;
	auto start = copyThis.find_first_not_of(separator);

	uint end;
	while ((end = copyThis.find_first_of(copySeparator, start)) != npos) {
		result.push_back(substr(start, end - start));
		start = copyThis.find_first_not_of(copySeparator, end);
	}
	if (start != npos) {
		result.push_back(substr(start));
	}
	return result;
}

StringVector AString::splitByNonNumerics() const
{
	return splitByCharset(false);
}

StringVector AString::splitByNumerics() const
{
	return splitByCharset(true);
}

ByteArray AString::toByteArray() const
{
	ByteArray result;
	result.assign(begin(), end());
	return result;
}

bool AString::contains(const char c, const bool caseSensitive) const
{
	return contains(String(1, c), caseSensitive);
}

bool AString::contains(const AString& string, const bool caseSensitive) const
{
	if (!caseSensitive) {
		return String(*this).toLower().find(String(string).toLower()) != npos;
	}
	return find(string) != npos;
}

bool AString::endsWith(const AString& string, const bool caseSensitive) const
{
	/* Save calculating time by comparing length of both */
	if (size() < string.size()) {
		return false;
	}

	/* Only lower both strings if desired */
	if (!caseSensitive) {
		return String(*this).toLower().rfind(String(string).toLower()) == string.size();
	}

	/* Store data in var for faster access */
	const auto data = this->data();

	auto result = true;
	for (auto i = size() - 1, j = string.size() - 1;
		i >= 0 && j > 0 && i < UINT32_MAX && j < UINT32_MAX; --i) {
		/* Compare chars exactly */
		if (data[i] != string[j]) {
			result = false;
			break;
		}
		--j;
	}
	return result;
}

bool AString::equals(const AString& string, const bool caseSensitive) const
{
	auto copyThis = *this;
	auto copyString = string;
	if (!caseSensitive) {
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
		if (!Char::isWhitespace(*it)) {
			return false;
		}
	}
	return true;
}

bool AString::isWithoutWhitespaces() const
{
	for (auto it = begin(); it != end(); ++it) {
		if (Char::isWhitespace(*it)) {
			return false;
		}
	}
	return true;
}

bool AString::startsWith(const AString& string, const bool caseSensitive) const
{
	/* Save calculating time by comparing length of both */
	if (size() < string.size()) {
		return false;
	}

	/* Only lower both strings if desired */
	if (!caseSensitive) {
		return String(*this).toLower().rfind(String(string).toLower(), 0) == 0;
	}

	/* Store data in vars for faster access */
	const auto data = this->data();
	const auto indexSizeJ = string.size() - 1;

	for (size_t i = 0, j = 0; i < size() && j <= indexSizeJ; ++i, ++j) {
		/* Compare chars exactly */
		if (data[i] != string[j]) {
			return false;
		}
	}
	return true;
}

size_t AString::count(const char c, const bool caseSensitive) const
{
	if (!caseSensitive) {
		auto lowerThis = String(*this).toLower();
		return std::count(lowerThis.begin(), lowerThis.end(), Char::toLower(c));
	}
	return std::count(begin(), end(), c);
}

size_t AString::count(const AString& string, const bool caseSensitive) const
{
	uint result = 0;
	uint position = 0;
	auto copyThis = String(*this);
	auto copyString = String(string);

	if (!caseSensitive) {
		copyThis.toLower();
		copyString.toLower();
	}
	else {
		copyThis = String(*this);
		copyString = String(string);
	}
	while ((position = copyThis.find(copyString, position)) != npos) {
		++result;
		position += copyString.length();
	}
	return result;
}

size_t AString::countWords() const
{
	return count(' ') - 1;
}

size_t AString::firstIndexOf(const char c) const
{
	return indexOf(c);
}

size_t AString::indexOf(const char c) const
{
	for (uint i = 0; i < size(); ++i) {
		if (at(i) == c) {
			return i;
		}
	}
	return UINT32_MAX;
}

size_t AString::lastIndexOf(const char c) const
{
	for (uint i = size() - 1; i >= 0 && i < UINT32_MAX; --i) {
		if (at(i) == c) {
			return i;
		}
	}
	return UINT32_MAX;
}

bool AString::toBool() const
{
	return *this == "1" || equals("true", false) || isNumber() && toInt() > 0;
}

char AString::toChar() const
{
	return static_cast<char>(toInt());
}

byte AString::toByte() const
{
	return static_cast<byte>(toUInt());
}

short AString::toShort() const
{
	return static_cast<short>(toInt());
}

ushort AString::toUShort() const
{
	return static_cast<ushort>(toUInt());
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

void AString::setLocaleGermany()
{
	std::locale::global(std::locale("de-DE"));
}

StringVector AString::splitByCharset(bool splitByNumeric) const
{
	StringVector result;

	bool isNumber = false;
	String tempString;
	for (auto it = begin(); it != end(); ++it) {
		auto value = *it;
		isNumber = String(1, value).isNumber();
		if (splitByNumeric ? !isNumber : isNumber) {
			tempString.append(value);
			if (it + 1 == end()) {
				result.append(tempString);
			}
		}
		else if (!tempString.isEmpty()) {
			result.append(tempString);
			tempString.clear();
		}
	}
	return result;
}
