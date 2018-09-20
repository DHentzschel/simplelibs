#include "inifile.h"

#include <Windows.h>
#include "file.h"
#include "logger.h"
#include "dir.h"
#include <filesystem>

/**
 * \brief Constructs instance by setting filepath to passed param.
 * \param filepath filepath to ini file
 */
IniFile::IniFile(const AString& filepath)
{
    setFilepath(filepath);
}

/**
 * \brief Sets filepath to passed param.
 * \param filepath filepath to ini file
 */
void IniFile::setFilepath(const AString& filepath)
{
    if (filepath.size() > 1 && filepath[1] != ':') {
        filepath_ = std::filesystem::current_path().string() + "\\" + filepath;
    }
    else {
        filepath_ = filepath;
    }
    fileContent_ = File(filepath_).readAllText().split('\n');
    calculateGroupCount();
    calculateKeyCount();
}

/**
 * \brief Begins new ini group by setting group to passed param.
 * \param group ini group
 */
void IniFile::beginGroup(const AString& group)
{
    group_ = group;
}

/**
 * \brief Ends current ini group by resetting to empty string.
 */
void IniFile::endGroup()
{
    group_.clear();
}

uint IniFile::getGroupCount()
{
    return groupCount_;
}

uint IniFile::getKeyCount()
{
    return keyCount_;
}

/**
 * \brief Tries to read ini value by key param.
 * Returns "empty" if key not existing or empty.
 * \param key ini key
 * \return ini value
 */
AString IniFile::value(const AString& key) const
{
    if (!File::exists(filepath_)) {
        Logger::error("Error at IniFile::value(): File does not exist: '" + filepath_ + "'!");
    }

    AVector<char> buffer_;
    buffer_.resize(0xFF);
    GetPrivateProfileStringA(group_.toCString(), key.toCString(), "empty",
        buffer_.data(), static_cast<DWORD>(buffer_.size()),
        filepath_.toCString());
    return AString(buffer_.data());
}

/**
 * \brief Sets value of key passed by key param to value passed by value param.
 * \param key ini key
 * \param value ini value
 */
void IniFile::setValue(const AString& key, const AString& value) const
{
    const AString formattedValue = value.startsWith(" ") ? AString(value) : " " + AString(value);
    WritePrivateProfileStringA(group_.toCString(), key.toCString(),
        formattedValue.toCString(), filepath_.toCString());
}

void IniFile::calculateGroupCount()
{
    uint counter = 0;
    for (auto& line : fileContent_) {
        if (line.startsWith("[")) {
            ++counter;
        }
    }
    groupCount_ = counter;
}

void IniFile::calculateKeyCount()
{
    uint counter = 0;
    for (auto& line : fileContent_) {
        if (!line.startsWith("[") && !line.startsWith(";")) {
            ++counter;
        }
    }
    keyCount_ = counter;
}
