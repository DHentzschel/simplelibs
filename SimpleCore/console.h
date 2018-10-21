#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

#include "astring.h"
#include "consolecolor.h"

class Console {
public:
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

private:
    static CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo_;

    static Console consoleInitializer_;

    static HANDLE inputHandle_;

    static HANDLE outputHandle_;

    static int defaultColor_;

    static void setControlEventHandler();
};

#endif // CONSOLE_H
