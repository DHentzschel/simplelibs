#ifndef DIR_H
#define DIR_H

#include <filesystem>

#include "astring.h"
#include "avector.h"

class Dir {
public:
    Dir();

    Dir(const Dir& dir);

    explicit Dir(const AString& getPath) noexcept;

    ~Dir();

    AString getPath() const;

    void setPath(const AString& path);

    bool create(bool overrideIfExisting = false) const;

    static bool create(const AString& getPath, bool overrideIfExisting = false);

    bool exists() const;

    static bool exists(const AString& getPath);

    bool erase(bool recursively = true) const;

    int64 getFileCount();

    void operator=(const Dir& right);

    const AVector<std::filesystem::directory_entry>& getFiles();

    static bool erase(const AString& getPath, bool recursively = true);

    static AString getApplicationDir();

    static AString getDesktopDir();

    static AString getStartProgramsDir();

    static AString getFavoritesDir();

    static AString getStartupDir();

    static AString getRecentDir();

    static AString getSendToDir();

    static AString getStartMenuDir();

    static AString getDocumentsDir();

    static AString getMusicDir();

    static AString getVideosDir();

    static AString getNethoodDir();

    static AString getFontsDir();

    static AString getTemplatesDir();

    static AString getCommonStartMenuDir();

    static AString getCommonStartProgramsDir();

    static AString getCommonStartupDir();

    static AString getCommonDesktopDir();

    static AString getAppDataDir();

    static AString getPrintHoodDir();

    static AString getLocalAppDataDir();

    static AString getAltStartupDir();

    static AString getCommonAltStartupDir();

    static AString getCommonFavoritesDir();

    static AString getInternetCacheDir();

    static AString getCookiesDir();

    static AString getHistoryDir();

    static AString getCommonAppDataDir();

    static AString getWindowsDir();

    static AString getSystemDir();

    static AString getProgramFilesDir();

    static AString getPicturesDir();

    static AString getProfileDir();

    static AString getSystemx86Dir();

    static AString getProgramFilesx86Dir();

    static AString getProgramFilesCommonDir();

    static AString getProgramFilesx86CommonDir();

    static AString getCommonTemplatesDir();

    static AString getCommonDocumentsDir();

    static AString getCommonAdminToolsDir();

    static AString getAdminToolsDir();

    static AString getCommonMusicDir();

    static AString getCommonPicturesDir();

    static AString getCommonVideosDir();

    static AString getResourcesDir();

    static AString getCdBurnAreaDir();

private:
    AString path_;

    AVector<std::filesystem::directory_entry> fileList_;

    static AString getDir(int directoryId);
};

#endif   // DIR_H
