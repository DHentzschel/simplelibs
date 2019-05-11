#include "mousemovingcallbacktest.h"

#include <console.h>

void MouseMovingCallbackTest::invoke(GLFWwindow* window, const Vector2d& position)
{
    Console::print("Mouse position changed: " + AString::toString(position.x) + ", " + AString::toString(position.y));
}
