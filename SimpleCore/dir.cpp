#include "dir.h"

#include <ShlObj.h>
#include <Windows.h>

#include "console.h"
#include "logger.h"

Dir::Dir(const Dir& dir) :
	path_(dir.path_),
	fileList_(dir.fileList_)
{}

Dir::Dir(const AString& path) noexcept
{
	setPath(path);
}

AString Dir::getPath() const
{
	return path_;
}

void Dir::setPath(const AString& path)
{
	path_.clear();

	if (path.size() > 2 && path[1] != ':') {
		path_ = Dir::getDir(Directory::CurrentApplication) + "/";
	}

	path_ += path;
	path_.replaceAll("\\", "/");
}

bool Dir::create(const bool overrideIfExisting) const
{
	auto dirParts = path_.split('/');
	AString tempDirString;
	for (auto& part : dirParts) {
		if (path_.endsWith(part)) {
			break;
		}

		tempDirString += part + "/";
		if (part.size() >= 2 && part[1] == ':') {
			continue;
		}
		auto tempDir = Dir(tempDirString);
		if (!tempDir.exists()) {
			if (!static_cast<bool>(CreateDirectoryA(tempDirString.toCString(), nullptr))) {
				Logger::error("Couldn't create " + tempDirString);
			}
			return true;
		}
	}

	auto removed = true;
	if (exists()) {
		if (!overrideIfExisting) {
			return false;
		}
		removed = erase(true);
	}
	return removed && static_cast<bool>(CreateDirectoryA(path_.toCString(), nullptr));
}

bool Dir::create(const AString & getPath, const bool overrideIfExisting)
{
	return Dir(getPath).create(overrideIfExisting);
}

bool Dir::exists() const
{
	if (path_.isEmpty()) {
		Logger::error(AString(__FUNCTION__) + " failed, path is empty.");
	}
	const auto attributes = GetFileAttributesA(path_.c_str());
	return attributes != 0xFFFFFFFF && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

bool Dir::exists(const AString & path)
{
	return Dir(path).exists();
}

bool Dir::erase(const bool recursively) const
{
	if (recursively) {
		const auto length = path_.size() + 2;

		AVector<char> str;
		str.resize(length);

		const auto* cstr = path_.toCString();
		for (uint i = 0; i < length - 2; ++i) {
			str[i] = cstr[i];
		}

		SHFILEOPSTRUCT fileOp = { nullptr, FO_DELETE, str.data(), "", FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT,
								  false, nullptr, "" };
		return !SHFileOperationA(&fileOp);
	}
	return RemoveDirectoryA(path_.c_str());
}

bool Dir::erase(const AString & path, const bool recursively)
{
	return Dir(path).erase(recursively);
}

int64 Dir::getFileCount() const
{
	using std::filesystem::directory_iterator;
	return std::distance(directory_iterator(std::string(path_)), directory_iterator{});
}

const AVector<std::filesystem::directory_entry>& Dir::getFiles()
{
	if (fileList_.size() != 0) {
		return fileList_;
	}
	for (const auto& file : std::filesystem::directory_iterator(std::string(path_))) {
		fileList_.append(file);
	}
	return fileList_;
}

AString Dir::getDir(Directory directory)
{
	char buffer[_MAX_PATH + 1];
	if (directory == Directory::CurrentApplication) {
		GetModuleFileName(nullptr, buffer, _MAX_PATH);
		auto string = AString(buffer);
		string = string.left(static_cast<uint>(string.lastIndexOf('\\')));
		return string;
	}
	SHGetFolderPath(nullptr, static_cast<int>(directory), nullptr, 0, buffer);
	return AString(buffer);
}
