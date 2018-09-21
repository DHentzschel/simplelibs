#include "screen.h"

#include <Windows.h>

class ScreenPrivate {
public:
    ScreenPrivate();

    Vector2 getSize();

    static RECT desktopSize;

};

RECT ScreenPrivate::desktopSize;

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
    GetWindowRect(GetDesktopWindow(), &desktopSize);
}

Vector2 ScreenPrivate::getSize()
{
    return Vector2(desktopSize.right, desktopSize.bottom);
}
