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

private:
	static File file_;

	static AString printPrefix(LogType type);
};

#endif   // LOGGER_H
