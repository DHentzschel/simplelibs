#ifndef FILE_H
#define FILE_H

#include <fstream>

#include "astring.h"
#include "avector.h"
#include "openmode.h"

#include "simplecore.h"

/**
 * Provides simple functions to create, modify, erase etc. files.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class File {
public:
	/**
	 * Sets the openMode to NotOpen on default.
	 */
	SIMPLECORE_API File();

	/**
	 * Copies the openMode and file path from the given parameter.
	 *
	 * @param file the copyable object
	 */
	SIMPLECORE_API File(const File& file);

	/**
	 * Sets the filepath to the parameter and sets the openMode to NotOpen on default.
	 *
	 * @param filepath the filepath to use
	 */
	SIMPLECORE_API explicit File(const AString& filepath) noexcept;

	/**
	 * Closes the current filestream if opened.
	 */
	SIMPLECORE_API ~File();

	/**
	* Tries to create the current filepath.
	*
	* @param recursively if not existing, subfolders should be created
	* @return if the filepath could be created
	*/
	SIMPLECORE_API bool create(bool recursively = true) const;

	/**
	* Tries to create the filepath given as parameter.
	*
	* @param filepath the filepath to create
	* @param recursively if not existing, subfolders should be created
	* @return if the file path could be created
	*/
	SIMPLECORE_API static bool create(const AString& filepath, bool recursively = true);

	/**
	 * Tries to erase the file in filepath and returns the success.
	 *
	 * @return whether the file has been erased or not
	 */
	SIMPLECORE_API bool erase() const;

	/**
	 * Tries to erase the file in filepath given as parameter and returns the success.
	 *
	 * @param filepath the filepath to erase
	 * @return whether the file has been erased or not
	 */
	SIMPLECORE_API static bool erase(const AString& filepath);

	/**
	 * Returns whether the current filepath exists.
	 *
	 * @return whether the current filepath set exists
	 */
	SIMPLECORE_API bool exists() const;

	/**
	 * Returns whether the filepath given as parameter exists.
	 *
	 * @param filepath the filepath to check for existence
	 * @return whether the given filepath exists
	 */
	SIMPLECORE_API static bool exists(const AString& filepath);

	/**
	 * Returns the directory of the filepath.
	 * Example: C:\\Users\\user\\test.dat turns to C:\\Users\\user
	 *
	 * @return the directory of the current filepath
	 */
	SIMPLECORE_API AString getDirectory() const;

	/**
	 * Returns the filename of the filepath.
	 * Example: C:\\Users\\user\\test.dat turns to test.dat
	 *
	 * @return the filename of the current filepath
	 */
	SIMPLECORE_API AString getFilename() const;

	/**
	 * Returns the current filepath set.
	 *
	 * @return the current filepath
	 */
	SIMPLECORE_API AString getFilepath() const;

	/**
	 * Sets the filepath for the next filestream.
	 *
	 * @param filepath the filepath for the filestream
	 */
	SIMPLECORE_API void setFilepath(const AString& filepath);

	/**
	 * Returns whether the filestream is open.
	 *
	 * @return whether the filestream is open
	 */
	SIMPLECORE_API bool isOpen() const;

	/**
	 * Tries to open the filestream by parameter openMode.
	 *
	 * @param openModeFlags the openMode flags
	 * @return whether the filestream could be opened
	 */
	SIMPLECORE_API bool open(int openModeFlags = static_cast<int>(OpenMode::NotOpen));

	/**
	 * Closes the current filestream.
	 */
	SIMPLECORE_API void close();

	/**
	 * Copies member variable from another File instance.
	 */
	SIMPLECORE_API void operator=(const File& file);

	/**
	 * Writes the string from param string to file and returns the reference to std::fstream.
	 *
	 * @param string the string to write
	 * @return the reference to the std::fstream object
	 */
	SIMPLECORE_API std::fstream& operator<<(const AString& string);

	/**
	 * Appends a string to the file. This only works if flags WriteOnly and Append were set.
	 *
	 * @param string the string to write to the file
	 */
	SIMPLECORE_API void append(const AString& string);

	/**
	 * Reads the complete file to an empty string and returns it.
	 *
	 * @return the string read from file
	 */
	SIMPLECORE_API AString readAllText();

	/**
	 * Clears the filestream and writes the complete param text string to file.
	 *
	 * @param text the string to write
	 */
	SIMPLECORE_API void writeAllText(const AString& text);

	/**
	 * Reads the complete filestream in binary mode and returns a new byte array.
	 *
	 * @return the read byte array
	 */
	SIMPLECORE_API ByteArray readAllBytes();

	/**
	 * Clears the filestream and writes all bytes from param bytes to file.
	 *
	 * @param bytes the byte array to write
	 */
	SIMPLECORE_API void writeAllBytes(const ByteArray& bytes);

	/**
	 * Returns the next line to read from filestream.
	 *
	 * @return the next line to read
	 */
	SIMPLECORE_API AString readLine();

	/**
	 * Returns whether the filestream reader is at the end.
	 *
	 * @return whether the filestream is at the end
	 */
	SIMPLECORE_API bool atEnd() const;

private:
	AString filepath_;

	std::fstream fstream_;

	int openModeFlags_;

	/**
	 * Returns whether the filestream is open.
	 *
	 * @return whether the filestream is open
	 */
	bool printFileOpen() const;

	/**
	 * Returns whether the ReadOnly flag was set.
	 *
	 * @return whether the ReadOnly flag was set
	 */
	bool printFlagReadOnly() const;

	/**
	 * Returns whether the WriteOnly flag was set.
	 *
	 * @return whether the WriteOnly flag was set
	 */
	bool printFlagWriteOnly() const;
};

#endif   // FILE_H
