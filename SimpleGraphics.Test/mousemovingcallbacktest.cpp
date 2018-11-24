#include "mousemovingcallbacktest.h"

#include <console.h>

void MouseMovingCallbackTest::invoke(GLFWwindow* window, const Vector2d& position)
{
    Console::print("Mouse position changed: " + TO_STRING(position.x) + ", " + TO_STRING(position.y));
}
