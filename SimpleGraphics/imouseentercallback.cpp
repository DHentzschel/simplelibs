#include "imouseentercallback.h"

#include <functions.h>

void IMouseEnterCallback::invokeCallback(GLFWwindow* window, int entered) {
    invoke(window, STATIC_CAST(bool, entered));
}