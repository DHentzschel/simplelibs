#include "maximizewindowcallbacktest.h"

#include <console.h>

void MaximizeWindowCallbackTest::invoke(GLFWwindow* window, const Vector2& size)
{
    Console::print("Window maximized. Size: " + TO_STRING(size.x) + ", " + TO_STRING(size.y));
}
