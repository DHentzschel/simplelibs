#ifndef FILE_H
#define FILE_H

#include <fstream>

#include "astring.h"
#include "avector.h"
#include "openmode.h"

/**
 * @author Daniel Hentzschel on 11.05.2019.
 */
class File {
public:
	/**
	 * Sets the openMode to NotOpen on default.
	 */
	File();

	/**
	 * Copies the openMode and file path from the given parameter.
	 *
	 * @param file the copyable object
	 */
	File(const File& file);

	/**
	 * Sets the filepath to the parameter and sets the openMode to NotOpen on default.
	 *
	 * @param filepath the filepath to use
	 */
	explicit File(const AString& filename) noexcept;

	/**
	 * Closes the current filestream if opened.
	 */
	~File();

	/**
	* Tries to create the current filepath.
	*
	* @param recursively if not existing, subfolders should be created
	* @return if the filepath could be created
	*/
	bool create(bool recursively = true) const;

	/**
	* Tries to create the filepath given as parameter.
	*
	* @param filepath the filepath to create
	* @param recursively if not existing, subfolders should be created
	* @return if the file path could be created
	*/
	static bool create(const AString& filepath, bool recursively = true);

	/**
	 * Tries to erase the file in filepath and returns the success.
	 *
	 * @return either the file has been erased or not
	 */
	bool erase() const;

	/**
	 * Tries to erase the file in filepath given as parameter and returns the success.
	 *
	 * @param filepath the filepath to erase
	 * @return either the file has been erased or not
	 */
	static bool erase(const AString& filepath);

	/**
	 * Returns either the current filepath exists.
	 *
	 * @return either the current filepath set exists
	 */
	bool exists() const;

	/**
	 * Returns either the filepath given as parameter exists.
	 *
	 * @param filepath the filepath to check for existence
	 * @return either the given filepath exists
	 */
	static bool exists(const AString& filepath);

	/**
	 * Returns the directory of the filepath.
	 * Example: C:\Users\user\test.dat turns to C:\Users\user
	 *
	 * @return the directory of the current filepath
	 */
	AString getDirectory() const;

	/**
	 * Returns the filename of the filepath.
	 * Example: C:\Users\user\test.dat turns to test.dat
	 *
	 * @return the filename of the current filepath
	 */
	AString getFilename() const;

	/**
	 * Returns the current filepath set.
	 *
	 * @return the current filepath
	 */
	AString getFilepath() const;

	/**
	 * Sets the filepath for the next filestream.
	 *
	 * @param filepath the filepath for the filestream
	 */
	void setFilepath(const AString& filepath);

	/**
	 * Returns either the filestream is open.
	 *
	 * @return either the filestream is open
	 */
	bool isOpen() const;

	/**
	 * Tries to open the filestream by parameter openMode.
	 *
	 * @param openMode the openMode flags
	 * @return either the filestream could be opened
	 */
	bool open(int openModeFlags = static_cast<int>(OpenMode::NotOpen));

	/**
	 * Closes the current filestream.
	 */
	void close();

	/**
	 * Copies member variable from another File instance.
	 */
	void operator=(const File& file);

	/**
	 * Writes the string from param string to file and returns the reference to std::fstream.
	 *
	 * @param string the string to write
	 * @return the reference to the std::fstream object
	 */
	std::fstream& operator<<(const AString& string);

	/**
	 * Appends a string to the file. This only works if flags WriteOnly and Append were set.
	 *
	 * @param string the string to write to the file
	 */
	void append(const AString& string);

	/**
	 * Reads the complete file to an empty string and returns it.
	 *
	 * @return the string read from file
	 */
	AString readAllText();

	/**
	 * Clears the filestream and writes the complete param text string to file.
	 *
	 * @param text the string to write
	 */
	void writeAllText(const AString& text);

	/**
	 * Reads the complete filestream in binary mode and returns a new byte array.
	 *
	 * @return the read byte array
	 */
	ByteArray readAllBytes();

	/**
	 * Clears the filestream and writes all bytes from param bytes to file.
	 *
	 * @param bytes the byte array to write
	 */
	void writeAllBytes(const ByteArray& bytes);

	/**
	 * Returns the next line to read from filestream.
	 *
	 * @return the next line to read
	 */
	AString readLine();

	/**
	 * Returns either the filestream reader is at the end.
	 *
	 * @return either the filestream is at the end
	 */
	bool atEnd() const;

private:
	AString filepath_;

	std::fstream fstream_;

	int openModeFlags_;

	/**
	 * Returns either the filestream is open.
	 *
	 * @return either the filestream is open
	 */
	bool printFileOpen() const;

	/**
	 * Returns either the ReadOnly flag was set.
	 *
	 * @return either the ReadOnly flag was set
	 */
	bool printFlagReadOnly() const;

	/**
	 * Returns either the WriteOnly flag was set.
	 *
	 * @return either the WriteOnly flag was set
	 */
	bool printFlagWriteOnly() const;
};

#endif   // FILE_H
