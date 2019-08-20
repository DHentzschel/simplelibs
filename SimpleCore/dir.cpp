#include "dir.h"

#include "osdetection.h"
#include <filesystem>
#ifdef OS_WIN
#  include <ShlObj.h>
#  include <Windows.h>
#elif defined OS_LINUX || defined OS_UNIX
#  include <unistd.h>
#  include <limits.h>
#  include <sys/stat.h>
#  include <dirent.h> 
#  include <pwd.h>
#endif // OS_LINUX || OS_UNIX

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
	auto created = false;
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
			bool result = false;
#ifdef OS_WIN
			result = static_cast<bool>(CreateDirectoryA(tempDirString.toCString(), nullptr));
#elif defined OS_LINUX || defined OS_UNIX
			result = mkdir(tempDirString.toCString(),
				S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1;
#endif // OS_LINUX || OS_UNIX
			if (!result) {
				Logger::error("Couldn't create " + tempDirString);
				return false;
			}
		}
	}

	auto removed = true;
	if (exists()) {
		if (!overrideIfExisting) {
			return false;
		}
		removed = erase(true);
	}

	bool result = false;
	if (!created) {
#ifdef OS_WIN
		result = static_cast<bool>(CreateDirectoryA(path_.toCString(), nullptr));
#elif defined OS_LINUX || defined OS_UNIX
		result = mkdir(tempDirString.toCString(),
			S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1;
#endif // OS_LINUX || defined OS_UNIX
	}
	return created || (removed && result);
}

bool Dir::create(const AString& getPath, const bool overrideIfExisting)
{
	return Dir(getPath).create(overrideIfExisting);
}

bool Dir::exists() const
{
#ifdef OS_WIN
	const auto attributes = GetFileAttributesA(path_.toCString());
	return attributes != 0xFFFFFFFF && (attributes & FILE_ATTRIBUTE_DIRECTORY);
#elif defined OS_LINUX
	DIR* dir = opendir(path_.toCString());
	return dir != nullptr;
#endif // OS_LINUX
}

bool Dir::exists(const AString& path)
{
	return Dir(path).exists();
}

bool Dir::erase(const bool recursively) const
{
	if (recursively) {
		return std::filesystem::remove_all(path_.toStdString()) > 0;
	}
	return std::filesystem::remove(path_.toStdString());
}

bool Dir::erase(const AString& path, const bool recursively)
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
#ifdef OS_WIN
	char buffer[_MAX_PATH + 1];
	if (directory == Directory::CurrentApplication) {
		GetModuleFileName(nullptr, buffer, _MAX_PATH);
		auto string = AString(buffer);
		string = string.left(static_cast<uint>(string.lastIndexOf('\\')));
		return string;
	}
	SHGetFolderPath(nullptr, static_cast<int>(directory), nullptr, 0, buffer);
	return AString(buffer);
#elif defined OS_LINUX || defined OS_UNIX
	char buffer[PATH_MAX];
	if (directory == Directory::CurrentApplication) {
		auto result = getcwd(buffer, sizeof buffer);
		if (result != nullptr) {
			return buffer;
		}
	} 
	else if (directory == Directory::Desktop) {
		passwd* tempPasswd = getpwuid(getuid());
		return tempPasswd->pw_dir;
	}

	return AString();
#endif // OS_LINUX || OS_UNIX
}
