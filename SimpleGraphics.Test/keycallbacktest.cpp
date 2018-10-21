#include "keycallbacktest.h"

#include <console.h>

KeyCallbackTest::KeyCallbackTest()
{
}

KeyCallbackTest::~KeyCallbackTest()
{
}

void KeyCallbackTest::invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods)
{
    Console::print("Key " + TO_STRING(STATIC_CAST(int, key)) + " was pressed, Action: " + TO_STRING(STATIC_CAST(int, action))
        + ", Mods: " + TO_STRING(mods));
}
