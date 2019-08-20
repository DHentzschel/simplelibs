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
	DarkMagenta,
	DarkYellow,
	LightGray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
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
#endif // OS_LINUX || OS_UNIX

static const Type all[] = {
	Type::Black,
	Type::DarkRed,
	Type::DarkGreen,
	Type::DarkYellow,
	Type::DarkBlue,
	Type::DarkMagenta,
	Type::DarkCyan,
	Type::LightGray,
	Type::DarkGray,
	Type::Red,
	Type::Green,
	Type::Yellow,
	Type::Blue,
	Type::Magenta,
	Type::Cyan,
	Type::White
};
};

#endif // CONSOLECOLOR_H
