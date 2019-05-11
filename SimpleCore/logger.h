#ifndef LOGGER_H
#define LOGGER_H

#include "astring.h"
#include "consolecolor.h"
#include "plogtp.h"
#include "file.h"

/**
 * @author Daniel Hentzschel on 11.05.2019.
 */
class Logger {
public:
	/**
	 * Closes the filestream if opened.
	 */
	~Logger();

	/**
	 * Initializes the log filestream by opening it with the path given by
	 * parameter.
	 *
	 * @param path the file path of the log file
	 */
	static void prepareLogFile(const AString& path);

	/**
	 * Prints text to the console.
	 *
	 * @param text the text to print
	 * @param newLine either there should be a new line appended
	 * @param color the foreground color of the text (default is Turquoise)
	 * @param backgroundColor the background color of the text (default is Black)
	 */
	static void print(const AString& text,
		bool newLine = true,
		ConsoleColor color = Turquoise,
		ConsoleColor backgroundColor = Black);

	/**
	 * Prints debug text to the console.
	 * The current time and output mode will be prepended.
	 *
	 * @param text the text to print
	 * @param newLine either there should be a new line appended
	 * @param color the foreground color of the text (default is Turquoise)
	 * @param backgroundColor the background color of the text (default is Black)
	 */
	static void debug(const AString& text,
		bool newLine = true,
		ConsoleColor color = Turquoise,
		ConsoleColor backgroundColor = Black);

	/**
	 * Prints information text to the console.
	 * The current time and output mode will be prepended.
	 *
	 * @param text the text to print
	 * @param newLine either there should be a new line appended
	 * @param color the foreground color of the text (default is LightGray)
	 * @param backgroundColor the background color of the text (default is Black)
	 */
	static void info(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

	/**
	 * Prints error text to the console.
	 * The current time and output mode will be prepended.
	 *
	 * @param text the text to print
	 * @param newLine either there should be a new line appended
	 * @param color the foreground color of the text (default is LightGray)
	 * @param backgroundColor the background color of the text (default is Black)
	 */
	static void error(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

	/**
	 * Prints warning text to the console.
	 * The current time and output mode will be prepended.
	 *
	 * @param text the text to print
	 * @param newLine either there should be a new line appended
	 * @param color the foreground color of the text (default is LightGray)
	 * @param backgroundColor the background color of the text (default is Black)
	 */
	static void warn(const AString& text,
		bool newLine = true,
		ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black);

private:
	static File file_;

	/**
	 * Prints the prefix consisting of the timestamp and output mode.
	 * Example: [HH:mm:ss INFO]
	 *
	 * @param type the log type to be used
	 */
	static void printPrefix(LogType type);
};

#endif   // LOGGER_H
