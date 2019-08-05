#include "console.h"

#include <iostream>

Console Console::consoleInitializer_ = Console();

#ifdef OS_WIN32
CONSOLE_SCREEN_BUFFER_INFO Console::consoleBufferInfo_;

HANDLE Console::inputHandle_;

HANDLE Console::outputHandle_;

int Console::defaultColor_;
#endif // OS_WIN32

Console::Console()
{
#ifdef OS_WIN32
	inputHandle_ = GetStdHandle(STD_INPUT_HANDLE);
	outputHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	defaultColor_ = static_cast<int>(ConsoleColor::LightGray);
	//   setControlEventHandler();
#endif OS_WIN32
}

void Console::print(const AString& string,
	const bool newLine,
	const ConsoleColor color,
	const ConsoleColor backgroundColor,
	const bool centered)
{
#ifdef OS_WIN
	const auto colorChanged = color != ConsoleColor::LightGray || backgroundColor != ConsoleColor::Black;
#elif defined (OS_LINUX)
	const auto colorChanged = color != ConsoleColor::Default || backgroundColor != (static_cast<int>(ConsoleColor::Default) + 10);
#endif // OS_LINUX

	if (colorChanged) {
#ifdef OS_WIN
		SetConsoleTextAttribute(outputHandle_, static_cast<int>(color) + static_cast<int>(backgroundColor) * 16);
#elif defined (OS_LINUX) // OS_WIN
		std::cout << "\033[0" << ';' << AString::toString(color) << ';' << backgroundColor << 'm';
#endif //OS_LINUX
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
#elif defined (OS_LINUX) // OS_WIN
		std::cout << "\033[0m";
#endif // OS_LINUX
	}
}

void Console::printLine(const ConsoleColor color, const ConsoleColor backgroundColor)
{
	const auto colorChanged = color != ConsoleColor::LightGray || backgroundColor != ConsoleColor::Black;

	if (colorChanged) {
		SetConsoleTextAttribute(outputHandle_, static_cast<int>(color) + static_cast<int>(backgroundColor) * 16);
	}

	const auto width = getConsoleWidth();
	for (auto i = 0; i < width; ++i) {
		std::cout << '-';
	}

	if (colorChanged) {
		SetConsoleTextAttribute(outputHandle_, defaultColor_);
	}
}

void Console::keep()
{
	std::cin.get();
}

#ifdef OS_WIN32
void Console::setControlEventHandler()
{
	DWORD mode = 0;
	GetConsoleMode(inputHandle_, &mode);
	SetConsoleMode(inputHandle_, mode &= ~ENABLE_PROCESSED_INPUT);
}
#endif // OS_WIN32

#ifdef OS_WIN32
void Console::disableCloseButton()
{
	const auto hmenu = GetSystemMenu(GetConsoleWindow(), FALSE);
	while (DeleteMenu(hmenu, 0, MF_BYPOSITION));
}
#endif // OS_WIN32

void Console::setConsoleTitle(const AString & title)
{
#ifdef OS_WIN32
	SetConsoleTitleA(title.c_str());
#endif // OS_WIN32
}

int Console::getConsoleWidth()
{
#ifdef OS_WIN32
	ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
	return consoleBufferInfo_.srWindow.Right - consoleBufferInfo_.srWindow.Left + 1;
#endif // OS_WIN32
}

int Console::getConsoleHeight()
{
#ifdef OS_WIN32
	ZeroMemory(&consoleBufferInfo_, sizeof CONSOLE_SCREEN_BUFFER_INFO);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo_);
	return consoleBufferInfo_.srWindow.Bottom - consoleBufferInfo_.srWindow.Top + 1;
#endif // OS_WIN32

}

void Console::printColorExample()
{
#ifdef OS_WIN32
	for (int i = 1; i < 0x10; i++) {
		SetConsoleTextAttribute(outputHandle_, i);
		std::cout << i << "This is a test!" << std::endl;
	}
#endif //OS_WIN32
}
