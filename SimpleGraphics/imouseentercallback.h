#ifndef IMOUSEENTERCALLBACK_H
#define IMOUSEENTERCALLBACK_H

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMouseEnterCallback {
public:
    void invokeCallback(GLFWwindow* window, int entered);

    virtual void invoke(GLFWwindow* window, bool entered) {}

};

#endif // IMOUSEENTERCALLBACK_H
