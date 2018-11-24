#ifndef IMINIMIZEWINDOWCALLBACK_H
#define IMINIMIZEWINDOWCALLBACK_H

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMinimizeWindowCallback {
public:
    void invokeCallback(GLFWwindow* window);

    virtual void invoke(GLFWwindow* window) {}

};

#endif // IMINIMIZEWINDOWCALLBACK_H
