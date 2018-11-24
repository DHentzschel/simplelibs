#include "resizewindowcallbacktest.h"

#include <console.h>

void ResizeWindowCallbackTest::invoke(GLFWwindow* window, const Vector2& size)
{
    Console::print("Window resized: " + TO_STRING(size.x) + ", " + TO_STRING(size.y));
}
