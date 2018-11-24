#ifndef IMOUSEMOVINGCALLBACK_H
#define IMOUSEMOVINGCALLBACK_H

#include <vector2d.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMouseMovingCallback {
public:
    void invokeCallback(GLFWwindow* window, const Vector2d& position);

    virtual void invoke(GLFWwindow* window, const Vector2d& position) {}

};

#endif // IMOUSEMOVINGCALLBACK_H
