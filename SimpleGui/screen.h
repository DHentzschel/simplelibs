#ifndef SCREEN_H
#define SCREEN_H

#include <vector2.h>

class ScreenPrivate;

class Screen {
public:
    static Vector2 getSize();

private:
    Screen();

    ~Screen();

    static Screen screenInitializer_;

    static ScreenPrivate* private_;
};

#endif // SCREEN_H
