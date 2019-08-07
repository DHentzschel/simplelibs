#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <ShlObj.h>

/**
 * Provides enum directory types from Windows operating system.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
#ifdef OS_WIN
enum class Directory {
	/** The current directory of the executable */
	CurrentApplication = -1,

	/** The desktop path of the user e. g. C:\User\user\Desktop */
	Desktop = CSIDL_DESKTOP,

	/** The start programs path e. g. Start Menu\Programs */
	StartPrograms = CSIDL_PROGRAMS,

	/** The favorites path of the user e. g. C:\User\user\Favorites */
	Favorites = CSIDL_FAVORITES,

	/** The startup directory of the start menu e. g. Start Menu\Programs\Startup */
	Startup = CSIDL_STARTUP,

	/** The recent directory of the user C:\Users\user\Recent */
	Recent = CSIDL_RECENT,

	/** The SendTo path of the user e. g. C:\Users\user\SendTo */
	SendTo = CSIDL_SENDTO,

	/** The start menu path of the user e. g. C:\Users\user\Start Menu */
	StartMenu = CSIDL_STARTMENU,

	/** The documents path of the user e. g. C:\Users\user\Documents */
	Documents = CSIDL_MYDOCUMENTS,

	/** The music path of the user e. g. C:\Users\user\Music */
	Music = CSIDL_MYMUSIC,

	/** The videos path of the user e. g. C:\Users\user\Videos */
	Videos = CSIDL_MYVIDEO,

	/** The nethood path of the user e. g. C:\Users\user\nethood */
	Nethood = CSIDL_NETHOOD,

	/** The fonts path of the operating system e. g. C:\Windows\fonts */
	Fonts = CSIDL_FONTS,

	/** The templates path of the user e. g. C:\Users\user\AppData\Roaming\Microsoft\Windows\Templates */
	Templates = CSIDL_TEMPLATES,

	/** The common start menu path e. g. C:\ProgramData\Microsoft\Windows\Start Menu */
	CommonStartMenu = CSIDL_COMMON_STARTMENU,

	/** The common start programs path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs */
	CommonStartPrograms = CSIDL_COMMON_PROGRAMS,

	/** The common startup path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup */
	CommonStartup = CSIDL_COMMON_STARTUP,

	/** The common desktop path e. g. C:\Users\Public\Desktop */
	CommonDesktop = CSIDL_COMMON_DESKTOPDIRECTORY,

	/** The application data path of the user e. g. C:\Users\user\AppData\Roaming */
	AppData = CSIDL_APPDATA,

	/** The printhood path of the user e. g. C:\Users\user\Roaming\Microsoft\Windows\Printer Shortcuts */
	Printhood = CSIDL_PRINTHOOD,

	/** The local app data path of the user e. g. C:\Users\user\AppData\Local */
	LocalAppData = CSIDL_LOCAL_APPDATA,

	/** The alt startup path e. g.
	 * C:\Users\user\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup */
	AltStartup = CSIDL_ALTSTARTUP,

	/** The common alt startup path e. g. C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup */
	CommonAltStartup = CSIDL_COMMON_ALTSTARTUP,

	/** The common favorites path e. g. C:\Users\Public\Favorites */
	CommonFavorites = CSIDL_COMMON_FAVORITES,

	/** The internet cache path of the user e. g.
	 * C:\Users\user\AppData\Local\Microsoft\Windows\INetCache */
	InternetCache = CSIDL_INTERNET_CACHE,

	/** The cookies path of the user e. g.
	 * C:\Users\user\AppData\Local\Microsoft\Windows\INetCookies */
	Cookies = CSIDL_COOKIES,

	/** The history path of the user e. g. C:\Users\user\AppData\Local\Microsoft\Windows\History */
	History = CSIDL_HISTORY,

	/** The common app data path e. g. C:\ProgramData */
	CommonAppData = CSIDL_COMMON_APPDATA,

	/** The path of the operating system e. g. C:\Windows */
	Windows = CSIDL_WINDOWS,

	/** The system32 path of the operating system e. g. C:\Windows\system32 */
	System32 = CSIDL_SYSTEM,

	/** The program files path e. g. C:\Program Files */
	ProgramFiles = CSIDL_PROGRAM_FILES,

	/** The pictures path of the user e. g. C:\Users\user\Pictures */
	Pictures = CSIDL_MYPICTURES,

	/** The profile path of the user e. g. C:\Users\user */
	Profile = CSIDL_PROFILE,

	/** The SysWOW64 path of the operating system e. g. C:\Windows\SysWOW64 */
	SysWOW64 = CSIDL_SYSTEMX86,

	/** The program files x86 path e. g. C:\Program Files (x86) */
	ProgramFilesX86 = CSIDL_PROGRAM_FILESX86,

	/** The common program files path e. g. C:\Program Files\Common Files */
	ProgramFilesCommon = CSIDL_PROGRAM_FILES_COMMON,

	/** The common program files x86 path e. g. C:\Program Files (x86)\Common Files */
	ProgramFilesX86Common = CSIDL_PROGRAM_FILES_COMMONX86,

	/** The common templates path e. g. C:\ProgramData\Microsoft\Windows\Templates */
	CommonTemplates = CSIDL_COMMON_TEMPLATES,

	/** The common documents path e. g. C:\Users\Public\Documents */
	CommonDocuments = CSIDL_COMMON_DOCUMENTS,

	/** The common admin tools path e. g.
	 * C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Administrative Tools */
	CommonAdminTools = CSIDL_COMMON_ADMINTOOLS,

	/** The admin tools path e. g.
	 * C:\Users\Test\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Administrative Tools */
	AdminTools = CSIDL_ADMINTOOLS,

	/** The common music path e. g. C:\Users\Public\Music */
	CommonMusic = CSIDL_COMMON_MUSIC,

	/** The common pictures path e. g. C:\Users\Public\Pictures */
	CommonPictures = CSIDL_COMMON_PICTURES,

	/** The common videos path e. g. C:\Users\Public\Videos */
	CommonVideos = CSIDL_COMMON_VIDEO,

	/** The resources path of the operating system e. g. C:\Windows\resources */
	Resources = CSIDL_RESOURCES,

	/** The CD burn area path e. g. C:\Users\Test\AppData\Local\Microsoft\Windows\Burn\Burn */
	CdBurnArea = CSIDL_CDBURN_AREA
};
#elif defined(OS_LINUX)
enum class Directory {
}
#endif // OS_LINUX

#endif // !DIRECTORY_H
