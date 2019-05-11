#include "maximizewindowcallbacktest.h"

#include <console.h>

void MaximizeWindowCallbackTest::invoke(GLFWwindow* window, const Vector2& size)
{
    Console::print("Window maximized. Size: " + AString::toString(size.x) + ", " + AString::toString(size.y));
}
