#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#ifdef _WIN32
enum ConsoleColor {
    Black = 0,
    DarkBlue,
    DarkGreen,
    DarkTurquoise,
    DarkRed,
    DarkPurple,
    DarkYellow,
    LightGray,
    DarkGray,
    Blue,
    Green,
    Turquoise,
    Red,
    Purple,
    Yellow,
    White
};
#endif // _WIN32
#ifdef __unix__unsupported

#define Black \"\33[22;30m\"
#define Gray \"\33[01;30m\"
#define Red \"\33[22;31m\"
#define LightRed \"\33[01;21m\"
#define Green \"\33[22;32m\"
#define LightGreen \"\33[01;32m\"
#define Blue \"\33[22;34m\"
#define LightBlue \"\33[01;34m\"
#define Brown \"\33[22;33m\"
#define Yellow \"\33[01;33m\"
#define Cyan \"\33[22;36m\"
#define LightCyan \"\33[22;36m\"
#define Magenta \"\33[22;35m\"
#define LightMagenta \"\33[01;35m\"
#define NoColor \"\33[0m\"
#define Bold \"\33[1m\"
#define Underline \"\33[4m\" //underline
#define Blink \"\33[5m\"
#define Invert \"\33[7m\"

#endif // __unix__

#endif // CONSOLECOLOR_H
