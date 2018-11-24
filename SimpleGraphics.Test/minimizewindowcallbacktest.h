#ifndef MINIMIZEWINDOWCALLBACKTEST_H
#define MINIMIZEWINDOWCALLBACKTEST_H

#include <iminimizewindowcallback.h>

class MinimizeWindowCallbackTest : public IMinimizeWindowCallback {
public:
    void invoke(GLFWwindow* window) override;

};

#endif // MINIMIZEWINDOWCALLBACKTEST_H
