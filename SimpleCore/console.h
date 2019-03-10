#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef _WIN32
#include <Windows.h>
#include "consolecolor.h"
#endif // _WIN32

#include "astring.h"

class Console {
public:
#ifdef _WIN32
    Console();

    static void print(const AString& string,
        bool newLine = true,
        ConsoleColor color = LightGray,
        ConsoleColor backgroundColor = Black,
        bool centered = false);

    static void printLine(ConsoleColor color = LightGray, ConsoleColor backgroundColor = Black);

    static void keep();

    static void disableCloseButton();

    static void setConsoleTitle(const AString& title);

    static int getConsoleWidth();

    static int getConsoleHeight();

    static void printColorExample();
#elif __unix__

    static void print(const AString& string, bool newLine = true);

    static void keep();

#endif // __unix__
private:
#ifdef _WIN32
    static CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo_;

    static Console consoleInitializer_;

    static HANDLE inputHandle_;

    static HANDLE outputHandle_;

    static int defaultColor_;

    static void setControlEventHandler();
#elif __unix__unsupported
    static AString defaultColor_;
#endif // __unix__unsupported
};

#endif // CONSOLE_H
