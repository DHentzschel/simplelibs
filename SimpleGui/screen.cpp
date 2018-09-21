#include "screen.h"

#include <Windows.h>

class ScreenPrivate {
public:
    ScreenPrivate();

    Vector2 getSize();

    static Vector2 desktopSize;
};

Vector2 ScreenPrivate::desktopSize;

Screen Screen::screenInitializer_;

ScreenPrivate* Screen::private_;

Vector2 Screen::getSize()
{
    return private_->getSize();
}

Screen::Screen()
{
    private_ = new ScreenPrivate();
}

Screen::~Screen()
{
    delete private_;
}

ScreenPrivate::ScreenPrivate()
{
    desktopSize.x = GetSystemMetrics(SM_CXSCREEN);
    desktopSize.y = GetSystemMetrics(SM_CYSCREEN);
}

Vector2 ScreenPrivate::getSize()
{
    return desktopSize;
}
