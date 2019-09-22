#include "inifile.h"

#include "file.h"
#include "logger.h"
#include "dir.h"
#include <filesystem>

IniFile::IniFile() :
	IniFile("")
{
}

IniFile::IniFile(const AString& filepath) :
	File(filepath),
	groupCount_(0),
	keyCount_(0)
{
	setFilepath(filepath);
	read();
}

void IniFile::setFilepath(const AString& filepath)
{
	File::setFilepath(filepath);
}

void IniFile::beginGroup(const AString& group)
{
	group_ = group;

	auto containsGroup = false;
	for (auto& tempGroup : groups_) {
		if (tempGroup.name == group) {
			containsGroup = true;
			break;
		}
	}

	if (!containsGroup) {
		Group newGroup;
		newGroup.name = group_;
		groups_.append(newGroup);
	}
}

void IniFile::deleteGroup(const AString& group)
{
	auto tempGroup = (group.isEmpty() ? group_ : group);
	for (auto it = groups_.begin(); it != groups_.end(); ++it) {
		if ((*it).name.equals(tempGroup, false)) {
			--it;
			groups_.erase(it+1);
			if (group_.equals(group, false)) {
				group_.clear();
			}
			setValue("", "");
		}
	}
}

uint IniFile::getGroupCount()
{
	return groupCount_;
}

uint IniFile::getKeyCount()
{
	return keyCount_;
}

AString IniFile::value(const AString& key, const AString& defaultValue) const
{
	if (!exists()) {
		Logger::error("Error at IniFile::value(): File does not exist: '" + getFilepath() + "'!");
		return defaultValue;
	}

	for (auto& group : groups_) {
		if (group.name.equals(group_, false)) {
			AString result = defaultValue;
			try {
				result = group.keyValues.at(key);
			}
			catch (std::exception&) {
			}
			return result;
		}
	}
	return defaultValue;
}

void IniFile::setValue(const AString& key, const AString& value)
{
	groupCount_ = 0;
	keyCount_ = 0;

	erase();
	const auto formattedValue = AString(value).trim();
	if (!open(OpenMode::WriteOnly | OpenMode::Append)) {
		Logger::error("Error at IniFile::setValue(): Cannot open file " + getFilepath());
		return;
	}

	for (auto& group : groups_) {
		writeGroup(group.name);
		++groupCount_;
		if (!key.isEmpty() && group.name.equals(group_, false)) {
			group.keyValues[key] = value;
		}

		for (auto it = group.keyValues.begin(); it != group.keyValues.end(); ++it) {
			++keyCount_;
			auto derefIt = *it;
			writeValue(derefIt.first, derefIt.second);
		}
		append("\n");
	}
	close();
}

void IniFile::read()
{
	groupCount_ = 0;
	keyCount_ = 0;

	Group group;
	auto fileContent = readAllText().split('\n');
	for (auto& line : fileContent) {
		line = line.trim();
		/* Case group */
		if (line.startsWith("[") && line.endsWith("]")) {
			if (!group.name.isEmpty()) {
				groups_.append(group);
				group = Group();
			}

			group.name = line.removeFirst('[')
				.removeFirst(']')
				.trim();
		}
		/* Case key and value */
		else if (!group.name.isEmpty() && !line.startsWith(";") && !line.startsWith("[")) {
			const auto index = line.firstIndexOf('=');
			group.keyValues[line.left(index)] = line.right(index);
			++keyCount_;
		}
		groups_.append(group);
	}
	groupCount_ = groups_.size();
}

void IniFile::writeGroup(const AString& group)
{
	append(AString("[%1]\n").arg(group));
}

void IniFile::writeValue(const AString& key, const AString& value)
{
	append(AString("%1 = %2\n").arg(key).arg(value));
}
