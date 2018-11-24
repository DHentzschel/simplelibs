#include "mousescrollingcallbacktest.h"

#include <console.h>

MouseScrollingCallbackTest::MouseScrollingCallbackTest()
{
}


MouseScrollingCallbackTest::~MouseScrollingCallbackTest()
{
}

void MouseScrollingCallbackTest::invoke(GLFWwindow* window, const Vector2d& offset)
{
    Console::print("Mouse scrolled offsets: " + TO_STRING(offset.x) + ", " + TO_STRING(offset.y));
}
