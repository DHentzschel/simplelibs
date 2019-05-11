#include "logger.h"

#include "console.h"
#include "datetime.h"

File Logger::file_;

Logger::~Logger()
{
	if (file_.isOpen()) {
		file_.close();
	}
}

void Logger::prepareLogFile(const AString& path)
{
	file_.setFilepath(AString(path).replaceAll(":", "-").replaceFirst(" ", "_") + ".log");
	if (!file_.open(WriteOnly | Append)) {
		warn("Couldn't create logfile '" + path + "'!");
	}
}

void Logger::print(const AString & text,
	bool newLine,
	ConsoleColor color,
	ConsoleColor backgroundColor)
{
	Console::print(text, newLine, color, backgroundColor);
	if (file_.isOpen()) {
		file_ << text + (newLine ? "\n" : "");
	}
}

void Logger::debug(const AString & text,
	bool newLine,
	ConsoleColor color,
	ConsoleColor backgroundColor)
{
	printPrefix(LogType::Debug);
	print(text, newLine, color, backgroundColor);
}

void Logger::info(const AString & text,
	bool newLine,
	ConsoleColor color,
	ConsoleColor backgroundColor)
{
	printPrefix(LogType::Info);
	print(text, newLine, color, backgroundColor);
}

void Logger::error(const AString & text,
	bool newLine,
	ConsoleColor color,
	ConsoleColor backgroundColor)
{
	printPrefix(LogType::Error);
	print(text, newLine, color, backgroundColor);
}

void Logger::warn(const AString & text,
	bool newLine,
	ConsoleColor color,
	ConsoleColor backgroundColor)
{
	printPrefix(LogType::Warn);
	print(text, newLine, color, backgroundColor);
}

void Logger::printPrefix(LogType type)
{
	AString string = "[" + DateTime::getTimestamp();
	Console::print(string, false);
	if (type == LogType::Debug) {
		const auto label = " DBG";
		Console::print(label, false, Turquoise);
		string += label;
	}
	else if (type == LogType::Info) {
		const auto label = " INFO";
		Console::print(label, false, Green);
		string += label;
	}
	else if (type == LogType::Error) {
		const auto label = " ERR";
		Console::print(label, false, Red);
		string += label;
	}
	else if (type == LogType::Warn) {
		const auto label = " WARN";
		Console::print(label, false, Yellow);
		string += label;
	}

	const auto label = "]: ";
	Console::print(label, false);
	const auto result = string + label;

	if (file_.isOpen()) {
		file_.append(result);
	}
}
