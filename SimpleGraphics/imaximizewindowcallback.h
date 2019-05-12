#ifndef IMAXIMIZEWINDOWCALLBACK_H
#define IMAXIMIZEWINDOWCALLBACK_H

#include <vector2i.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMaximizeWindowCallback {
public:
    void invokeCallback(GLFWwindow* window, const Vector2i& size);

    virtual void invoke(GLFWwindow* window, const Vector2i& size) {}

};

#endif // IMAXIMIZEWINDOWCALLBACK_H
