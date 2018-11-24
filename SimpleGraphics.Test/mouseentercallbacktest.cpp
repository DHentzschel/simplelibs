#include "mouseentercallbacktest.h"

#include <console.h>

void MouseEnterCallbackTest::invoke(GLFWwindow* window, bool entered)
{
    Console::print("Mouse entered window: " + TO_STRING_BOOL(entered));
}
