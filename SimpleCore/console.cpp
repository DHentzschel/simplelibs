#include "console.h"

#include <iostream>


Console Console::consoleInitializer_ = Console();

#ifdef _WIN32
CONSOLE_SCREEN_BUFFER_INFO Console::consoleBufferInfo_;

HANDLE Console::inputHandle_;

HANDLE Console::outputHandle_;

int Console::defaultColor_;
#elif __unix__unsupported
#include <sys/ioctl.h>
#include <unistd.h>

winsize Console::terminalSize_;

AString Console::defaultColor_;
#endif // __unix__

#ifdef _WIN32
/**
 * \brief Constructs instance by calling intializing control event handler.
 */
Console::Console()
{
    inputHandle_ = GetStdHandle(STD_INPUT_HANDLE);
    outputHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
    defaultColor_ = static_cast<int>(LightGray);
}

/**
 * \brief Prints param string to console with new line depending on newLine param.
 * If set, params color and backgroundColor could be changed.
 * Default color = LightGrey, default backgroundColor = Black.
 * If param centerd set to true, prints string centered to console.
 * \param string
 * \param newLine
 * \param color
 * \param backgroundColor
 * \param centered
 */
void Console::print(const AString& string,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor,
    const bool centered)
{
    const auto colorChanged = color != LightGray || backgroundColor != Black;

    if (colorChanged) {
        SetConsoleTextAttribute(outputHandle_, static_cast<int>(color + backgroundColor * 16));
    }
    if (centered) {
        const auto factor = (getConsoleWidth() - string.size()) * 0.5F;
        for (auto i = 0; i < factor; ++i) {
            std::cout << ' ';
        }
    }
    std::cout << string << (newLine ? "\n" : "");
    if (colorChanged) {
        SetConsoleTextAttribute(outputHandle_, defaultColor_);
    }
}

/**
 * \brief Prints line consisting of minuses to console in the amount of columns.
 */
void Console::printLine(const ConsoleColor color, const ConsoleColor backgroundColor)
{
    const auto colorChanged = color != LightGray || backgroundColor != Black;

    if (colorChanged) {
        SetConsoleTextAttribute(outputHandle_, static_cast<int>(color + backgroundColor * 16));
    }

    const auto width = getConsoleWidth();
    for (auto i = 0; i < width; ++i) {
        std::cout << '-';
    }

    if (colorChanged) {
        SetConsoleTextAttribute(outputHandle_, defaultColor_);
    }
}

/**
 * \brief Keeps console alive. Cancel by pressing return.
 */
void Console::keep()
{
    std::cin.get();
}

/**
 * \brief Initializes console mode and set some default stuff.
 */
void Console::setControlEventHandler()
{
    DWORD mode = 0;
    GetConsoleMode(inputHandle_, &mode);
    SetConsoleMode(inputHandle_, mode &= ~ENABLE_PROCESSED_INPUT);
}

/**
 * \brief Disables close button of console window.
 */
void Console::disableCloseButton()
{
    const auto hmenu = GetSystemMenu(GetConsoleWindow(), FALSE);
    while (DeleteMenu(hmenu, 0, MF_BYPOSITION));
}

/**
 * \brief Set console tile by param title.
 * \param title new console title
 */
void Console::setConsoleTitle(const AString& title)
{
    SetConsoleTitleA(title.c_str());
}

/**
 * \brief Returns console width. Width means column count of chars.
 * \return console width
 */
int Console::getConsoleWidth()
{
#ifdef _WIN32
    ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
    return consoleBufferInfo_.srWindow.Right - consoleBufferInfo_.srWindow.Left + 1;
#elif __unix__
    ZeroMemory(&terminalSize_, sizeof winsize);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize_);
    return terminalSize_.ws_col;
#endif // __unix__
}

/**
* \brief Returns console height. Height means row count of chars.
* \return console height
*/
int Console::getConsoleHeight()
{
#ifdef _WIN32
    ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
    return consoleBufferInfo_.srWindow.Bottom - consoleBufferInfo_.srWindow.Top + 1;
#elif __unix__
    ZeroMemory(&terminalSize_, sizeof winsize);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize_);
    return terminalSize_.ws_row;
#endif // __unix__
}

void Console::printColorExample()
{
    for (int i = 1; i < 0x10; i++) {
        SetConsoleTextAttribute(outputHandle_, i);
        std::cout << i << "This is a test!" << std::endl;
    }
    SetConsoleTextAttribute(outputHandle_, ConsoleColor::LightGray);
}

#elif __unix__

/**
 * \brief Prints param string to console with new line depending on newLine param.
 * \param string
 * \param newLine
 */
void Console::print(const AString& string,
    const bool newLine)
{
    std::cout << string << (newLine ? "\n" : "");
}

/**
 * \brief Keeps console alive. Cancel by pressing return.
 */
void Console::keep()
{
    std::cin.get();
}

#endif // __unix__
