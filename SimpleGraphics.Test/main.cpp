#include <window.h>

#include "keycallbacktest.h"
#include "mousebuttoncallbacktest.h"
#include "mousescrollingcallbacktest.h"
#include "mousemovingcallbacktest.h"
#include "filedropcallbacktest.h"
#include "mouseentercallbacktest.h"
#include "resizewindowcallbacktest.h"
#include "minimizewindowcallbacktest.h"
#include "maximizewindowcallbacktest.h"

#include <mouse.h>
int main()
{
    KeyCallbackTest kcb;
    MouseButtonCallbackTest mcb;
    MouseScrollingCallbackTest scb;
    MouseMovingCallbackTest mvcb;
    FileDropCallbackTest fdcb;
    MouseEnterCallbackTest mecb;
    ResizeWindowCallbackTest mrcb;
    MinimizeWindowCallbackTest mincb;
    MaximizeWindowCallbackTest maxcb;

    Window window;
    window.setIsRunning(true);

    Mouse::setWindow(&window);
    Mouse::setCursorPosition(Vector2d(0.0F, 0.0F), &window);

    //window.setKeyCallback(&kcb);
    //window.setMouseButtonCallback(&mcb);
    //window.setMouseScrollingCallback(&scb);
    //window.setMouseMovingCallback(&mvcb);
    //window.setFileDropCallback(&fdcb);
    //window.setMouseEnterCallback(&mecb);
    window.setMinimizeWindowCallback(&mincb);
    window.setMaximizeWindowCallback(&maxcb);
    window.setResizeWindowCallback(&mrcb);

    while (window.getIsRunning()) {
        window.clear();
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}