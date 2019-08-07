#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#include "osdetection.h"

/**
 * This class contains the default system console colors.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
#ifdef OS_WIN
enum class ConsoleColor {
	Black = 0,
	DarkBlue,
	DarkGreen,
	DarkTurquoise,
	DarkRed,
	DarkPurple,
	DarkYellow,
	LightGray,
	DarkGray,
	Blue,
	Green,
	Turquoise,
	Red,
	Purple,
	Yellow,
	White
};
#elif defined (OS_LINUX) // OS_WIN
enum class ConsoleColor {
	Default = 39,
	Black = 30,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	LightGray,
	DarkGray = 90,
	LightRed,
	LightGreen,
	LightYellow,
	LightBlue,
	LightMagenta,
	LightCyan,
	White
};
#endif // OS_LINUX

#endif // CONSOLECOLOR_H
