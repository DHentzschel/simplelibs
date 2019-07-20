#ifndef DIR_H
#define DIR_H

#include <filesystem>

#include "simplecore.h"
#include "astring.h"
#include "avector.h"
#include "directory.h"

/**
 * Provides simple functions to create, modify, erase etc. directories.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class Dir {
public:
	/**
	 * Provides the default constructor.
	 */
	SIMPLECORE_API Dir() = default;

	/**
	 * Copies the values from the specified Dir instance.
	 *
	 * @param dir the Dir instance to copy from
	 */
	SIMPLECORE_API Dir(const Dir& dir);

	/**
	 * Sets the default value path.
	 *
	 * @param path the directory path
	 */
	SIMPLECORE_API explicit Dir(const AString& path) noexcept;

	/**
	 * Returns the directory path as string.
	 *
	 * @return path the directory path
	 */
	SIMPLECORE_API AString getPath() const;

	/**
	 * Sets the path by parameter and replaces \\ by /
	 *
	 * @param path the absolute or relative path
	 */
	SIMPLECORE_API void setPath(const AString& path);

	/**
	 * Tries to create the directory in path variable set.
	 * Depending on parameter overrideIfExisting, the directory will be overridden or not.
	 *
	 * @param overrideIfExisting override if the folder exists
	 * @return if the directory could get created
	 */
	SIMPLECORE_API bool create(bool overrideIfExisting = false) const;

	/**
	 * Tries to create the directory in path variable set.
	 * Depending on parameter overrideIfExisting, the directory will be overridden or not.
	 *
	 * @param path the path to create
	 * @param overrideIfExisting override if the folder exists
	 * @return if the directory could get created
	 */
	SIMPLECORE_API static bool create(const AString& path, bool overrideIfExisting = false);

	/**
	 * Returns if the directory located in the path exists.
	 *
	 * @return if the directory exists
	 */
	SIMPLECORE_API bool exists() const;

	/**
	 * Returns if the directory located in the path exists.
	 *
	 * @param path the directory path
	 * @return if the directory exists
	 */
	SIMPLECORE_API static bool exists(const AString& path);

	/**
	 * Erases the directory located in the path, depending on recursively if recursively.
	 *
	 * @param recursively if the directory should be erased recursively
	 * @return if the directory could be erased
	 */
	SIMPLECORE_API bool erase(bool recursively = true) const;

	/**
	 * Erases the directory located in the path, depending on recursively if recursively.
	 *
	 * @param path the directory to erase
	 * @param recursively if the directory should be erased recursively
	 * @return if the directory could be erased
	 */
	SIMPLECORE_API static bool erase(const AString& path, bool recursively = true);

	/**
	 * Returns the count of the files inside the directory.
	 *
	 * @return the count of files inside the directory
	 */
	SIMPLECORE_API int64 getFileCount() const;

	/**
	 * Returns a list of filenames inside the directory.
	 *
	 * @return a list of filenames inside the directory
	 */
	SIMPLECORE_API const AVector<std::filesystem::directory_entry>& getFiles();

	/**
	 * Returns the path by directoy type.
	 *
	 * @param directory the enum of the directory type
	 * @return the full path
	 */
	SIMPLECORE_API static AString getDir(Directory directory);
private:
	/** Represents the path to work with */
	AString path_;

	/** Contains a list of files inside the current directory */
	AVector<std::filesystem::directory_entry> fileList_;
};

#endif   // DIR_H
