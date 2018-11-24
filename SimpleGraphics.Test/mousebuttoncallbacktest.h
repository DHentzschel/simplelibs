#ifndef MOUSEBUTTONCALLBACKTEST_H
#define MOUSEBUTTONCALLBACKTEST_H

#include <imousebuttoncallback.h>

class MouseButtonCallbackTest : public IMouseButtonCallback {
public:
    MouseButtonCallbackTest();

    ~MouseButtonCallbackTest();

    void invoke(GLFWwindow* window, Key button, InputAction action, byte mods);
};

#endif // MOUSEBUTTONCALLBACKTEST_H
