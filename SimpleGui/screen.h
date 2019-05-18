#ifndef SCREEN_H
#define SCREEN_H

#include <vector2i.h>

class ScreenPrivate;

class Screen {
public:
    static Vector2i getSize();

private:
    Screen();

    ~Screen();

    static Screen screenInitializer_;

    static ScreenPrivate* private_;
};

#endif // SCREEN_H
