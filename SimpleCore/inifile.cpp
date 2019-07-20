#include "inifile.h"

#include <Windows.h>
#include "file.h"
#include "logger.h"
#include "dir.h"
#include <filesystem>

IniFile::IniFile() :
	groupCount_(0),
	keyCount_(0)
{
}

IniFile::IniFile(const AString& filepath) :
	IniFile()
{
	setFilepath(filepath);
}

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

void IniFile::beginGroup(const AString& group)
{
	group_ = group;
}

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

AString IniFile::value(const AString& key) const
{
	if (!File::exists(filepath_)) {
		Logger::error("Error at IniFile::value(): File does not exist: '" + filepath_ + "'!");
	}

	AVector<char> buffer;
	buffer.resize(0xFF);
	GetPrivateProfileStringA(group_.toCString(), key.toCString(), "empty",
		buffer.data(), static_cast<DWORD>(buffer.size()),
		filepath_.toCString());
	return AString(buffer.data());
}

void IniFile::setValue(const AString & key, const AString & value) const
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
