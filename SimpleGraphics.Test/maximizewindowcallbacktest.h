#ifndef MAXIMIZEWINDOWCALLBACKTEST_H
#define MAXIMIZEWINDOWCALLBACKTEST_H

#include <imaximizewindowcallback.h>

class MaximizeWindowCallbackTest : public IMaximizeWindowCallback {
public:
    void invoke(GLFWwindow* window, const Vector2i& size) override;

};

#endif // MAXIMIZEWINDOWCALLBACKTEST_H
