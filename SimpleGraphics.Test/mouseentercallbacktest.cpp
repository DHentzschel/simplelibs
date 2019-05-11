#include "mouseentercallbacktest.h"

#include <console.h>

void MouseEnterCallbackTest::invoke(GLFWwindow* window, bool entered)
{
    Console::print("Mouse entered window: " + AString::toString(entered, true));
}
