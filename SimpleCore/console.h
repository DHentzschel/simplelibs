#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

#include "astring.h"
#include "consolecolor.h"

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
	Console();

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
	static void print(const AString& string, bool newLine = true, ConsoleColor color = LightGray,
		ConsoleColor backgroundColor = Black, bool centered = false);

	/**
	 * Prints a line consisting of minuses to console in the amount of columns.
	 *
	 * @param color the foreground color of the string to print
	 * @param backgroundColor the background color of the string to print
	 */
	static void printLine(ConsoleColor color = LightGray, ConsoleColor backgroundColor = Black);

	/**
	 * Keeps console alive. Cancel by pressing return.
	 */
	static void keep();

	/**
	 * Disables the close button of the console window.
	 */
	static void disableCloseButton();

	/**
	 * Sets the console tile to the specified title.
	 *
	 * @param title the new console title
	 */
	static void setConsoleTitle(const AString& title);

	/**
	 * Returns the console width. Width means column count of chars.
	 *
	 * @return the console width (count of columns)
	 */
	static int getConsoleWidth();

	/**
	 * Returns th console height. Height means row count of chars.
	 *
	 * @return the console height (count of rows)
	 */
	static int getConsoleHeight();

	/**
	 * Prints an example of colorizing the console. Only for testing.
	 */
	static void printColorExample();

private:
	static CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo_;

	static Console consoleInitializer_;

	static HANDLE inputHandle_;

	static HANDLE outputHandle_;

	static int defaultColor_;

	/**
	 * Initializes the console mode and sets the some default stuff.
	 */
	static void setControlEventHandler();
};

#endif // CONSOLE_H
