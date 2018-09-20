#include "sqlvariant.h"

/**
 * \brief Constructs instance by setting some values passed by params.
 * \param data void array
 * \param useCasts if static casts should be used
 */
SqlVariant::SqlVariant(void* data, const bool useCasts, bool fromString) :
    useCasts_(useCasts),
    fromString_(fromString),
    data_(data)
{}

/**
 * \brief Returns if data were set.
 * \return nullptr if not, otherwise pointer
 */
bool SqlVariant::isValid() const
{
    return data_;
}

/**
 * \brief Converts data to bool and returns it.
 * \return value
 */
bool SqlVariant::toBool() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toBool() :  *reinterpret_cast<bool*>(data_)) : 0;
}

/**
* \brief Converts data to char and returns it.
* \return value
*/
char SqlVariant::toChar() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toChar() :  *reinterpret_cast<char*>(data_)) : 0;
}

/**
* \brief Converts data to byte and returns it.
* \return value
*/
byte SqlVariant::toByte() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toByte() :  *reinterpret_cast<byte*>(data_)) : 0;
}

/**
* \brief Converts data to short and returns it.
* \return value
*/
short SqlVariant::toShort() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toShort() :  *reinterpret_cast<short*>(data_)) : 0;
}

/**
* \brief Converts data to ushort and returns it.
* \return value
*/
ushort SqlVariant::toUShort() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toUShort() :  *reinterpret_cast<ushort*>(data_)) : 0;
}

/**
* \brief Converts data to int and returns it.
* \return value
*/
int SqlVariant::toInt() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toInt() :  *reinterpret_cast<int*>(data_)) : 0;
}

/**
* \brief Converts data to uint and returns it.
* \return value
*/
uint SqlVariant::toUInt() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toUInt() :  *reinterpret_cast<uint*>(data_)) : 0;
}

/**
* \brief Converts data to int64 and returns it.
* \return value
*/
int64 SqlVariant::toInt64() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toInt64() :  *reinterpret_cast<int64*>(data_)) : 0;
}

/**
* \brief Converts data to uint64 and returns it.
* \return value
*/
uint64 SqlVariant::toUInt64() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toUInt64() :  *reinterpret_cast<uint64*>(data_)) : 0;
}

/**
* \brief Converts data to float and returns it.
* \return value
*/
float SqlVariant::toFloat() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toFloat() :  *reinterpret_cast<float*>(data_)) : 0;
}

/**
* \brief Converts data to double and returns it.
* \return value
*/
double SqlVariant::toDouble() const
{
    return isValid() ? (fromString_ ? AString(toCString()).toDouble() :  *reinterpret_cast<double*>(data_)) : 0;
}

/**
* \brief Converts data to char array and returns it.
* \return value
*/
const char* SqlVariant::toCString() const
{
    return isValid() ? reinterpret_cast<char*>(data_) : "NULL";
}

/**
* \brief Converts data to string and returns it.it.
* \return value
*/
AString SqlVariant::toString() const
{
    return toCString();
}