#include "mousebuttoncallbacktest.h"

#include <console.h>

MouseButtonCallbackTest::MouseButtonCallbackTest()
{}

MouseButtonCallbackTest::~MouseButtonCallbackTest()
{}

void MouseButtonCallbackTest::invoke(GLFWwindow* window, Key button, InputAction action, byte mods)
{
    Console::print("Mouse button " + AString::toString(static_cast<int>(button))
        + " was pressed, Action: " + AString::toString(static_cast<int>(action))
        + ", Mods: " + AString::toString(mods));
}
