#include "imouseentercallback.h"

#include <functions.h>

void IMouseEnterCallback::invokeCallback(GLFWwindow* window, int entered)
{
    invoke(window, static_cast<bool>(entered));
}