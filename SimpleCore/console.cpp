#include "console.h"

#include <iostream>

#ifdef OS_WIN
CONSOLE_SCREEN_BUFFER_INFO Console::consoleBufferInfo_;

HANDLE Console::inputHandle_;

HANDLE Console::outputHandle_;
#elif defined OS_LINUX || defined OS_UNIX
# include <sys/ioctl.h> 
#endif // OS_LINUX || OS_UNIX

ConsoleColor::Type Console::defaultColor_;

Console Console::consoleInitializer_ = Console();

Console::Console()
{
#ifdef OS_WIN
	inputHandle_ = GetStdHandle(STD_INPUT_HANDLE);
	outputHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	// setControlEventHandler();
#endif OS_WIN
	defaultColor_ = ConsoleColor::LightGray;
}

void Console::print(const AString& string,
	const bool newLine,
	const ConsoleColor::Type color,
	const ConsoleColor::Type backgroundColor,
	const bool centered)
{
	const auto colorChanged = color != ConsoleColor::LightGray || backgroundColor != ConsoleColor::Black;

	if (colorChanged) {
#ifdef OS_WIN
		SetConsoleTextAttribute(outputHandle_, static_cast<int>(color) + static_cast<int>(tempBackgroundColor) * 16);
#elif defined OS_LINUX || defined OS_UNIX
		std::cout << "\033[0" << ';' << color << ';' << backgroundColor + 10 << 'm';
#endif // OS_LINUX || OS_UNIX
	}
	if (centered) {
		const auto factor = (getConsoleWidth() - string.size()) * 0.5F;
		for (auto i = 0; i < factor; ++i) {
			std::cout << ' ';
		}
	}
	std::cout << string << (newLine ? "\n" : "");
	if (colorChanged) {
#ifdef OS_WIN
		SetConsoleTextAttribute(outputHandle_, defaultColor_);
#elif defined OS_LINUX || defined OS_UNIX
		std::cout << "\033[0m";
#endif // OS_LINUX || OS_UNIX
	}
}

void Console::printLine(const ConsoleColor::Type color, const ConsoleColor::Type backgroundColor)
{
	const auto width = getConsoleWidth();
	AString line = "-";
	for (auto i = 0; line.size() < width; ++i) {
		line += '-';
	}
	print(line, true, color, backgroundColor);
}

void Console::keep()
{
	std::cin.get();
}

#ifdef OS_WIN
void Console::setControlEventHandler()
{
	DWORD mode = 0;
	GetConsoleMode(inputHandle_, &mode);
	SetConsoleMode(inputHandle_, mode &= ~ENABLE_PROCESSED_INPUT);
}
#endif // OS_WIN

#ifdef OS_WIN
void Console::disableCloseButton()
{
	const auto hmenu = GetSystemMenu(GetConsoleWindow(), FALSE);
	while (DeleteMenu(hmenu, 0, MF_BYPOSITION));
}
#endif // OS_WIN

void Console::setConsoleTitle(const AString & title)
{
#ifdef OS_WIN
	SetConsoleTitleA(title.c_str());
#elif defined OS_LINUX || defined OS_UNIX
	std::cout << "\033]0;" << title << "\007";
#endif // OS_LINUX || OS_UNIX
}

int Console::getConsoleWidth()
{
#ifdef OS_WIN
	ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
	return consoleBufferInfo_.srWindow.Right - consoleBufferInfo_.srWindow.Left + 1;
#elif defined(OS_LINUX) || defined(OS_UNIX)
	winsize tempWinsize;
	ioctl(0, TIOCGWINSZ, &tempWinsize);
	return tempWinsize.ws_col;
#endif // OS_LINUX || OS_UNIX
}

int Console::getConsoleHeight()
{
#ifdef OS_WIN
	ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
	return consoleBufferInfo_.srWindow.Bottom - consoleBufferInfo_.srWindow.Top + 1;
#elif defined(OS_LINUX) || defined(OS_UNIX)
	winsize tempWinsize;
	ioctl(0, TIOCGWINSZ, &tempWinsize);
	return tempWinsize.ws_row;
#endif // OS_LINUX || OS_UNIX
}

void Console::printColorExample()
{
#ifdef OS_WIN
	for (int i = 1; i < 0x10; i++) {
		SetConsoleTextAttribute(outputHandle_, i);
		std::cout "This is a test!" << std::endl;
	}
#elif defined(OS_LINUX) || defined(OS_UNIX)
	for (auto color : ConsoleColor::all) {
		for (auto backgroundColor : ConsoleColor::all) {
			print("This is a test!", true, color, backgroundColor);
		}
	}
#endif // OS_LINUX || OS_UNIX
}
