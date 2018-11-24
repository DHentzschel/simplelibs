#ifndef IRESIZEWINDOWCALLBACK_H
#define IRESIZEWINDOWCALLBACK_H

#include <vector2.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMaximizeWindowCallback;

class IMinimizeWindowCallback;

class IResizeWindowCallback {
    friend class Window;

public:
    void invokeCallback(GLFWwindow* window, int width, int height);

    virtual void invoke(GLFWwindow* window, const Vector2& size) {}

private:
    IMaximizeWindowCallback* maximizeWindowCallback_ = nullptr;

    IMinimizeWindowCallback* minimizeWindowCallback_ = nullptr;

};

#endif // IRESIZEWINDOWCALLBACK_H
