#ifndef MOUSESCROLLINGCALLBACKTEST_H
#define MOUSESCROLLINGCALLBACKTEST_H

#include <imousescrollingcallback.h>

class MouseScrollingCallbackTest : public IMouseScrollingCallback {
public:
    MouseScrollingCallbackTest();

    ~MouseScrollingCallbackTest();

    void invoke(GLFWwindow* window, const Vector2d& offset);
};

#endif // MOUSESCROLLINGCALLBACKTEST_H
