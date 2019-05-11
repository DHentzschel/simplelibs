#include "keycallbacktest.h"

#include <console.h>

KeyCallbackTest::KeyCallbackTest()
{}

KeyCallbackTest::~KeyCallbackTest()
{}

void KeyCallbackTest::invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods)
{
    Console::print("Key " + AString::toString(static_cast<int>(key))
        + " was pressed, Action: " + AString::toString(static_cast<int>(action))
        + ", Mods: " + AString::toString(mods));
}
