#ifndef IMOUSEBUTTONCALLBACK_H
#define IMOUSEBUTTONCALLBACK_H

#include <types.h>

#include "key.h"
#include "inputaction.h"

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IMouseButtonCallback {
public:
    void invokeCallback(GLFWwindow* window, int button, int action, int mods);

    virtual void invoke(GLFWwindow* window, Key button, InputAction action, byte mods) {}

};

#endif // IMOUSEBUTTONCALLBACK_H
