#include "minimizewindowcallbacktest.h"

#include <console.h>

void MinimizeWindowCallbackTest::invoke(GLFWwindow* window)
{
    Console::print("Window minimized.");
}
