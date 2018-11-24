#include "mousebuttoncallbacktest.h"

#include <console.h>

MouseButtonCallbackTest::MouseButtonCallbackTest()
{
}

MouseButtonCallbackTest::~MouseButtonCallbackTest()
{
}

void MouseButtonCallbackTest::invoke(GLFWwindow* window, Key button, InputAction action, byte mods)
{
    Console::print("Mouse button " + TO_STRING(STATIC_CAST(int, button)) + " was pressed, Action: "
        + TO_STRING(STATIC_CAST(int, action)) + ", Mods: " + TO_STRING(mods));
}
