#ifndef INIFILE_H
#define INIFILE_H

#include "osdetection.h"
#include "file.h"

#include "astring.h"
#include <map>

/**
 * This class makes it easy to parse an INI file.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class IniFile : protected File {
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
	 * Deletes the current group and writes the changes to file.
	 */
	SIMPLECORE_API void deleteGroup(const AString& group = "");

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
	SIMPLECORE_API AString value(const AString& key, const AString& defaultValue = "null") const;

	/**
	 * Sets the value of the key specified.
	 *
	 * @param key the key to find
	 * @param value the value to set
	 */
	SIMPLECORE_API void setValue(const AString& key, const AString& value);

private:
	struct Group {
		AString name;
		
		std::map<AString, AString> keyValues;
	};

	Vector<Group> groups_;

	AString group_;

	uint groupCount_;

	uint keyCount_;
	
	void read();

	void writeGroup(const AString& group);

	void writeValue(const AString& key, const AString& value);
};

#endif // INIFILE_H
