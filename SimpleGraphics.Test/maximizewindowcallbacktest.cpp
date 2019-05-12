#include "maximizewindowcallbacktest.h"

#include <console.h>

void MaximizeWindowCallbackTest::invoke(GLFWwindow* window, const Vector2i& size)
{
    Console::print("Window maximized. Size: " + AString::toString(size.x) + ", " + AString::toString(size.y));
}
