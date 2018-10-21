#include <window.h>
#include "keycallbacktest.h"

int main()
{
    KeyCallbackTest kcb;

    Window window;
    window.setIsRunning(true);

    window.setKeyCallback(&kcb);

    while (window.getIsRunning()) {
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}