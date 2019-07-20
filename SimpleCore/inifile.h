#ifndef INIFILE_H
#define INIFILE_H

#include "astring.h"

/**
 * This class makes it easy to parse an INI file.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class IniFile {
public:
	/**
	 * Calls the default constructor.
	 */
	SIMPLECORE_API IniFile();

	/**
	 * Sets the filepath passed by parameter.
	 *
	 * @param filepath the filepath to set
	 */
	SIMPLECORE_API explicit IniFile(const AString& filepath);

	/**
	 * Sets the current filepath and calculates the group and key count.
	 *
	 * @param filepath the filepath to set
	 */
	SIMPLECORE_API void setFilepath(const AString& filepath);

	/**
	 * Sets the current focus to the group specified.
	 *
	 * @param group the group to focus on
	 */
	SIMPLECORE_API void beginGroup(const AString& group);

	/**
	 * Sets the current group focus to none.
	 */
	SIMPLECORE_API void endGroup();

	/**
	 * Returns the group count.
	 *
	 * @return the group count
	 */
	SIMPLECORE_API uint getGroupCount();

	/**
	 * Returns the key count.
	 *
	 * @return the key count
	 */
	SIMPLECORE_API uint getKeyCount();

	/**
	 * Returns the value of the key specified.
	 * Returns "empty" when the value is null or not existent.
	 *
	 * @param key the key to find
	 * @return the value
	 */
	SIMPLECORE_API AString value(const AString& key) const;

	/**
	 * Sets the value of the key specified.
	 *
	 * @param key the key to find
	 * @param value the value to set
	 */
	SIMPLECORE_API void setValue(const AString& key, const AString& value) const;

private:
	AString filepath_;

	AString group_;

	AVector<AString> fileContent_;

	uint groupCount_;

	uint keyCount_;

	/**
	 * Calculates the group count.
	 */
	void calculateGroupCount();

	/**
	 * Calculates the key count.
	 */
	void calculateKeyCount();
};

#endif // INIFILE_H
