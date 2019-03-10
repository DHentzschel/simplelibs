#include "logger.h"

#include "console.h"
#include "datetime.h"

File Logger::file_;

/**
 * \brief Destroys current instance after closing the opened filestream.
 */
Logger::~Logger()
{
    if (file_.isOpen()) {
        file_.close();
    }
}

/**
 * \brief Initializes log filestream by opening with param path.
 * \param path file path
 */
void Logger::prepareLogFile(const AString& getPath)
{
    file_.setFilepath(AString(getPath).replaceAll(":", "-").replaceFirst(" ", "_") + ".log");
    if (!file_.open(WriteOnly | Append)) {
        warn("Couldn't create logfile '" + getPath + "'!");
    }
}

#ifdef _WIN32

void Logger::print(const AString& text,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor)
{
    Console::print(text, newLine, color, backgroundColor);
    if (file_.isOpen()) {
        file_ << text + (newLine ? "\n" : "");
    }
}

void Logger::debug(const AString& text,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor)
{
    printPrefix(Debug);
    print(text, newLine, color, backgroundColor);
}

void Logger::info(const AString& text,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor)
{
    printPrefix(Info);
    print(text, newLine, color, backgroundColor);
}

void Logger::error(const AString& text,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor)
{
    printPrefix(Error);
    print(text, newLine, color, backgroundColor);
}

void Logger::warn(const AString& text,
    const bool newLine,
    const ConsoleColor color,
    const ConsoleColor backgroundColor)
{
    printPrefix(Warn);
    print(text, newLine, color, backgroundColor);
}

AString Logger::printPrefix(const LogType type)
{
    AString string = "[" + DateTime::getTimestamp();
    Console::print(string, false);
    if (type == Debug) {
        Console::print(" DBG", false, Turquoise);
        string += " DBG";
    }
    else if (type == Info) {
        Console::print(" INFO", false, Green);
        string += " INFO";
    }
    else if (type == Error) {
        Console::print(" ERR", false, Red);
        string += " ERR";
    }
    else if (type == Warn) {
        Console::print(" WARN", false, Yellow);
        string += " WARN";
    }
    Console::print("]: ", false);
    const auto result = string + "]: ";

    if (file_.isOpen()) {
        file_.append(result);
    }

    return result;
}

#elif __unix__

void Logger::print(const AString& text,
    const bool newLine)
{
    Console::print(text, newLine);
    if (file_.isOpen()) {
        file_ << text + (newLine ? "\n" : "");
    }
}

void Logger::debug(const AString& text,
    const bool newLine)
{
    printPrefix(Debug);
    print(text, newLine);
}

void Logger::info(const AString& text,
    const bool newLine)
{
    printPrefix(Info);
    print(text, newLine);
}

void Logger::error(const AString& text,
    const bool newLine)
{
    printPrefix(Error);
    print(text, newLine);
}

void Logger::warn(const AString& text,
    const bool newLine)
{
    printPrefix(Warn);
    print(text, newLine);
}

AString Logger::printPrefix(const LogType type)
{
    AString string = "[" + DateTime::getTimestamp();
    Console::print(string, false);
    if (type == Debug) {
        Console::print(" DBG", false);
        string += " DBG";
    }
    else if (type == Info) {
        Console::print(" INFO", false);
        string += " INFO";
    }
    else if (type == Error) {
        Console::print(" ERR", false);
        string += " ERR";
    }
    else if (type == Warn) {
        Console::print(" WARN", false);
        string += " WARN";
    }
    Console::print("]: ", false);
    const auto result = string + "]: ";

    if (file_.isOpen()) {
        file_.append(result);
    }

    return result;
}

#endif // __unix__
