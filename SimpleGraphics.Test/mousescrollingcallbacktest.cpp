#include "mousescrollingcallbacktest.h"

#include <console.h>

MouseScrollingCallbackTest::MouseScrollingCallbackTest()
{}


MouseScrollingCallbackTest::~MouseScrollingCallbackTest()
{}

void MouseScrollingCallbackTest::invoke(GLFWwindow* window, const Vector2d& offset)
{
    Console::print("Mouse scrolled offsets: " + AString::toString(offset.x) + ", " + AString::toString(offset.y));
}
