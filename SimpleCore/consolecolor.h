#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#include "osdetection.h"

/**
 * This class contains the default system console colors.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
namespace ConsoleColor {
#ifdef OS_WIN
enum Type {
	Black = 0,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkPurple,
	DarkYellow,
	LightGray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White,
	Reset = Black
};
#elif defined OS_LINUX || defined OS_UNIX
enum Type {
	Black = 30,
	DarkRed,
	DarkGreen,
	DarkYellow,
	DarkBlue,
	DarkMagenta,
	DarkCyan,
	LightGray,
	Reset = 39,
	DarkGray = 90,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
};

static const Type all[] = {
	Black,
	DarkRed,
	DarkGreen,
	DarkYellow,
	DarkBlue,
	DarkMagenta,
	DarkCyan,
	LightGray,
	Reset,
	DarkGray,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
};
#endif // OS_LINUX || OS_UNIX
};

#endif // CONSOLECOLOR_H
