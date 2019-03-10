#ifndef LOGGER_H
#define LOGGER_H

#include "astring.h"
#include "consolecolor.h"
#include "plogtp.h"
#include "file.h"

class Logger {
public:
	Logger() = default;
	~Logger();

	static void prepareLogFile(const AString& getPath);

#ifdef _WIN32

    static void print(const AString& text,
        bool newLine = true,
        ConsoleColor color = Turquoise,
        ConsoleColor backgroundColor = Black);

	static void debug(const AString& text,
		bool newLine = true,
		ConsoleColor color = Turquoise,
		ConsoleColor backgroundColor = Black);

	static void info(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

	static void error(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

	static void warn(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

#elif __unix__

    static void print(const AString& text,
        bool newLine = true);

    static void debug(const AString& text,
        bool newLine = true);

    static void info(const AString& text,
        bool newLine = true);

    static void error(const AString& text,
        bool newLine = true);

    static void warn(const AString& text,
        bool newLine = true);

#endif // __unix__

private:
	static File file_;

	static AString printPrefix(LogType type);
};

#endif   // LOGGER_H
