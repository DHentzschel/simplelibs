#ifndef WINDOWRESIZECALLBACKTEST_H
#define WINDOWRESIZECALLBACKTEST_H

#include <iresizewindowcallback.h>

class ResizeWindowCallbackTest : public IResizeWindowCallback {
public:
    void invoke(GLFWwindow* window, const Vector2i& size) override;

};

#endif // WINDOWRESIZECALLBACKTEST_H
