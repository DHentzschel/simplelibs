#include "sqlutils.h"

/**
 * \brief Serializes mysql type by passed parameter string and returns type.
 * \param string parsable string containing type
 * \return mysql type
 */
enum_field_types SqlUtils::getMySqlType(const AString& string)
{
    if (startsWithEntry(string, { "bigi", "int8" })) {
        return MYSQL_TYPE_LONGLONG;
    }
    if (string.startsWith("bit")) {
        return MYSQL_TYPE_BIT;
    }
    if (string.startsWith("blob")) {
        return MYSQL_TYPE_BLOB;
    }
    if (startsWithEntry(string, { "char", "bool", "int1", "tin" })) {
        return MYSQL_TYPE_TINY;
    }
    if (string.startsWith("date(")) {
        return MYSQL_TYPE_DATE;
    }
    if (string.startsWith("datet")) {
        return MYSQL_TYPE_DATETIME;
    }
    if (startsWithEntry(string, { "dec", "fixed", "numeric" })) {
        return MYSQL_TYPE_DECIMAL;
    }
    if (startsWithEntry(string, { "float8", "double" })) {
        return MYSQL_TYPE_DOUBLE;
    }
    if (string.startsWith("enum")) {
        return MYSQL_TYPE_ENUM;
    }
    if (startsWithEntry(string, { "float(", "float4" })) {
        return MYSQL_TYPE_FLOAT;
    }
    if (startsWithEntry(string,
        { "int(", "inte", "int4", "mediumi", "int3", "mid" })) {
        return MYSQL_TYPE_LONG;
    }
    if (string.startsWith("js")) {
        return MYSQL_TYPE_JSON;
    }
    if (string.startsWith("longb")) {
        return MYSQL_TYPE_LONG_BLOB;
    }
    if (startsWithEntry(string, { "longt", "varchar", "string", "text",
                                  "mediumt", "tinyt" })) {
        return MYSQL_TYPE_STRING;
    }
    if (startsWithEntry(string, { "sh", "int2", "small" })) {
        return MYSQL_TYPE_SHORT;
    }
    if (startsWithEntry(string, { "mediumb", "longvarb" })) {
        return MYSQL_TYPE_MEDIUM_BLOB;
    }
    if (string.startsWith("tinyb")) {
        return MYSQL_TYPE_TINY_BLOB;
    }
    if (string.startsWith("blob")) {
        return MYSQL_TYPE_BLOB;
    }
    if (string.startsWith("time(")) {
        return MYSQL_TYPE_TIME;
    }
    if (string.startsWith("times")) {
        return MYSQL_TYPE_TIMESTAMP;
    }
    if (string.startsWith("y")) {
        return MYSQL_TYPE_YEAR;
    }
    return MYSQL_TYPE_NULL;
}

/**
 * \brief Parses mysql type length from passed param string.
 * \param string parsable string
 * \return mysql type length
 */
short SqlUtils::getMySqlLength(const AString& string)
{
    AString result;
    for (auto c : string) {
        if (c >= '0' && c <= '9') {
            result.append(c);
        }
    }
    return result.isEmpty() ? 127 : result.toShort();
}

/**
 * \brief Returns if vector containing strings contains string passed by param.
 * \param string parsable string
 * \param vector vector to check
 * \return vector containing string or not
 */
bool SqlUtils::startsWithEntry(const AString& string,
    const AVector<AString>& vector)
{
    for (auto& entry : vector) {
        if (string.startsWith(entry)) {
            return true;
        }
    }
    return false;
}
