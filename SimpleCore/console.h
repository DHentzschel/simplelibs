#ifndef CONSOLE_H
#define CONSOLE_H

#include "osdetection.h"
#include "astring.h"
#include "consolecolor.h"

#ifdef OS_WIN
#include <Windows.h>
#endif // OS_WIN

/**
 * This class provides easy functions concerning the console window.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class Console {
public:
	/**
	 * Calls the default constructor and initializes default values.
	 */
	SIMPLECORE_API Console();

	/**
	 * Prints the specified string to console with new line depending on newLine parameter.
	 * If set, the parameters color and backgroundColor could be changed.
	 * Default color is LightGrey, default backgroundColor is Black.
	 * If parameter centered is set to true, the console prints the string centered in the console.
	 *
	 * @param string the string to print
	 * @param newLine whether a new line should be appended to console
	 * @param color the foreground color of the string to print
	 * @param backgroundColor the background color of the string to print
	 * @param centered whether the string should be printed centered
	 */
	SIMPLECORE_API static void print(const AString& string, bool newLine = true, 
		ConsoleColor::Type color = ConsoleColor::Type::LightGray,
		ConsoleColor::Type backgroundColor = ConsoleColor::Type::Black,
		bool centered = false);

	/**
	 * Prints a line consisting of minuses to console in the amount of columns.
	 *
	 * @param color the foreground color of the string to print
	 * @param backgroundColor the background color of the string to print
	 */
	SIMPLECORE_API static void printLine(ConsoleColor::Type color = ConsoleColor::Type::LightGray,
	 ConsoleColor::Type backgroundColor = ConsoleColor::Type::Black);

	/**
	 * Keeps console alive. Cancel by pressing return.
	 */
	SIMPLECORE_API static void keep();

	/**
	 * Disables the close button of the console window.
	 */
	SIMPLECORE_API static void disableCloseButton();

	/**
	 * Sets the console tile to the specified title.
	 *
	 * @param title the new console title
	 */
	SIMPLECORE_API static void setConsoleTitle(const AString& title);

	/**
	 * Returns the console width. Width means column count of chars.
	 *
	 * @return the console width (count of columns)
	 */
	SIMPLECORE_API static int getConsoleWidth();

	/**
	 * Returns th console height. Height means row count of chars.
	 *
	 * @return the console height (count of rows)
	 */
	SIMPLECORE_API static int getConsoleHeight();

	/**
	 * Prints an example of colorizing the console. Only for testing.
	 */
	SIMPLECORE_API static void printColorExample();

private:
	static Console consoleInitializer_;

	static ConsoleColor::Type defaultColor_;

#ifdef OS_WIN
	static CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo_;

	static HANDLE inputHandle_;

	static HANDLE outputHandle_;

	/**
	 * Initializes the console mode and sets the some default stuff.
	 */
	static void setControlEventHandler();
#endif // OS_WIN32
};

#endif // CONSOLE_H
