#ifndef IMOUSESCROLLINGCALLBACK_H
#define IMOUSESCROLLINGCALLBACK_H

#include <vector2d.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMouseScrollingCallback {
public:
    void invokeCallback(GLFWwindow* window, const Vector2d& offset);

    virtual void invoke(GLFWwindow* window, const Vector2d& offset) {}

};

#endif // IMOUSESCROLLINGCALLBACK_H
