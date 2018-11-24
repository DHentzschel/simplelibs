#include "dir.h"

#include <ShlObj.h>
#include <Windows.h>

#include "console.h"
#include "logger.h"

/**
 * \brief Constructs instance on default.
 */
Dir::Dir() = default;

Dir::Dir(const Dir& dir) :
    path_(dir.path_),
    fileList_(dir.fileList_)
{
}

Dir::Dir(Dir&& dir) :
    Dir(dir)
{
}

/**
 * \brief Constructs instance and sets default value path.
 * \param path directory path
 */
Dir::Dir(const AString& getPath)
{
    setPath(getPath);
}

/**
 * \brief Destroys instance on default.
 */
Dir::~Dir() = default;

/**
 * \brief Returns path as string.
 * \return path
 */
AString Dir::getPath() const
{
    return path_;
}

/**
 * \brief Sets path by param and replace \\\\ by /
 * \param path absolute or relative path
 */
void Dir::setPath(const AString& path)
{
    path_.clear();

    if (path.size() > 2 && path[1] != ':') {
        path_ = Dir::getApplicationDir() + "/";
    }

    path_ += path;
    path_.replaceAll("\\", "/");
}

/**
* \brief Tries to create a directory located in path.
* Depending on overrideIfExisting, override or not.
* \param overrideIfExisting override if existings
* \return success
*/
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
            if (!static_cast<bool>(
                CreateDirectoryA(tempDirString.toCString(), nullptr))) {
                Logger::error("Couldn't create " + tempDirString);
            }
        }
    }

    auto removed = true;
    if (exists()) {
        if (!overrideIfExisting) {
            return false;
        }
        if (overrideIfExisting) {
            removed = erase(true);
        }
    }
    return removed &&
        static_cast<bool>(CreateDirectoryA(path_.toCString(), nullptr));
}

/**
* \brief Tries to create a directory located in path.
* Depending on overrideIfExisting, override or not.
* \param path directory path
* \param overrideIfExisting override if existings
* \return success
*/
bool Dir::create(const AString& getPath, const bool overrideIfExisting)
{
    return Dir(getPath).create(overrideIfExisting);
}

