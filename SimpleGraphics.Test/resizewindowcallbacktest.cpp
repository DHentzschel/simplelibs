#include "resizewindowcallbacktest.h"

#include <console.h>

void ResizeWindowCallbackTest::invoke(GLFWwindow* window, const Vector2i& size)
{
    Console::print("Window resized: " + AString::toString(size.x) + ", " + AString::toString(size.y));
}
