#include "screen.h"

#include <Windows.h>

class ScreenPrivate {
public:
    ScreenPrivate();

	Vector2i getSize();

    static Vector2i desktopSize;
};

Vector2i ScreenPrivate::desktopSize;

Screen Screen::screenInitializer_;

ScreenPrivate* Screen::private_;

Vector2i Screen::getSize()
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

Vector2i ScreenPrivate::getSize()
{
    return desktopSize;
}