/**
* \brief Determines if dir located in path exists.
* \return if existing
*/
bool Dir::exists() const
{
    if (path_.isEmpty()) {
        Logger::error(AString(__FUNCTION__) + " failed, path is empty.");
    }
    const auto attributes = GetFileAttributesA(path_.c_str());
    return attributes != 0xFFFFFFFF && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

/**
 * \brief Determines if dir located in path exists.
 * \param path directory path
 * \return if existing
 */
bool Dir::exists(const AString& getPath)
{
    return Dir(getPath).exists();
}

/**
* \brief Deletes directory located in path, depending on recursively if recursively.
* \param recursively delete recursivelys
* \return success
*/
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

int64 Dir::getFileCount()
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

/**
 * \brief Deletes directory located in path, depending on recursively if recursively.
 * \param path absolute path
 * \param recursively delete recursivelys
 * \return success
 */
bool Dir::erase(const AString& getPath, const bool recursively)
{
    return Dir(getPath).erase(recursively);
}

/**
 * \brief Determines application's current path.
 * \return current app path
 */
AString Dir::getApplicationDir()
{
    char buffer[_MAX_PATH + 1];
    GetModuleFileName(nullptr, buffer, _MAX_PATH);
    auto string = AString(buffer);
    string = string.left(static_cast<uint>(string.lastIndexOf('\\')));
    return string;
}

/**
 * \brief Determines path e. g. C:\Users\Test\Desktop.
 * \return desktop path
 */
AString Dir::getDesktopDir()
{
    return getDir(CSIDL_DESKTOP);
}

/**
* \brief Determines path e. g. Start Menu\Programs.
* \return start programs path
*/
AString Dir::getStartProgramsDir()
{
    return getDir(CSIDL_PROGRAMS);
}

/**
* \brief Determines path e. g. C:\Users\Test\Favorites.
* \return favorite path
*/
AString Dir::getFavoritesDir()
{
    return getDir(CSIDL_FAVORITES);
}

/**
* \brief Determines path e. g. Start Menu\Programs\Startup.
* \return startup path
*/
AString Dir::getStartupDir()
{
    return getDir(CSIDL_STARTUP);
}

/**
* \brief Determines path e. g. C:\Users\Test\Recent.
* \return recent path
*/
AString Dir::getRecentDir()
{
    return getDir(CSIDL_RECENT);
}

/**
* \brief Determines path e. g. C:\Users\Test\SendTo.
* \return sendto path
*/
AString Dir::getSendToDir()
{
    return getDir(CSIDL_SENDTO);
}

/**
* \brief Determines path e. g. C:\Users\Test\Start Menu.
* \return start menu path
*/
AString Dir::getStartMenuDir()
{
    return getDir(CSIDL_STARTMENU);
}

/**
* \brief Determines path e. g. C:\Users\Test\Documents.
* \return documents path
*/
AString Dir::getDocumentsDir()
{
    return getDir(CSIDL_MYDOCUMENTS);
}

/**
* \brief Determines path e. g. C:\Users\Test\Music.
* \return music path
*/
AString Dir::getMusicDir()
{
    return getDir(CSIDL_MYMUSIC);
}

/**
* \brief Determines path e. g. C:\Users\Test\Videos.
* \return videos path
*/
AString Dir::getVideosDir()
{
    return getDir(CSIDL_MYVIDEO);
}

/**
* \brief Determines path e. g. C:\Users\Test\nethood.
* \return nethood path
*/
AString Dir::getNethoodDir()
{
    return getDir(CSIDL_NETHOOD);
}

/**
* \brief Determines path e. g. C:\Windows\fonts.
* \return fonts path
*/
AString Dir::getFontsDir()
{
    return getDir(CSIDL_FONTS);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Roaming\Microsoft\Windows\Templates.
* \return templates dir
*/
AString Dir::getTemplatesDir()
{
    return getDir(CSIDL_TEMPLATES);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Start Menu.
* \return common start menu path
*/
AString Dir::getCommonStartMenuDir()
{
    return getDir(CSIDL_COMMON_STARTMENU);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs.
* \return common start programs path
*/
AString Dir::getCommonStartProgramsDir()
{
    return getDir(CSIDL_COMMON_PROGRAMS);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup.
* \return common startup path
*/
AString Dir::getCommonStartupDir()
{
    return getDir(CSIDL_COMMON_STARTUP);
}

/**
* \brief Determines path e. g. C:\Users\Public\Desktop.
* \return common desktop path
*/
AString Dir::getCommonDesktopDir()
{
    return getDir(CSIDL_COMMON_DESKTOPDIRECTORY);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Roaming.
* \return appdata path
*/
AString Dir::getAppDataDir()
{
    return getDir(CSIDL_APPDATA);
}

/**
* \brief Determines path e. g. C:\Users\Test\Roaming\Microsoft\Windows\Printer Shortcuts.
* \return printhood path
*/
AString Dir::getPrintHoodDir()
{
    return getDir(CSIDL_PRINTHOOD);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Local.
* \return local appdata path
*/
AString Dir::getLocalAppDataDir()
{
    return getDir(CSIDL_LOCAL_APPDATA);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup.
* \return alt startup path
*/
AString Dir::getAltStartupDir()
{
    return getDir(CSIDL_ALTSTARTUP);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup.
* \return common alt startup path
*/
AString Dir::getCommonAltStartupDir()
{
    return getDir(CSIDL_COMMON_ALTSTARTUP);
}

/**
* \brief Determines path e. g. C:\Users\Test\Favorites.
* \return common favorites path
*/
AString Dir::getCommonFavoritesDir()
{
    return getDir(CSIDL_COMMON_FAVORITES);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Local\Microsoft\Windows\INetCache.
* \return internet cache path
*/
AString Dir::getInternetCacheDir()
{
    return getDir(CSIDL_INTERNET_CACHE);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Local\Microsoft\Windows\INetCookies.
* \return cookies path
*/
AString Dir::getCookiesDir()
{
    return getDir(CSIDL_COOKIES);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Local\Microsoft\Windows\History.
* \return history path
*/
AString Dir::getHistoryDir()
{
    return getDir(CSIDL_HISTORY);
}

/**
* \brief Determines path e. g. C:\ProgramData.
* \return common appdata or programdata path
*/
AString Dir::getCommonAppDataDir()
{
    return getDir(CSIDL_COMMON_APPDATA);
}

/**
* \brief Determines path e. g. C:\Windows.
* \return windows path
*/
AString Dir::getWindowsDir()
{
    return getDir(CSIDL_WINDOWS);
}

/**
* \brief Determines path e. g. C:\Windows\system32.
* \return system path
*/
AString Dir::getSystemDir()
{
    return getDir(CSIDL_SYSTEM);
}

/**
* \brief Determines path e. g. C:\Program Files.
* \return program files path
*/
AString Dir::getProgramFilesDir()
{
    return getDir(CSIDL_PROGRAM_FILES);
}

/**
* \brief Determines path e. g. C:\Users\Test\Pictures.
* \return pictures path
*/
AString Dir::getPicturesDir()
{
    return getDir(CSIDL_MYPICTURES);
}

/**
* \brief Determines path e. g. C:\Users\Test.
* \return profile path
*/
AString Dir::getProfileDir()
{
    return getDir(CSIDL_PROFILE);
}

/**
* \brief Determines path e. g. C:\Windows\SysWOW64.
* \return system x86 path
*/
AString Dir::getSystemx86Dir()
{
    return getDir(CSIDL_SYSTEMX86);
}

/**
* \brief Determines path e. g. C:\Program Files (x86).
* \return program files x86 path
*/
AString Dir::getProgramFilesx86Dir()
{
    return getDir(CSIDL_PROGRAM_FILESX86);
}

/**
* \brief Determines path e. g. C:\Program Files\Common Files.
* \return common program files path
*/
AString Dir::getProgramFilesCommonDir()
{
    return getDir(CSIDL_PROGRAM_FILES_COMMON);
}

/**
* \brief Determines path e. g. C:\Program Files (x86)\Common Files.
* \return common program files x86 path
*/
AString Dir::getProgramFilesx86CommonDir()
{
    return getDir(CSIDL_PROGRAM_FILES_COMMONX86);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Templates.
* \return common templates path
*/
AString Dir::getCommonTemplatesDir()
{
    return getDir(CSIDL_COMMON_TEMPLATES);
}

/**
* \brief Determines path e. g. C:\Users\Public\Documents.
* \return common documents path
*/
AString Dir::getCommonDocumentsDir()
{
    return getDir(CSIDL_COMMON_DOCUMENTS);
}

/**
* \brief Determines path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Administrative Tools.
* \return common admin tools path
*/
AString Dir::getCommonAdminToolsDir()
{
    return getDir(CSIDL_COMMON_ADMINTOOLS);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Administrative Tools.
* \return admin tools path
*/
AString Dir::getAdminToolsDir()
{
    return getDir(CSIDL_ADMINTOOLS);
}

/**
* \brief Determines path e. g. C:\Users\Public\Music.
* \return common music path
*/
AString Dir::getCommonMusicDir()
{
    return getDir(CSIDL_COMMON_MUSIC);
}

/**
* \brief Determines path e. g. C:\Users\Public\Pictures.
* \return common pictures path
*/
AString Dir::getCommonPicturesDir()
{
    return getDir(CSIDL_COMMON_PICTURES);
}

/**
* \brief Determines path e. g. C:\Users\Public\videos.
* \return common videos path
*/
AString Dir::getCommonVideosDir()
{
    return getDir(CSIDL_COMMON_VIDEO);
}

/**
* \brief Determines path e. g. C:\Windows\resources.
* \return resources path
*/
AString Dir::getResourcesDir()
{
    return getDir(CSIDL_RESOURCES);
}

/**
* \brief Determines path e. g. C:\Users\Test\AppData\Local\Microsoft\Windows\Burn\Burn.
* \return cd burn area path
*/
AString Dir::getCdBurnAreaDir()
{
    return getDir(CSIDL_CDBURN_AREA);
}

/**
 * \brief Determines path by WINAPI macro with prefix CSIDL_ as int.
 * \param directoryId macro with prefix CSIDL_ as int.
 * \return full path
 */
AString Dir::getDir(const int directoryId)
{
    char buffer_[_MAX_PATH + 1];
    SHGetFolderPath(nullptr, directoryId, nullptr, 0, buffer_);
    return AString(buffer_);
}
