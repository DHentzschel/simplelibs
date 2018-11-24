#ifndef IMAXIMIZEWINDOWCALLBACK_H
#define IMAXIMIZEWINDOWCALLBACK_H

#include <vector2.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMaximizeWindowCallback {
public:
    void invokeCallback(GLFWwindow* window, const Vector2& size);

    virtual void invoke(GLFWwindow* window, const Vector2& size) {}

};

#endif // IMAXIMIZEWINDOWCALLBACK_H
