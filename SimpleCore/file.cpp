#include "file.h"

#include <cstdio>
#include <sstream>

#include "console.h"
#include "dir.h"
#include "logger.h"

/**
 * \brief Constructs instance by setting openMode param to default NotOpen.
 */
File::File() :
    openMode_(NotOpen)
{}

/**
 * \brief Constructs instance by setting params for filepath (passed by param) and openMode(NotOpen)
 * \param filepath filepath to use
 */
File::File(const AString& filepath) :
    filepath_(filepath),
    openMode_(NotOpen)
{
    filepath_.replaceAll("\\", "/");
}

/**
 * \brief Destroys instance after closing current filestream.
 */
File::~File()
{
    close();
}

/**
* \brief Tries to create current filepath.
* \param recursively if not existing subfolders should be created
* \return success
*/
bool File::create(const bool recursively) const
{
    auto dir = Dir(getDirectory());

    auto result = true;
    if (!dir.exists()) {
        result = dir.create();
    }

    std::ofstream outfile(filepath_);
    outfile << "";
    outfile.close();
    return result && outfile.good();
}

/**
 * \brief Tries to create a filepath passed by param filepath.
 * \param filepath filepath to create
 * \param recursively if not existing subfolders should be created
 * \return success
 */
bool File::create(const AString& filepath, const bool recursively)
{
    return File(filepath).create(recursively);
}

/**
 * \brief Tries to delte file in filepath and returns success.
 * \return success
 */
bool File::erase() const
{
    return remove(filepath_.toCString());
}

/**
 * \brief Tries to delete file in filepath passed by param and returns success.
 * \param filepath filepath
 * \return success
 */
bool File::erase(const AString& filepath)
{
    return File(filepath).erase();
}

/**
 * \brief Returns if current filepath exists.
 * \return if filepath exists
 */
bool File::exists() const
{
    std::ifstream infile(filepath_);
    return infile.good();
}

/**
 * \brief Returns if file in filepath passed by param filepath exists.
 * \param filepath to test if it exists
 * \return if filepath exists
 */
bool File::exists(const AString& filepath)
{
    return File(filepath).exists();
}

/**
 * \brief Returns file path's directory.
 * \return directory
 */
AString File::getDirectory() const
{
    if (filepath_.count("/") == 0 && filepath_.count("\\") == 0) {
        return Dir::getApplicationDir() + filepath_;
    }

    // TODO: Return absolute directory from relative
    auto lastIndexOfSlash = filepath_.lastIndexOf('/');

    if (lastIndexOfSlash == STATIC_CAST(uint64, -1)) {
        return AString();
    }

    auto copy = filepath_;
    copy.erase(STATIC_CAST(size_t, lastIndexOfSlash), copy.size() - 1);
    return copy;
}

AString File::getFilename() const
{
    auto lastIndexOfSlash = filepath_.lastIndexOf('/');
    if (lastIndexOfSlash == -1) {
        lastIndexOfSlash = filepath_.lastIndexOf('\\');
    }

    auto copy = filepath_;
    copy.erase(0, STATIC_CAST(size_t, lastIndexOfSlash) + 1);
    return copy;
}

/**
 * \brief Returns current filepath set.
 * \return filepath
 */
AString File::getFilepath() const
{
    return filepath_;
}

/**
 * \brief Sets file path for the next filestream.
 * \param filepath filepath for filestream
 */
void File::setFilePath(const AString& filepath)
{
    filepath_ = filepath;
    filepath_.replaceAll("\\", "/");
}

/**
 * \brief Returns if filestream is open.
 * \return if filestream is open
 */
bool File::isOpen() const
{
    return fstream_.is_open();
}

/**
 * \brief Tries to open filestream by param openMode.
 * \param openMode OpenMode flags
 * \return success
 */
bool File::open(const int openMode)
{
    auto result = true;
    if (!exists()) {
        result = create();
    }
    if (filepath_.isEmpty()) {
        return false;
    }
    fstream_.open(filepath_.toCString(), openMode_ = openMode);
    return result && isOpen();
}

/**
 * \brief Closes current filestream.
 */
void File::close()
{
    fstream_.close();
}

