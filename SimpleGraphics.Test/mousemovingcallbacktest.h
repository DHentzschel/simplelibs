#ifndef MOUSEMOVINGCALLBACKTEST_H
#define MOUSEMOVINGCALLBACKTEST_H

#include <imousemovingcallback.h>

class MouseMovingCallbackTest : public IMouseMovingCallback {
public:
    void invoke(GLFWwindow* window, const Vector2d& position) override;

};

#endif // MOUSEMOVINGCALLBACKTEST_H