/**
 * \brief Writes string from param string to file and returns std::fstream.
 * \param string string to write
 * \return std::fstream instance
 */
std::fstream& File::operator<<(const AString& string)
{
    if (!printFileOpen()) {
        return fstream_;
    }
    if (!printFlagWriteOnly()) {
        return fstream_;
    }
    if (openMode_ & NewOnly && exists()) {
        Logger::error("Failed to write to file, Flag NewOnly was set.");
        return fstream_;
    }
    if (openMode_ & ExistingOnly && !exists()) {
        Logger::error("Failed to write to file, Flag NewOnly was set.");
        return fstream_;
    }

    fstream_ << string.toCString();
    fstream_.flush();
    return fstream_;
}

/**
 * \brief Appends string to file. Only works if flags WriteOnly and Append were set.
 * \param string string to write
 */
void File::append(const AString& string)
{
    if (!printFileOpen()) {
        return;
    }
    if (!printFlagWriteOnly()) {
        return;
    }

    if (!(openMode_ & Append)) {
        Logger::error("Failed writing to file '" + filepath_ +
            "'. Flag Append was not set.");
        return;
    }

    fstream_ << string.toCString();
    fstream_.flush();
}

/**
 * \brief Reads complete file to string and returns it.
 * \return read string
 */
AString File::readAllText()
{
    if (isOpen()) {
        close();
    }
    open(ReadOnly);
    std::stringstream stringstream;
    stringstream << fstream_.rdbuf();
    return AString(stringstream.str());
}

/**
 * \brief Clears filestream and writes complete param text string to file.
 * \param text string to write
 */
void File::writeAllText(const AString& text)
{
    if (isOpen()) {
        close();
    }
    if (!open(WriteOnly)) {
        Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
        return;
    }
    fstream_ << text.toCString();
    fstream_.flush();
}

/**
 * \brief Reads complete filestream in binary and returns new vector.
 * \return byte array
 */
AVector<char> File::readAllBytes()
{
    if (isOpen()) {
        close();
    }
    if (!open(ReadOnly | Binary | AtTheEnd)) {
        Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
        return AVector<char>();
    }
    const size_t pos = STATIC_CAST(size_t, fstream_.tellg());
    AVector<char> result(pos);

    fstream_.seekg(0, std::ios::beg);
    fstream_.read(&result[0], pos);

    return result;
}

/**
 * \brief Clears filestream and writes all bytes existing in param bytes.
 * \param bytes byte array
 */
void File::writeAllBytes(const AVector<char>& bytes)
{
    if (isOpen()) {
        close();
    }
    if (!open(WriteOnly | Binary)) {
        Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
        return;
    }
    fstream_.write(bytes.data(), bytes.size());
    fstream_.close();
}

/**
 * \brief Returns next read line from filestream.
 * \return next read line
 */
AString File::readLine()
{
    if (!printFileOpen()) {
        return "empty";
    }
    if (!printFlagReadOnly()) {
        return "empty";
    }
    AString temp;
    std::getline(fstream_, temp);
    return temp;
}

/**
 * \brief Determines if filestream reader is at the end.
 * \return if at end
 */
bool File::atEnd() const
{
    return isOpen() && fstream_.eof();
}

/**
 * \brief Determines if filestream is open.
 * \return if filestream is open
 */
bool File::printFileOpen() const
{
    if (!isOpen()) {
        Logger::error("Couldn't write to file '" + filepath_ +
            "'. File stream is not opened.");
        return false;
    }
    return true;
}

/**
 * \brief Determines if flag ReadOnly was set.
 * \return if flag ReadOnly was set
 */
bool File::printFlagReadOnly() const
{
    if (!(openMode_ & ReadOnly)) {
        Logger::error("Failed writing to file '" + filepath_ +
            "'. Flag ReadOnly was not set.");
        return false;
    }
    return true;
}

/**
 * \brief Determines if flag WriteOnly was set.
 * \return if flag WriteOnly was set
 */
bool File::printFlagWriteOnly() const
{
    if (!(openMode_ & WriteOnly)) {
        Logger::error("Failed writing to file '" + filepath_ +
            "'. Flag WriteOnly was not set.");
        return false;
    }
    return true;
}
